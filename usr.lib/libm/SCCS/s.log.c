h01114
s 00010/00005/00149
d D 5.3 88/06/30 17:45:23 bostic 9 8
c install approved copyright notice
e
s 00016/00013/00138
d D 5.2 88/04/29 12:41:56 bostic 8 7
c add Berkeley specific header
e
s 00000/00000/00151
d D 5.1 87/11/30 18:34:04 bostic 7 6
c tahoe release
e
s 00013/00013/00138
d D 1.6 87/07/13 19:20:42 zliu 6 5
c clean-ups.
e
s 00008/00004/00143
d D 1.5 87/07/10 10:36:30 zliu 5 4
c adding _0x macro for TAHOE.
e
s 00003/00003/00144
d D 1.4 87/07/07 01:32:00 zliu 4 3
c first shot at TAHOE.
e
s 00002/00002/00145
d D 1.3 86/03/16 19:08:44 elefunt 3 2
c All instances of "double static" got converted to "static double",
c as it should be.
e
s 00002/00001/00145
d D 1.2 85/09/11 23:54:20 elefunt 2 1
c 4.3BSD version dated 09/11/85.
e
s 00146/00000/00000
d D 1.1 85/09/06 17:52:58 zliu 1 0
c date and time created 85/09/06 17:52:58 by zliu
e
u
U
t
T
I 1
D 8
/* 
E 8
I 8
/*
E 8
 * Copyright (c) 1985 Regents of the University of California.
D 8
 * 
 * Use and reproduction of this software are granted  in  accordance  with
 * the terms and conditions specified in  the  Berkeley  Software  License
 * Agreement (in particular, this entails acknowledgement of the programs'
 * source, and inclusion of this notice) with the additional understanding
 * that  all  recipients  should regard themselves as participants  in  an
 * ongoing  research  project and hence should  feel  obligated  to report
 * their  experiences (good or bad) with these elementary function  codes,
 * using "sendbug 4bsd-bugs@BERKELEY", to the authors.
E 8
I 8
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 9
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
E 8
 */

#ifndef lint
D 2
static char sccsid[] = "%W% (ELEFUNT) %G%";
E 2
I 2
D 8
static char sccsid[] =
"%Z%%M%	4.5 (Berkeley) 8/21/85; %I% (ucb.elefunt) %G%";
E 2
D 6
#endif not lint
E 6
I 6
#endif	/* not lint */
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 6

/* LOG(X)
 * RETURN THE LOGARITHM OF x 
 * DOUBLE PRECISION (VAX D FORMAT 56 bits or IEEE DOUBLE 53 BITS)
 * CODED IN C BY K.C. NG, 1/19/85;
 * REVISED BY K.C. NG on 2/7/85, 3/7/85, 3/24/85, 4/16/85.
 *
 * Required system supported functions:
 *	scalb(x,n)
 *	copysign(x,y)
 *	logb(x)	
 *	finite(x)
 *
 * Required kernel function:
 *	log__L(z) 
 *
 * Method :
 *	1. Argument Reduction: find k and f such that 
 *			x = 2^k * (1+f), 
 *	   where  sqrt(2)/2 < 1+f < sqrt(2) .
 *
 *	2. Let s = f/(2+f) ; based on log(1+f) = log(1+s) - log(1-s)
 *		 = 2s + 2/3 s**3 + 2/5 s**5 + .....,
 *	   log(1+f) is computed by
 *
 *	     		log(1+f) = 2s + s*log__L(s*s)
 *	   where
 *		log__L(z) = z*(L1 + z*(L2 + z*(... (L6 + z*L7)...)))
 *
 *	   See log__L() for the values of the coefficients.
 *
 *	3. Finally,  log(x) = k*ln2 + log(1+f).  (Here n*ln2 will be stored
 *	   in two floating point number: n*ln2hi + n*ln2lo, n*ln2hi is exact
 *	   since the last 20 bits of ln2hi is 0.)
 *
 * Special cases:
 *	log(x) is NaN with signal if x < 0 (including -INF) ; 
 *	log(+INF) is +INF; log(0) is -INF with signal;
 *	log(NaN) is that NaN with no signal.
 *
 * Accuracy:
 *	log(x) returns the exact log(x) nearly rounded. In a test run with
 *	1,536,000 random arguments on a VAX, the maximum observed error was
 *	.826 ulps (units in the last place).
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following constants.
 * The decimal values may be used, provided that the compiler will convert
 * from decimal to binary accurately enough to produce the hexadecimal values
 * shown.
 */

