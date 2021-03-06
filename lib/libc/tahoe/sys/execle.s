/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#if defined(SYSLIBC_SCCS) && !defined(lint)
	.asciz "@(#)execle.s	5.3 (Berkeley) 6/27/88"
#endif /* SYSLIBC_SCCS and not lint */

#include "SYS.h"

ENTRY(execle)
	movw	-2(fp),r0	# removed word.
	subw2	$4,r0
	shar	$2,r0,r0	# num. of args.
	pushl	(fp)[r0]
	pushab	8(fp)
	pushl	4(fp)
	calls	$16,_execve
	ret		# execle(file, arg1, arg2, ..., env);
