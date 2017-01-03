/*
 * Copyright (c) 1987 Regents of the University of California.
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

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)sprintf.c	5.5 (Berkeley) 6/27/88";
#endif /* LIBC_SCCS and not lint */

#include <stdio.h>

sprintf(str, fmt, args)
	char *str, *fmt;
	int args;
{
	FILE _strbuf;
	int len;

	_strbuf._flag = _IOWRT+_IOSTRG;
	_strbuf._ptr = str;
	_strbuf._cnt = 32767;
	len = _doprnt(fmt, &args, &_strbuf);
	*_strbuf._ptr = 0;
	return(len);
}
