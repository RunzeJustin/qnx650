/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _H_CLI_H_
#define _H_CLI_H_

#include <stdint.h>
#define	_LOGGING_NO_INCLUDE_API_
#include <sys/logging.h>

__BEGIN_DECLS


/**
 * The maximum number of plug-ins that can be used.
 */
#define	CONFIG_MAX_CLIS	8

/**
 * Clock format buffer length.
 */
#define CLI_CLK_LEN 15

/**
 * This function formats the clock in the specified buffer and returns it.
 */
char *cli_clk_fmt( char buf[ CLI_CLK_LEN ] );

/** 
 * This function emits an event log.
 * 
 * @param fmt
 */
void cli_evlog( const char *fmt, ... );

/**
 * A command argument.
 */
typedef struct cli_cmd_arg {
	const char *str;
	long long   num;
} cli_cmd_arg_t;

/**
 * A command output.
 */
#define	CLI_CMD_OP_NAME_LEN_MAX		32
#define	CLI_CMD_OP_VALUE_LEN_MAX	1024
typedef struct cli_cmd_op {
	char    name[CLI_CMD_OP_NAME_LEN_MAX];
	char    value[CLI_CMD_OP_VALUE_LEN_MAX];
} cli_cmd_op_t;

/**
 * Maximum number of arguments per commands.
 */
#define CLI_CMD_MAX_ARGS	10

/**
 * Maximum number of outputs per command.
 */
#define	CLI_CMD_MAX_OPS		4

/** 
 * A command function.
 * 
 * On error, the first output element's value member may be used for an error
 * string.
 * 
 * @param args	Array of arguments to the command
 * @param outputs	Array for outputs from the command
 * @param clk	Clock buffer
 * @return >=0 on success; the number of output elements set
 * @return <0 on failure
 */
typedef int cli_cmd_t(cli_cmd_arg_t const args[CLI_CMD_MAX_ARGS],
					  cli_cmd_op_t outputs[CLI_CMD_MAX_OPS],
					  const char clk[CLI_CLK_LEN]);

/**
 * Command flags
 */
enum cli_cmd_flag {
	CLI_CMD_QUIET  = 1,  /**< Don't log it */
	CLI_CMD_UNCOND = 2,  /**< Unconditional */
};

/**
 * A command definition structure.
 */
typedef struct cli_cmd_def {
	const char *name;		/**< How it's invoked. */
	const char *signature;	/**< 's'=string, 'i'=integer, 'u'=unsigned, '*' = any remaining characters */
	cli_cmd_t  *fun;		/**< The command function. */
	const char *comment;	/**< short help for the command. */
	unsigned    flags;		/**< flags; see cli_cmd_flag enumerations. */
} cli_cmd_def_t;


/**
 * Defines the API version that the plug-in was compiled to.
 */
#define CLI_CI_VER_MAJOR		1
#define CLI_CI_VER_MINOR		0
#define CLI_CI_VER_CURRENT		(((CLI_CI_VER_MAJOR) << 8) | (CLI_CI_VER_MINOR))


/**
 * A command plug-in API.
 */
typedef struct cli_ci {
	/**
	 * The name of the command interface plug-in.
	 * 
	 * Not optional.
	 */
	char       *name;

	/** The version of the plug-in. */
	uint32_t    version;

	/**
	 * The initialization function of the command interface plug-in. Called once.
	 * 
	 * @param config The configuration string for the plug-in.
	 *               The plugin is free to modify it (up to the terminating null character).
	 * @return 0 on success 
	 * @return -1 on failure (must set errno)
	 */
	int             (*init)(char *config, log_hdl_t *log_hdl);

	/**
	 * The termination function of the command interface plug-in.
	 * 
	 * @return 0 on success 
	 * @return -1 on failure 
	 */
	int             (*terminate)(void);

	/**
	 * Sets the logging verbosity and flags of the plug-in.
	 * 
	 * Optional.
	 * 
	 * @param verbosity	Verbosity level
	 * @param flags		Control flags. See logging.h.
	 */
	int             (*logging)(unsigned verbosity, unsigned flags);

	/**
	 * The command array for the plug-in.
	 */
	cli_cmd_def_t  *cmds[];

} cli_ci_t;


/**
 * Until decide how to deal with this...
 */
#define MOD_LOG_INFO(verbose_level, format, args...) \
	LOG_EMIT_INFO(log_hdl, verbose_level, format, ## args)

#define MOD_LOG_WARNING(verbose_level, format, args...) \
	LOG_EMIT_WARNING(log_hdl, verbose_level, format, ## args)

#define MOD_LOG_ERROR(format, args...) \
	LOG_EMIT_ERROR(log_hdl, format, ## args)

#define MOD_LOG_CRITICAL(format, args...) \
	LOG_EMIT_CRITICAL(log_hdl, format, ## args)

#define	MOD_EMITS_TIMING() \
	((log_hdl->control_flags & LOG_EMIT_TIME_LOGS)!=0)

#define MOD_LOG_TIMING(format, args...) \
	LOG_EMIT_TIMING(log_hdl, format, ## args)


__END_DECLS

#endif /* _H_CLI_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/utils/m/mmcli/core/public/mm/mmcli.h $ $Rev: 680801 $")
#endif
