/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


#include <stdarg.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include "apis.h"

#define MAX_DEVICES		5	/* Maximum number of connected devices allowed */
#define NUM_COLORS		5	/* Number of colors to handle */
#define BORDER_X_OFFSET		6	/* The horizontal padding to use between our border and window */
#define BORDER_Y_OFFSET		4	/* The vertical padding to use between our border and window */
#define SLIDER_HEIGHT		3	/* The heigh of our slider bar */
#define MIN_WINDOW_Y_SZ		7	/* The minimum horizontal window size allowed */
#define READ_TIMEOUT		(500)	/* How often to check for signal when blocked on getch() */

#define FLAG_SHUTDOWN		0x0001	/* Indicate we want to shutdown */
#define FLAG_RESIZE		0x0002	/* Indicate the terminal has been resized */

/* Function prototypes for our function pointers */
static int read_input ( WINDOW *w );
static int read_color ( WINDOW *w );
static int read_slider( WINDOW *w );
static int read_device( WINDOW *w );

typedef int (*func_ptr_t)( WINDOW *w );

/* Our ncurses windows */
enum {
	WINDOW_OUTPUT = 0,
	WINDOW_INPUT,
	WINDOW_SLIDER,
	WINDOW_COLOR,
	WINDOW_DEVICES,

	WINDOW_COUNT
};

/* Our ncurses color schemes */
enum {
	SCHEME_BORDER = 1,
	SCHEME_DEFAULT,
	SCHEME_RED,
	SCHEME_GREEN,
	SCHEME_BLUE,
	SCHEME_YELLOW
};

static pthread_mutex_t	console_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t	device_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t	device_cond = PTHREAD_COND_INITIALIZER;
static const char	*colors[] = { "[ ]None", "[ ]Red", "[ ]Green", "[ ]Blue", "[ ]Yellow" };
static const int	y_sz[] =  { -1, MIN_WINDOW_Y_SZ, MIN_WINDOW_Y_SZ, MIN_WINDOW_Y_SZ, MIN_WINDOW_Y_SZ };
static WINDOW		*borders[WINDOW_COUNT];
static WINDOW		*wins[WINDOW_COUNT];
static WINDOW		*c_win = NULL;
static acc_t		*dev_head;
static acc_t		*acc_tail;
static acc_t		*g_dev = NULL;
static int		color_pos[NUM_COLORS][NUM_COLORS];
static int		ctrl = WINDOW_INPUT;
static int		slider_pos = 1;
static int		color_idx = 0;
static int		device_cnt = 0;
static int		g_flags = 0;

/* Headers to write on our curses windows */
static const char	*w_hdr[] = {
	"Console Output:\n",
	"Console Input:\n",
	"Slider Position:\n",
	"Color Value:\n",
	"Device:\n"
};

/* Function pointer list for handling the different windows */
static func_ptr_t	funcs[] = {
	NULL,
	&read_input,
	&read_slider,
	&read_color,
	&read_device
};

/*
 * This function gives us a total of our horizontal window sizes.  If the window
 * is defined with a size of -1 in y_sz(), we simply return 0 for it's size.
 */
static int y_total( void ) {
	int	i;
	int	ret = 0;

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		ret += y_sz[i] > 0 ? y_sz[i] : 0;
	}
	return ret;
}

/*
 * This function gives us the minimum horizontal window size required for this
 * application to run.
 */
static int y_min( void ) {
	int	i;
	int	ret = 0;

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		ret += y_sz[i] > 0 ? y_sz[i] : MIN_WINDOW_Y_SZ;
	}
	return ret;
}

/*
 * This function gives us the minimum vertical window size required for this
 * application to run.  It is defined by the color strings as these represent
 * the longest width for our windows and we want them on one line.
 */
static int x_min( void ) {
	int	i;
	int	ret = 0;

	for ( i=0; i<NUM_COLORS; i++ ) {
		ret += strlen(colors[i]) + 1;
	}

	return ret + BORDER_X_OFFSET;
}

/*
 * This function writes the headers to the correct windows.
 */
static int create_headers( void ) {
	int	i;

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		mvwaddstr( borders[i], 1, 2, w_hdr[i] );
	}

	return 0;
}

/*
 * This function either colorizes the border of the active window or sets the
 * color back to the default if we're losing focus from the active window.
 */
