h52988
s 00003/00003/00045
d D 5.2 2013/01/19 22:02:33 msokolov 2 1
c mjdtime.h declares sexatime() as returning void
c PDP-11 back-portability nitpick
e
s 00048/00000/00000
d D 5.1 2012/06/20 02:36:34 msokolov 1 0
c date and time created 2012/06/20 02:36:34 by msokolov
e
u
U
t
T
I 1
/*
 * Sexatime - break time-of-day into Sumerian sexagesimal HH:MM:SS
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (IFCTF) %E%";
#endif LIBC_SCCS and not lint

#include <sys/types.h>
#include <mjdtime.h>

/*
 * Thankfully, we are using the good K&R C, not the Nazi^H^H^H^HANSI kind,
 * hence we have the freedom to declare the tod argument internally
 * as whatever type we like without impacting our users, as long as
 * it's the same number of bits.  The valid range of 0-86399 fits into
 * both signed and unsigned long types.
 *
 * Our choice of C type here should be guided by whichever would
 * yield more efficient machine code for the expensive radix-splitting
 * division and modulo operations.  On DEC PDP-11 and VAX architectures
 * we definitely want the signed long here, not u_long.
 *
 * Modulo tends to be a very inefficient operation.  On the VAX it is
 * normally computed by performing a division, then multiplying the
 * quotient result by the divisor and subtracting that product from
 * the original dividend - whew!  Comments in the pcc source say
 * that the EDIV instruction (the only VAX division instruction that yields
 * a remainder "natively") is even slower than this sequence on every
 * known VAX implementation.
 *
 * Since no machine known to this author that is likely to run this code
 * has a way to compute modulo any faster than via a div-mul-sub
 * sequence, we perform this sequence explicitly instead of relying
 * on the compiler to recognize that we are asking for both the quotient
 * and the remainder for the same {dividend,divisor} tuple.
 */

I 2
void
E 2
sexatime(tod, sexa)
	register long tod;
	register struct sexatime *sexa;
{
D 2
	sexa->hh = tod / 3600;
	tod -= sexa->hh * 3600;
E 2
I 2
	sexa->hh = tod / 3600L;
	tod -= sexa->hh * 3600L;	/* the L would matter on a PDP-11! */
E 2
	sexa->mm = tod / 60;
	sexa->ss = tod - sexa->mm * 60;
D 2
	return 0;
E 2
}
E 1
