h55262
s 00001/00001/00147
d D 7.3 02/08/31 12:38:49 msokolov 3 2
c (ccitt_addfcs16) bad check for when it's OK to append to the last mbuf
e
s 00001/00001/00147
d D 7.2 02/07/20 10:58:28 msokolov 2 1
c brown paper bag
e
s 00148/00000/00000
d D 7.1 02/07/12 19:47:38 msokolov 1 0
c date and time created 02/07/12 19:47:38 by msokolov
e
u
U
t
T
I 1
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
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
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Table and routines for CCITT FCS-16 calculation for interfaces that need to
 * do it in software.
 */

#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "errno.h"

#include "if.h"
#include "if_fcs16.h"

u_short ccitt_fcs16tab[256] = {
      0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
      0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
      0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
      0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
      0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
      0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
      0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
      0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
      0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
      0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
      0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
      0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
      0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
      0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
      0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
      0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
      0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
      0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
      0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
      0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
      0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
      0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
      0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
      0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
      0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
      0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
      0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
      0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
      0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
      0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
      0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
      0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

/* Append FCS to an mbuf chain */
ccitt_addfcs16(m)
	register struct mbuf *m;		/* r11 on vax */
{
	register u_long fcs;			/* r10 on vax */
	register char *cp;			/* r9 on vax */
	register int len;			/* r8 on vax */
	register u_short *table;		/* r7 on vax */
#ifdef vax
	register int r6 = 0;
#endif

	/* Calculate the FCS */
	fcs = CCITT_FCS16_INIT;
	table = ccitt_fcs16tab;
	while (1) {
		if (len = m->m_len) {
			cp = mtod(m, char *);
#ifdef vax
			asm("Lfcs1:	xorb3	(r9)+,r10,r6");
			asm("		ashl	$-8,r10,r10");
			asm("		xorw2	(r7)[r6],r10");
			asm("		sobgtr	r8,Lfcs1");
#else
			while (len--)
				fcs = (fcs >> 8) ^ table[(fcs ^ *cp++) & 0xff];
#endif
		}
		if (m->m_next == 0)
			break;
		m = m->m_next;
	}
	/* Invert it */
	fcs = fcs ^ 0xFFFF;
	/* Append it */
D 3
	if (m->m_off + m->m_len > MSIZE - 2) {
E 3
I 3
	if (M_HASCL(m) || m->m_off + m->m_len > MMAXOFF - 2) {
E 3
		struct mbuf *n;

		MGET(n, M_DONTWAIT, MT_HEADER);		/* trailer really... */
		if (n == 0)
			return(ENOBUFS);
		m->m_next = n;
		m = n;
		m->m_len = 0;
	}
D 2
	cp = mtod(m, char *);
E 2
I 2
	cp = mtod(m, char *) + m->m_len;
E 2
	*cp++ = fcs & 0xFF;
	*cp++ = fcs >> 8;
	m->m_len += 2;
	return(0);
}

/* Check an FCS-terminated block of data */
ccitt_fcs16check(buf, len)
	register char *buf;			/* r11 on vax */
	register int len;			/* r10 on vax */
{
	register u_long fcs;			/* r9 on vax */
	register u_short *table;		/* r8 on vax */
#ifdef vax
	register int r7 = 0;
#endif

	/* Calculate the FCS */
	fcs = CCITT_FCS16_INIT;
	table = ccitt_fcs16tab;
#ifdef vax
	asm("Lfcs2:	xorb3	(r11)+,r9,r7");
	asm("		ashl	$-8,r9,r9");
	asm("		xorw2	(r8)[r7],r9");
	asm("		sobgtr	r10,Lfcs2");
#else
	while (len--)
		fcs = (fcs >> 8) ^ table[(fcs ^ *buf++) & 0xff];
#endif
	/* Is it good? */
	if (fcs == CCITT_FCS16_GOOD)
		return(0);
	else
		return(-1);
}
E 1
