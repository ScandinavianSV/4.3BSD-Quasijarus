h57277
s 00120/00000/00000
d D 4.1 83/06/27 14:23:06 sam 1 0
c date and time created 83/06/27 14:23:06 by sam
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif

#include <stdio.h>
#include "con.h"
abval(q)
{
	return (q>=0 ? q : -q);
}

xconv (xp)
{
	/* x position input is -2047 to +2047, output must be 0 to PAGSIZ*HORZRES */
	xp += 2048;
	/* the computation is newx = xp*(PAGSIZ*HORZRES)/4096 */
	return (xoffset + xp /xscale);
}

yconv (yp)
{
	/* see description of xconv */
	yp += 2048;
	return (yp / yscale);
}

inplot()
{
	spew (ESC);
	spew(PLOTIN);
}

outplot()
{
	spew(ESC);
	spew(PLOTOUT);
	fflush(stdout);
}

spew(ch)
{
	if(ch == UP){
		putc(ESC,stdout);
		ch = DOWN;
	}
	putc(ch, stdout);
}

tobotleft ()
{
	move(-2048,-2048);
}
reset()
{
	signal(2,1);
	outplot();
	stty(OUTF,&ITTY);
	exit();
}

float
dist2 (x1, y1, x2, y2)
{
	float t,v;
	t = x2-x1;
	v = y1-y2;
	return (t*t+v*v);
}

swap (pa, pb)
int *pa, *pb;
{
	int t;
	t = *pa;
	*pa = *pb;
	*pb = t;
}
movep (xg,yg)
{
	int i,ch;
	if((xg == xnow) && (yg == ynow))return;
	/* if we need to go to left margin, just CR */
	if (xg < xnow/2)
	{
		spew(CR);
		xnow = 0;
	}
	i = (xg-xnow)/HORZRES;
	if(xnow < xg)ch = RIGHT;
	else ch = LEFT;
	xnow += i*HORZRES;
	i = abval(i);
	while(i--)spew(ch);
	i = abval(xg-xnow);
	inplot();
	while(i--) spew(ch);
	outplot();
	i=(yg-ynow)/VERTRES;
	if(ynow < yg)ch = UP;
	else ch = DOWN;
	ynow += i*VERTRES;
	i = abval(i);
	while(i--)spew(ch);
	i=abval(yg-ynow);
	inplot();
	while(i--)spew(ch);
	outplot();
	xnow = xg; ynow = yg;
}

xsc(xi){
	int xa;
	xa = (xi - obotx) * scalex + botx;
	return(xa);
}
ysc(yi){
	int ya;
	ya = (yi - oboty) *scaley +boty;
	return(ya);
}
E 1