D 4
#ifdef VAX	/* VAX D format */
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))	/* VAX D format */
E 6
I 6
#if defined(vax)||defined(tahoe)	/* VAX D format */
E 6
E 4
#include <errno.h>
D 5

E 5
I 5
D 6
#ifdef VAX
E 6
I 6
#ifdef vax
E 6
#define _0x(A,B)	0x/**/A/**/B
D 6
#else	/* VAX */
E 6
I 6
#else	/* vax */
E 6
#define _0x(A,B)	0x/**/B/**/A
D 6
#endif	/* VAX */
E 6
I 6
#endif	/* vax */
E 6
E 5
D 3
/* double static */
E 3
I 3
/* static double */
E 3
/* ln2hi  =  6.9314718055829871446E-1    , Hex  2^  0   *  .B17217F7D00000 */
/* ln2lo  =  1.6465949582897081279E-12   , Hex  2^-39   *  .E7BCD5E4F1D9CC */
/* sqrt2  =  1.4142135623730950622E0     ; Hex  2^  1   *  .B504F333F9DE65 */
D 5
static long     ln2hix[] = { 0x72174031, 0x0000f7d0};
static long     ln2lox[] = { 0xbcd52ce7, 0xd9cce4f1};
static long     sqrt2x[] = { 0x04f340b5, 0xde6533f9};
E 5
I 5
static long     ln2hix[] = { _0x(7217,4031), _0x(0000,f7d0)};
static long     ln2lox[] = { _0x(bcd5,2ce7), _0x(d9cc,e4f1)};
static long     sqrt2x[] = { _0x(04f3,40b5), _0x(de65,33f9)};
E 5
#define    ln2hi    (*(double*)ln2hix)
#define    ln2lo    (*(double*)ln2lox)
#define    sqrt2    (*(double*)sqrt2x)
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe)	*/
E 6
D 3
double static
E 3
I 3
static double
E 3
ln2hi  =  6.9314718036912381649E-1    , /*Hex  2^ -1   *  1.62E42FEE00000 */
ln2lo  =  1.9082149292705877000E-10   , /*Hex  2^-33   *  1.A39EF35793C76 */
sqrt2  =  1.4142135623730951455E0     ; /*Hex  2^  0   *  1.6A09E667F3BCD */
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe)	*/
E 6

double log(x)
double x;
{
	static double zero=0.0, negone= -1.0, half=1.0/2.0;
	double logb(),scalb(),copysign(),log__L(),s,z,t;
	int k,n,finite();

D 4
#ifndef VAX
E 4
I 4
D 6
#if (!defined(VAX)&&!defined(TAHOE))
E 6
I 6
#if !defined(vax)&&!defined(tahoe)
E 6
E 4
	if(x!=x) return(x);	/* x is NaN */
D 6
#endif
E 6
I 6
#endif	/* !defined(vax)&&!defined(tahoe) */
E 6
	if(finite(x)) {
	   if( x > zero ) {

	   /* argument reduction */
	      k=logb(x);   x=scalb(x,-k);
	      if(k == -1022) /* subnormal no. */
		   {n=logb(x); x=scalb(x,-n); k+=n;} 
	      if(x >= sqrt2 ) {k += 1; x *= half;}
	      x += negone ;

	   /* compute log(1+x)  */
              s=x/(2+x); t=x*x*half;
	      z=k*ln2lo+s*(t+log__L(s*s));
	      x += (z - t) ;

	      return(k*ln2hi+x);
	   }
	/* end of if (x > zero) */

	   else {
D 4
#ifdef VAX
E 4
I 4
D 6
#if (defined(VAX)||defined(TAHOE))
E 6
I 6
#if defined(vax)||defined(tahoe)
E 6
E 4
		extern double infnan();
		if ( x == zero )
		    return (infnan(-ERANGE));	/* -INF */
		else
		    return (infnan(EDOM));	/* NaN */
D 6
#else	/* IEEE double */
E 6
I 6
#else	/* defined(vax)||defined(tahoe) */
E 6
		/* zero argument, return -INF with signal */
		if ( x == zero )
		    return( negone/zero );

		/* negative argument, return NaN with signal */
		else 
		    return ( zero / zero );
D 6
#endif
E 6
I 6
#endif	/* defined(vax)||defined(tahoe) */
E 6
	    }
	}
    /* end of if (finite(x)) */
D 6
    /* NOT REACHED ifdef VAX */
E 6
I 6
    /* NOTREACHED if defined(vax)||defined(tahoe) */
E 6

    /* log(-INF) is NaN with signal */
	else if (x<0) 
	    return(zero/zero);      

    /* log(+INF) is +INF */
	else return(x);      

}
E 1