static int color_border( int idx, int scheme ) {
	pthread_mutex_lock( &console_mutex );
	if ( scheme == SCHEME_DEFAULT ) {
		wbkgd( borders[idx], COLOR_PAIR(scheme) );
	}
	else {
		wbkgd( borders[idx], COLOR_PAIR(scheme) );
	}
	wrefresh( borders[idx] );
	wrefresh( wins[idx] );
	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function creates a border around all our windows.
 */
static int create_borders( void ) {
	int	i;

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		box( borders[i], 0, '=' );
	}

	return 0;
}

/*
 * This function refreshes all the window's at once.  Updates don't take place on
 * a window until wrefresh() is called so when we're building up the screen, we
 * can call this last to draw them all at once.
 */
static int refresh_windows( void ) {
	int	i;

	pthread_mutex_lock( &console_mutex );
	for ( i=0; i<WINDOW_COUNT; i++ ) {
		wrefresh( borders[i] );
		wrefresh( wins[i] );
	}
	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function is used to draw the color window.  We want to write the name of
 * the color and keep track of the position of the bracks '[ ]' so we can place
 * an 'x' inside of it if selected and draw an arrow '^' underneath it while
 * chosing a selection.
 */
static int create_colors( WINDOW *w, int max_y, int max_x ) {
	int	i, j;
	int	x=1, y=0;

	for ( i=0; i<NUM_COLORS; i++ ) {

		/* Check to make sure we have room on the current line */
		if ( (x + 2 + strlen(colors[i])) >= max_x ) {
			x = 1;

			if ( (y += 2) >= max_y ) {
				return -1;
			}
		}

		/* Save the position of the location between the brackets */
		color_pos[i][0] = y;
		color_pos[i][1] = x + 1;
		for ( j=0; j<strlen(colors[i]); j++ ) {
			mvwaddch( w, y, x + j, colors[i][j] );
		}
		x += strlen(colors[i]) + 1;
	}

	/* Set the current color */
	mvwaddch( w, color_pos[color_idx][0], color_pos[color_idx][1], 'x' );

	return 0;
}

/*
 * This function is used to create the ncurses windows.  Each window has an outter
 * window around it which contains a border which we can colorize to indicate
 * focus.
 */
static int create_windows( void ) {
	int	max_y, max_x;
	int	y_off = 0, x_off = 0;
	int	b_y_off = BORDER_Y_OFFSET;
	int	b_x_off = BORDER_X_OFFSET;
	int	y, x;
	int	i;

	/* Let's make sure our terminal is large enough for the screens */
	getmaxyx( stdscr, max_y, max_x );
	if ( (max_y < y_min())|| (max_x < x_min()) ) {
		fprintf( stderr, "Window must be at least %d %d to run this application", x_min(), y_min() );
		return -1;
	}

	x = max_x;
	y = 0;
	for ( i=0; i<WINDOW_COUNT; i++ ) {
		if ( y_sz[i] == -1 ) {
			y = max_y - y_off - y_total();
		}
		else {
			y = y_sz[i];
		}

		/* create the border window and the sub-window */
		borders[i] = newwin( y, x, y_off, x_off );
		wins[i] = newwin( (y - b_y_off), (x - b_x_off), (y_off + (b_y_off/2) + 1), (x_off + (b_x_off/2)) );
		if ( !borders[i] || !wins[i] ) {
			fprintf( stderr, "Unable to create windows.\n" );
			return -1;
		}

		if ( i == WINDOW_SLIDER ) {
			/* Draw the slider box */
			box( wins[i], 0, '-' );
			mvwaddch( wins[i], 1, 1, '#' );
		}
		else if ( i == WINDOW_COLOR ) {
			/* Write the color names to the window */
			create_colors( wins[i], max_y, max_x );
		}
		else if ( i == WINDOW_DEVICES ) {
			/* Set some default device information */
			mvwprintw( wins[i], 0, 1, "Devices: 0" );
			mvwprintw( wins[i], 1, 1, "Name:    [NONE]" );
		}

		/* Keep a running total of our window size */
		y_off += y;
	}

	return 0;
}

/*
 * This function is used to indicate a selection in the color window.  An 'x'
 * will be placed in the selected position between the bracks '[ ]', the brackets
 * will be turned bold and the name of the color will take on the corresponding
 * color.
 *
 * Note: 'color_mutex' must be locked to call this function.
 */
static int refresh_color_window( WINDOW *w, int pos ) {
	int	tpos;

	tpos = (pos == -1) ? 0 : pos;
	mvwaddch( w, color_pos[color_idx][0], color_pos[color_idx][1], ' ' );
	mvwaddstr( w, color_pos[color_idx][0], color_pos[color_idx][1] + 2, colors[color_idx] + 3 );

	if ( pos != -1 ) {
		/* We don't want to set a color or 'x' on an empty screen */
		wattron( w, A_BOLD );
		mvwaddch( w, color_pos[tpos][0], color_pos[tpos][1], 'x' );
		wattron( w, COLOR_PAIR(pos + 2) );
	}
	mvwaddstr( w, color_pos[tpos][0], color_pos[tpos][1] + 2, colors[tpos] + 3 );
	wattroff( w, A_BOLD );
	wattroff( w, COLOR_PAIR(tpos + 2));

	return 0;
}

/*
 * This function is used to update the 'device' window which notifies the user
 * of all connected devices.
 *
 * Note: 'dev_mutex' must be locked to call this function.
 */
static int update_device_window( WINDOW *w ) {
	pthread_mutex_lock( &console_mutex );
	wmove( w, 0, 0 );
	wclrtoeol( w );
	wmove( w, 1, 0 );
	wclrtoeol( w );

	mvwprintw( w, 0, 1, "Devices: %d", device_cnt );
	mvwprintw( w, 1, 1, "Name:    %s", (device_cnt && g_dev) ? g_dev->name : "[NONE]" );

	wrefresh( w );
	pthread_mutex_unlock( &console_mutex );
	return 0;
}

/*
 * This function is used to clear the input window of any text which exists. It
 * should be called when the window loses focus.
 */
static int clear_input( WINDOW *w ) {
	pthread_mutex_lock( &console_mutex );
	wmove( w, 0, 0 );
	wclrtoeol( w );
	wrefresh( w );
	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function is used to clear the arrows present in the color window.  It
 * should be called when the window loses focus.
 */
static int clear_color( WINDOW *w ) {
	pthread_mutex_lock( &console_mutex );
	wmove( w, 1, 0 );
	wclrtoeol( w );
	wrefresh( w );
	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function is used query the Android application for either the slider
 * position or the current color.  When the incoming data is received, the
 * corresponding ncurses window will be updated accordingly.
 *
 * Note: 'dev_mutex' must be locked to call this function.  Our 'send_data()'
 *       is non-blocking so the device mutex won't be held if we encounter
 *       any USB issues.
 */
static int request_window_value( int window ) {
	uint8_t		ctrl = 's';

	switch ( window ) {
		case WINDOW_SLIDER:
			ctrl = 's';
			break;
		case WINDOW_COLOR:
			ctrl = 'c';
			break;
		default:
			/* This should never happen */
			break;
	}
	return send_data( g_dev, NULL, ctrl, (uint8_t)-1, 0 );
}

/*
 * This function is used to handle keystrokes which are common to all ncurses
 * windows.  In our case, the up and down arrows are used to switch between
 * windows.  The wtimeout() function performs a select() on a timer and our
 * wgetch().  We have the timer set to 1/2 a second so if the termination
 * signal is caught by our client, we can break out of are read loop here.
 */
int check_ctrl_switch( WINDOW *w, int *ch ) {
	int	rc = 0;

	do {
		wtimeout( w, READ_TIMEOUT );
		*ch = wgetch( w );
		switch ( *ch ) {
			case KEY_UP:
				/* Update our current focus via a color scheme */
				color_border( ctrl, SCHEME_DEFAULT );
				if ( ctrl == 1 ) {
					ctrl = WINDOW_COUNT -1;
				}
				else {
					ctrl -= 1;
				}
				rc = -1;

				break;
			case KEY_DOWN:
				/* Update our current focus via a color scheme */
				color_border( ctrl, SCHEME_DEFAULT );
				if ( ctrl == WINDOW_COUNT - 1 ) {
					ctrl = 1;
				}
				else {
					ctrl += 1;
				}
				rc = -1;

				break;
			case EOF:
				/* Break our read loop and check for shutdown status */
				pthread_mutex_lock( &device_mutex );
				if ( g_flags || !g_dev ) {
					rc = -2;
				}
				pthread_mutex_unlock( &device_mutex );
				break;
			default:
				break;
		}
	} while ( (*ch == EOF) && rc >= 0 );

	return rc;
}

/*
 * This function is used to handle the device window.  When the left arrow key
 * is pressed, we will go back a device looping to the end of the list when at
 * the first device.  Similarly, when the right arrow key is pressed, we'll move
 * on to our next device and loop to the beginning of the list if we're currently
 * on the last device.  If a different device is selected, we'll update our device
 * window and make a request to the Android application to pass us it's current
 * slider position and color.
 */
static int read_device( WINDOW *w ) {
	acc_t	*prev;
	int	rc, ch;
	int	update;

	do {
		/* Get our key press */
		rc = check_ctrl_switch( w, &ch );
		if ( rc < 0 ) {
			return -1;
		}
		update = 0;

		pthread_mutex_lock( &device_mutex );
		if ( !g_dev ) {
			pthread_mutex_unlock( &device_mutex );
			return -1;
		}

		switch ( ch ) {
		case KEY_RIGHT:
			/* Get our next device, looping at end */
			prev = g_dev;
			if ( device_cnt > 1 ) {
				g_dev = g_dev->next;
				if ( !g_dev ) {
					g_dev = dev_head;
				}
				if ( g_dev != prev ) {
					update = 1;
				}
			}
			break;
		case KEY_LEFT:
			/* Get our next device, looping at beginning */
			prev = g_dev;
			if ( device_cnt > 1 ) {
				g_dev = g_dev->prev;
				if ( !g_dev ) {
					g_dev = acc_tail;
				}
				if ( g_dev != prev ) {
					update = 1;
				}
			}
			break;
		case '\n':
		default:
			break;
		}

		if ( update ) {
			/* If the device is different, update our windows */
			update_device_window( w );
			request_window_value( WINDOW_SLIDER );
			request_window_value( WINDOW_COLOR );
		}
		pthread_mutex_unlock( &device_mutex );
	} while ( 1 );

	return -1;
}

/*
 * This function is used to handle the color window.  When the left arrow key
 * is pressed, we will move our location arrow under the brackets '[ ]' of the
 * previous color.  Similarly, when the right arrow key is pressed, we will move
 * our location arrow under the brackets '[ ]' of the next color.  If the enter
 * key is pressed, we'll update the window to place an and x between the brackets
 * of the current color '[x]'.  We'll also set the text to the proper color and
 * make the brackets bold.  Once selected, we'll pass our selection on to the
 * Android application so it can update the UI.
 */
static int read_color( WINDOW *w ) {
	int			rc, ch;
	int			pos = 0;
	int			slct;
	int			update;
	int			prev;

	pthread_mutex_lock( &console_mutex );
	mvwaddch( w, color_pos[0][0] + 1, color_pos[0][1], ACS_UARROW );
	wrefresh( w );
	pthread_mutex_unlock( &console_mutex );
	do {
		/* Get our key press */
		rc = check_ctrl_switch( w, &ch );
		if ( rc < 0 ) {
			if ( rc == -1 ) {
				clear_color( w );
			}
			return -1;
		}
		slct = 0;
		update = 0;

		switch ( ch ) {
		case KEY_RIGHT:
			/* Move to the next set of brackets [ ], looping at end */
			prev = pos;
			pos += 1;
			if ( pos == NUM_COLORS ) {
				pos = 0;
			}
			update = 1;
			break;
		case KEY_LEFT:
			/* Move to the next set of brackets [ ], looping at beginning */
			prev = pos;
			pos -= 1;
			if ( pos < 0 ) {
				pos = NUM_COLORS - 1;
			}
			update = 1;
			break;
		case '\n':
			/*
			 * User is making a selection. Update our current position with '[x]' and
			 * update the color of the selection.
			 */
			pthread_mutex_lock( &console_mutex );
			refresh_color_window( w, pos );
			wrefresh( w );
			pthread_mutex_unlock( &console_mutex );

			color_idx = pos;
			slct = 1;
			break;
		default:
			break;
		}

		if ( update ) {
			/*
			 * We've updated our current position, move our arrow '^' to indicate
			 * our new position and delete the old one.
			 */
			pthread_mutex_lock( &console_mutex );
			mvwdelch( w, color_pos[prev][0] + 1, color_pos[prev][1] );
			mvwaddch( w, color_pos[pos][0] + 1, color_pos[pos][1], ACS_UARROW );
			wrefresh( w );
			pthread_mutex_unlock( &console_mutex );
		}

		if ( slct ) {
			/* Send our selection to the Android application */
			pthread_mutex_lock( &device_mutex );
			rc = send_data( g_dev, NULL, 'c', (uint8_t)pos, 0 );
			pthread_mutex_unlock( &device_mutex );
			if ( rc == -1 ) {
				break;
			}
		}
	} while ( 1 );

	return -1;
}

/*
 * This function is used to handle the slider window.  When the left arrow key
 * is pressed, the slider '#' will be moved one position to the left.  Similarly,
 * when the right arrow key is pressed, the slider will be moved one position to
 * the right.  The position is bounded by the window box and can't exceed it
 * in either direction.  Once the slider has moved, we will send the position to
 * the Android application so it can update the UI.
 */
static int read_slider( WINDOW *w ) {
	int	rc, ch;
	int	y, x;
	int	new_pos = 0;

	do {
		/* Get our key press */
		rc = check_ctrl_switch( w, &ch );
		if ( rc < 0 ) {
			return -1;
		}

		pthread_mutex_lock( &console_mutex );
		switch ( ch ) {
		case KEY_RIGHT:
			/* move our slider to the right, stopping at the end */
			getmaxyx( w, y, x );
			mvwaddch( w, 1, slider_pos, ' ' );

			if ( slider_pos != (x -2) ) {
				slider_pos++;
			}
			break;
		case KEY_LEFT:
			/* move our slider to the left, stopping at the beginning */
			getmaxyx( w, y, x );
			mvwaddch( w, 1, slider_pos, ' ' );

			if ( slider_pos != 1 ) {
				slider_pos--;
			}
			break;
		default:
			pthread_mutex_unlock( &console_mutex );
			continue;
			break;
		}

		/* Update our slider position visually */
		mvwaddch( w, 1, slider_pos, '#' );
		wrefresh( w );
		new_pos = slider_pos;

		pthread_mutex_unlock( &console_mutex );

		/* Send our selection to the Android application after scaling it */
		new_pos /= ((double)x/(double)100);
		pthread_mutex_lock( &device_mutex );
		rc = send_data( g_dev, NULL, 's', (uint8_t)new_pos, 0 );
		pthread_mutex_unlock( &device_mutex );
		if ( rc == -1 ) {
			break;
		}
	} while ( 1 );

	return -1;
}

/*
 * This function is used to handle the input window.  When an alphanumeric key is
 * pressed, it will be echo'd to the screen.  If the delete key is pressed, the
 * last value entered will be removed.  If the enter key is pressed, any data
 * including an empty buffer will be sent to the Android application so it can
 * update the UI.
 *
 * Note: When focus from this window is lost, we delete and text currently written.
 */
static int read_input( WINDOW *w ) {
	int		rc, ch;
	int		pos = 1;
	uint8_t		buf[64];

	/* Add a fake cursor to the screen */
	pthread_mutex_lock( &console_mutex );
	mvwaddch( w, 0, 0, '_' );
	wrefresh( w );
	pthread_mutex_unlock( &console_mutex );
	buf[0] = 't';
	do {
		/* Get our key press */
		rc = check_ctrl_switch( w, &ch );
		if ( rc < 0 ) {
			if ( rc == -1 ) {
				/* Clear the screen if we lose focus */
				clear_input( w );
			}
			return -1;
		}

		pthread_mutex_lock( &console_mutex );
		switch ( ch ) {
		case '\n':
			/*
			 * When enter is pressed, clear our screen and send the current
			 * data to the Android application
			 */
			wmove( w, 0, 0 );
			wclrtoeol( w );
			buf[pos] = '\0';
			mvwaddch( w, 0, 0, '_' );

			pthread_mutex_unlock( &console_mutex );
			pthread_mutex_lock( &device_mutex );
			rc = send_data( g_dev, buf, 0, 0, pos + 1 );
			pthread_mutex_unlock( &device_mutex );
			if ( rc == -1 ) {
				return -1;
			}
			pos = 1;
			continue;

			break;
		case KEY_BACKSPACE:
		case KEY_DC:
		case 127:
			/* Backspace or delete key is pressed, remove our last character */
			if ( pos > 1 ) {
				mvwdelch( w, 0, pos - 1 );
				mvwaddch( w, 0, pos - 2, '_' );
				pos--;
			}
			break;
		default:
			/*
			 * Record the keystroke if it's alphanumeric and print it to the window
			 * otherwise simply ignore it and don't print it to the window.
			 */
			if ( ch > 31 && ch < 127 && pos != 32 ) {
				mvwaddch( w, 0, pos - 1, ch );
				mvwaddch( w, 0, pos, '_' );
				buf[pos] = ch;
				pos++;
			}
			break;
		}
		wrefresh( w );
		pthread_mutex_unlock( &console_mutex );

	} while( 1 );

	return -1;
}

/*
 * This is the main reader loop of the program.  We block until a device has been
 * inserted and once inserted, we start listening for keyboard input.  Depending
 * on what window currently has focus, we'll call the appropriate function via
 * a function pointer to handle that window.
 */
int read_loop( void ) {
	int		rc = 0;

	do {
		/* Block waiting for at least 1 device */
		pthread_mutex_lock( &device_mutex );
		while ( device_cnt == 0 && !g_flags ) {
			write_console( "\nWaiting for AOA device...\n\n" );

			/* Block waiting for device here */
			pthread_cond_wait( &device_cond, &device_mutex );
		}

		/* Exit if we get either a resize or shutdown request */
		if ( (g_flags & FLAG_RESIZE) ) {
			g_flags &= ~FLAG_RESIZE;
			g_flags |= FLAG_SHUTDOWN;
		}
		if ( (g_flags & FLAG_SHUTDOWN) ) {
			pthread_mutex_unlock( &device_mutex );
			return 0;
		}
		pthread_mutex_unlock( &device_mutex );

		/* Call the window functions depending on user input */
		color_border( ctrl, SCHEME_BORDER );
		rc = funcs[ctrl]( wins[ctrl] );
		if ( (rc == -1) && (g_flags & FLAG_SHUTDOWN) ) {
			break;
		}
	} while ( 1 );

	return 0;
}

/*
 * This function is used to set the color value when an update from the Android
 * application is received or we force it to reset internally by passing in a
 * position value of -1.
 */
int write_color( aoa_hdl_t *hdl, int pos ) {
	WINDOW	*w = wins[WINDOW_COLOR];
	int	tpos = pos;

	if ( pos != -1 ) {
		pthread_mutex_lock( &device_mutex );
		if ( (!g_dev || hdl != g_dev->hdl) ) {
			pthread_mutex_unlock( &device_mutex );
			return 0;
		}
		pthread_mutex_unlock( &device_mutex );

		if ( pos > (NUM_COLORS -1) ) {
			return -1;
		}
	}
	else {
		pos = 0;
	}

	pthread_mutex_lock( &console_mutex );
	if ( pos != color_idx ) {
		refresh_color_window( w, tpos );
		wrefresh( w );
		color_idx = pos;
	}
	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function is used to set the slider position when an update from the
 * Android application is received or we force it to reset internally by passing
 * in a position value of -1.
 */
int write_slider( aoa_hdl_t *hdl, int pos ) {
	WINDOW		*w = wins[WINDOW_SLIDER];
	double		scale;
	int		maxy, maxx;

	if ( pos != -1 ) {
		pthread_mutex_lock( &device_mutex );
		if ( !g_dev || (hdl != g_dev->hdl) ) {
			pthread_mutex_unlock( &device_mutex );
			return 0;
		}
		pthread_mutex_unlock( &device_mutex );

		if ( pos > 100 ) {
			return -1;
		}
	}
	else {
		pos = 0;
	}

	pthread_mutex_lock( &console_mutex );

	getmaxyx( w, maxy, maxx );
	scale = (double)maxx / (double)100;

	mvwaddch( w, 1, slider_pos, ' ' );
	slider_pos = (double)pos * (double)scale;
	if ( slider_pos == 0 ) {
		slider_pos = 1;
	}
	else if ( slider_pos == maxx ) {
		slider_pos = maxx - 2;
	}

	mvwaddch( w, 1, slider_pos, '#' );
	leaveok( c_win, TRUE );
	wrefresh( w );
	leaveok( c_win, FALSE );

	pthread_mutex_unlock( &console_mutex );

	return 0;
}

/*
 * This function is used to write text to the console window.  This data can be
 * coming from different devices and will generally be prepended with the device
 * name to differentiate who's writing.
 */
void write_console( const char *fmt, ... ) {
	va_list		arg;
	char		buf[1024];

	/* Convert user message to a string */
	va_start( arg, fmt );
	vsnprintf( buf, sizeof(buf), fmt, arg );
	va_end( arg );

	pthread_mutex_lock( &console_mutex );
	waddstr( wins[WINDOW_OUTPUT], buf );
	wrefresh( wins[WINDOW_OUTPUT] );
	pthread_mutex_unlock( &console_mutex );

	return;
}

/*
 * This function is used to build up our ncurses windows.  This includes setting
 * up colors, drawing the borders, drawing the main windows and setting some
 * default values.
 */
int setup_windows( void ) {
	int	rc;
	int	i;

	initscr();
	noecho();
	curs_set( 0 );

	if ( has_colors() ) {
		start_color();
		init_pair( SCHEME_DEFAULT, COLOR_WHITE,  COLOR_BLACK );
		init_pair( SCHEME_BORDER,  COLOR_YELLOW, COLOR_BLACK );
		init_pair( SCHEME_RED,     COLOR_RED,    COLOR_BLACK );
		init_pair( SCHEME_GREEN,   COLOR_GREEN,  COLOR_BLACK );
		init_pair( SCHEME_BLUE,    COLOR_BLUE,   COLOR_BLACK );
		init_pair( SCHEME_YELLOW,  COLOR_YELLOW, COLOR_BLACK );
	}

	rc = create_windows();
	if ( rc == -1 ) {
		return -1;
	}
	create_headers();
	create_borders();

	/* Setup our input terminal to scroll */
	scrollok( wins[WINDOW_OUTPUT], 1 );

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		keypad( wins[i], TRUE );
	}

	/* Refresh the windows */
	refresh_windows();

	return 0;
}

/*
 * This function is used to completely clear all window data to try and leave the
 * terminal in a nice clean state.  Clear all the data and overwrite our borders
 * with empty characters before ending our windows.
 */
int destroy_windows( void ) {
	int	i;

	for ( i=0; i<WINDOW_COUNT; i++ ) {
		box( borders[i], ' ', ' ' );
		wbkgd( borders[i], COLOR_PAIR(SCHEME_DEFAULT) );
		wclear( borders[i] );
		wclear( wins[i] );
		wrefresh( borders[i] );
		wrefresh( wins[i] );
		delwin( borders[i] );
		delwin( wins[i] );
	}
	curs_set(1);
	endwin();

	return 0;
}

/*
 * This function is used to add a new device to our list of devices.  It should
 * be called when a main application thread starts up.  If our maximum device
 * count is already reached, simply return.
 */
acc_t *add_device( aoa_hdl_t *hdl, const char *name ) {
	acc_t	*ret = NULL;
	acc_t	*prev = NULL;
	acc_t	**node;
	int	idx = 0;

	pthread_mutex_lock( &device_mutex );

	/* Have we reached our maximum connected devices? */
	if ( device_cnt == MAX_DEVICES ) {
		pthread_mutex_unlock( &device_mutex );
		write_console( "New device inserted but maximum reached, ignoring '%s'\n", name );
		return NULL;
	}

	ret = calloc( 1, sizeof(*ret) );
	if ( !ret ) {
		pthread_mutex_unlock( &device_mutex );
		return NULL;
	}
	acc_tail = ret;

	node = &dev_head;
	while ( *node ) {
		/* Look through our list for the highest device index if any current
		 * devices match our device name. This is so we have a unique identifier
		 * if more than one device with the same name exists.
		 *
		 * ex) NEXUS (1), NEXUS (2), etc.
		 */
		if ( strncmp((*node)->name, name, strlen(name)) == 0 ) {
			idx = max(idx, (*node)->idx);
		}
		prev = *node;
		node = &(*node)->next;
	}
	*node = ret;

	/* Setup our newly created node */
	snprintf( ret->name, sizeof(ret->name), "%s (%d)", name, idx + 1 );
	ret->hdl = hdl;
	ret->shutdown = 0;
	ret->idx = idx + 1;
	ret->prev = prev;
	ret->next = NULL;
	pthread_cond_init( &ret->cond, NULL );
	pthread_mutex_init( &ret->mutex, NULL );

	if ( ++device_cnt == 1 ) {
		/*
		 * If this is the only active connection, let's setup our windows to indicate
		 * that there's an active device.
		 */
		ctrl = WINDOW_INPUT;
		color_border( ctrl, SCHEME_BORDER );
		g_dev = dev_head;

		/* Let's request the Android apps color/slider window values */
		request_window_value( WINDOW_SLIDER );
		request_window_value( WINDOW_COLOR );
	}

	/* Update the device window as things have changed*/
	update_device_window( wins[WINDOW_DEVICES] );
	pthread_cond_signal( &device_cond );
	pthread_mutex_unlock( &device_mutex );

	return ret;
}

/*
 * This function is used to cleanup a device node once a main application thread
 * completely finishes.  It should only be called at the very end of the control
 * thread to ensure we aren't currently using it.
 */
int destroy_device( acc_t *dev ) {
	pthread_mutex_lock( &device_mutex );

	/* Cleanup */
	pthread_mutex_destroy( &dev->mutex );
	pthread_cond_destroy( &dev->cond );
	free( dev );

	pthread_mutex_unlock( &device_mutex );

	return 0;
}

/*
 * This function is used to remove a device from the device list.  Although the
 * node will be removed, the device might still be active so we leave it up to
 * the client to delete the device just before the application thread exits. We
 * don't actually delete the node here.
 */
int remove_device( aoa_hdl_t *hdl, bool mutex ) {
	int	err = 0;
	acc_t	*node;

	if ( !mutex ) {
		/* Only lock if not already locked */
		pthread_mutex_lock( &device_mutex );
	}
	do {
		/* Look for our node based on the handle */
		node = dev_head;
		while ( node ) {
			if ( node->hdl == hdl ) {
				break;
			}
			node = node->next;
		}
		if ( !node ) {
			/* Node not found, exit */
			err = -1;
			break;
		}

		/* This is a doubly linked list, setup the proper linkage */
		if ( node->prev ) {
			node->prev->next = node->next;
		}
		else {
			dev_head = node->next;
		}
		if ( node->next ) {
			node->next->prev = node->prev;
		}

		if ( --device_cnt == 0 ) {
			/* If there are no active devices, let's cleanup our windows */
			g_dev = NULL;
			clear_input( wins[WINDOW_INPUT] );
			clear_color( wins[WINDOW_COLOR] );
			write_slider( NULL, -1 );
			write_color( NULL, -1 );
			color_border( ctrl, SCHEME_DEFAULT );
		}
		else {
			if ( node == g_dev ) {
				/* If we're deleing the active node, let's choose another */
				g_dev = dev_head;

				/* Let's request the Android apps color/slider window values */
				request_window_value( WINDOW_SLIDER );
				request_window_value( WINDOW_COLOR );
			}
		}

		/* Update the device window as things have changed*/
		update_device_window( wins[WINDOW_DEVICES] );

		/* Let's notify the running thread that it can shutdown and cleanup this node */
		pthread_mutex_lock( &node->mutex );
		node->shutdown = 1;
		pthread_cond_signal( &node->cond );
		pthread_mutex_unlock( &node->mutex );

	} while ( 0 );

	if ( !mutex ) {
		/* Only lock if locked within this function */
		pthread_mutex_unlock( &device_mutex );
	}

	return err;
}

/*
 * This function is used to unblock all the worker threads on a shutdown if they
 * haven't already been unblocked.  Once they are unblocked, it is up to the
 * thread to call destroy_device() to cleanup the device.
 */
int unblock_worker_threads( ) {
	acc_t	*node;

	pthread_mutex_lock( &device_mutex );

	node = dev_head;
	while ( node ) {
		pthread_mutex_lock( &node->mutex );
		node->shutdown = 1;
		pthread_cond_signal( &node->cond );
		pthread_mutex_unlock( &node->mutex );
		node = node->next;
	}
	pthread_mutex_unlock( &device_mutex );

	return 0;
}

/*
 * This function is used to return the device name stored in the device structure.
 * If it isn't found, "UNKNOWN" will be returned instead.
 */
const char *get_device_name( aoa_hdl_t *hdl ) {
	static const char	*def_name = "UNKNOWN";
	const char		*name = def_name;
	acc_t			*node;

	pthread_mutex_lock( &device_mutex );

	node = dev_head;
	while ( node ) {
		if ( node->hdl == hdl ) {
			name = node->name;
			break;
		}
		node = node->next;
	}
	pthread_mutex_unlock( &device_mutex );

	return name;
}

/*
 * This function is used to indicate the ncurses.c module that a terminal resize
 * has been requested.  Since this isn't currently supported, it will be used to
 * break the read loop and exit.
 */
int set_resize( void ) {
	pthread_mutex_lock( &device_mutex );
	g_flags |= FLAG_RESIZE;
	pthread_cond_signal( &device_cond );
	pthread_mutex_unlock( &device_mutex );

	return 0;
}

/*
 * This function is used to indicate the ncurses.c module that a shutdown has
 * been requested.  It will be used to break the read loop and exit.
 */
int set_shutdown( void ) {
	pthread_mutex_lock( &device_mutex );
	g_flags |= FLAG_SHUTDOWN;
	pthread_cond_signal( &device_cond );
	pthread_mutex_unlock( &device_mutex );

	return 0;
}


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/aoa/examples/demo_curses/ncurses.c $ $Rev: 734140 $")
#endif
