/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef __NEUTRINO_H_INCLUDED
#error arm/neutrino.h should not be included directly.
#endif

__BEGIN_DECLS

/*
 * WARNING: these definitions must match <arm/syspage.h>
 *          We cannot directly include that file due to name space pollution.
 */
extern unsigned		__cpu_flags;
#ifndef __ARM_CPU_FLAG_V6
#define __ARM_CPU_FLAG_V6	0x0002u
#endif
#ifndef __ARM_CPU_FLAG_V7
#define __ARM_CPU_FLAG_V7	0x0020u
#endif
#ifndef __ARM_CPU_FLAG_SMP
#define __ARM_CPU_FLAG_SMP	0x0008u
#endif

#ifndef __KERCPU_H
static __inline__ void __attribute__((__unused__))
	__inline_InterruptEnable(void)
{
	if (__cpu_flags & __ARM_CPU_FLAG_V6) {
		__asm__ __volatile__("cpsie	i");
	} else {
		unsigned	__tmp;

		__asm__ __volatile__(
		  "mrs	%0, cpsr;"
		  "bic	%0, %0, #0x80;"
		  "msr	cpsr, %0;"
		  : "=r" (__tmp)
		);
	}
}

static __inline__ void __attribute__((__unused__))
	__inline_InterruptDisable(void)
{
	if (__cpu_flags & __ARM_CPU_FLAG_V6) {
		__asm__ __volatile__("cpsid	i");
	} else {
		unsigned	__tmp;

		__asm__ __volatile__(
		  "mrs	%0, cpsr;"
		  "orr	%0, %0, #0x80;"
		  "msr	cpsr, %0;"
		  : "=r" (__tmp)
		);
	}
}

static __inline__ void __attribute__((__unused__))
	__inline_InterruptLock(struct intrspin *__spin)
{
	__inline_InterruptDisable();
	if (__cpu_flags & __ARM_CPU_FLAG_SMP) {
		volatile unsigned	val;
		unsigned			tmp;
		__asm__ __volatile__(
			  "0:	ldrex	%0, [%3];"
			  "		teq		%0, #0;"
			  "		wfene;"
			  "		strexeq	%1, %2, [%3];"
			  "		teqeq	%1, #0;"
			  "		bne		0b;"
			  : "=&r" (val), "=&r"(tmp)
			  : "r" (1), "r" (&__spin->value)
		);
		if (__cpu_flags & __ARM_CPU_FLAG_V7) {
			__asm__ __volatile__("dmb");
		} else {
			__asm__ __volatile__("mcr	p15, 0, %0, c7, c10, 4" : : "r"(0));
		}
	}
}

static __inline__ void __attribute__((__unused__))
	__inline_InterruptUnlock(struct intrspin *__spin)
{
	if (__cpu_flags & __ARM_CPU_FLAG_SMP) {
		if (__cpu_flags & __ARM_CPU_FLAG_V7) {
			__asm__ __volatile__(
				"dmb;"
				"str	%0, [%1];"
				"dsb;"
				"sev"
				: : "r" (0), "r" (&(__spin)->value)
			);
		} else {
			__asm__ __volatile__(
				"mcr	p15, 0, %0, c7, c10, 5;"
				"str	%0, [%1];"
				"mcr	p15, 0, %0, c7, c10, 4;"
				"sev"
				: : "r" (0), "r" (&(__spin)->value)
			);
		}
	} else {
		__spin->value = 0;
	}
	__inline_InterruptEnable();
}
#endif

static __inline__ unsigned
(__inline_InterruptStatus)(void) {
	unsigned __val;
	__asm__ __volatile__( "mrs %0, cpsr" : "=&r" (__val));
	return (__val & 0x80)^0x80;
}

static __inline__ void __attribute__((__unused__))
	__inline_DebugBreak(void)
{
	/*
	 * WARNING: must match the breakpoint instruction used by gdb.
	 */
	__asm__ __volatile__(
		  "	.word	0xe7ffdefe"
		);
}

static __inline__ void __attribute__((__unused__))
	__inline_DebugKDBreak(void)
{
	__asm__ __volatile__(
		  "	.word	0xe7ffdeff"
		);
}


static __inline__ void __attribute__((__unused__))
	__inline_DebugKDOutput(const char *__text, _CSTD size_t __len)
{
	__asm__ __volatile__(
		  "	mov		r0, %0;"
		  "	mov		r1, %1;"
		  "	.word	0xe7ffffff"
		  :
		  : "r" (__text), "r" (__len)
		  : "r0", "r1"
		);
}

/*
 * ClockCycles must be emulated
 */
_Uint64t ClockCycles(void);

#define CLOCKCYCLES_INCR_BIT	0

__END_DECLS


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/SP1/services/system/public/arm/neutrino.h $ $Rev: 654987 $" )
