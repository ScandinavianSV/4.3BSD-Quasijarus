h54046
s 00009/00002/00008
d D 5.2 85/04/30 16:15:35 dist 3 2
c add copyright
e
s 00001/00001/00009
d D 5.1 85/04/30 15:44:04 dist 2 1
c add copyright
e
s 00010/00000/00000
d D 4.1 83/11/10 11:03:11 ralph 1 0
c date and time created 83/11/10 11:03:11 by ralph
e
u
U
t
T
I 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

E 3
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 3
static char sccsid[] = "@(#)point.c	4.1 (Berkeley) 11/10/83";
E 2
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

E 3

point(xi, yi)
int xi, yi;
{
	move(xi, yi);
	label(".");
}
E 1
