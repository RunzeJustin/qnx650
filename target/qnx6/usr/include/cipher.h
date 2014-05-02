/*
 *  cipher.h
 *
 *  Copyright by QNX Software Systems Limited 2006. All rights reserved.
 */

#ifndef _CIPHER_H_INCLUDED
#define _CIPHER_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define CIPHER_ENTRY	"cipher_create"

/* Never change the order (but you can add to the end) */
enum {
	CIPHER_NONE,     CIPHER_AES,     CIPHER_TWOFISH, CIPHER_SERPENT,
	CIPHER_BLOWFISH, CIPHER_DES3
} ;


struct cipher {
	struct {
		struct cipher*	(*create)(int keybits);
		void			(*destroy)(struct cipher *cip);
		int				(*setkey)(struct cipher *cip, const unsigned char *key);
		void			(*encrypt)(const unsigned char *ibuf, unsigned char *obuf, const void *eks);
		void			(*decrypt)(const unsigned char *ibuf, unsigned char *obuf, const void *dks);
		void			(*reserved1)(void);
		void			(*reserved2)(void);
		void			(*reserved3)(void);
	} funcs;
	int			type;		/*  enum CIPHER_xxx */
	int			keybits;	/*  Typically 128, 192, 256 */
	unsigned	reserved[4];
	void		*eks;		/*  Points to ciphers private encrypt key storage */
	void		*dks;		/*  Points tp ciphers private decrypt key storage */
 } ;

__BEGIN_DECLS
__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/lib/cipher/public/cipher.h $ $Rev: 680336 $")
#endif
