/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "@(#)htons.s	5.1 (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/* hostorder = htons(netorder) */

#include "DEFS.h"

ENTRY(htons)
	clrl	d0
	movw	sp@(6),d0
	rts
