h48166
s 00014/00003/00090
d D 5.4 88/06/18 14:43:20 bostic 5 4
c install approved copyright notice
e
s 00002/00001/00091
d D 5.3 87/09/21 11:48:03 bostic 4 2
c integrate with dm
e
s 00004/00001/00091
d R 5.3 87/09/19 17:10:54 bostic 3 2
c integrate with dm
e
s 00086/00017/00006
d D 5.2 87/06/03 13:55:02 bostic 2 1
c new template
e
s 00023/00000/00000
d D 5.1 87/06/03 13:47:40 bostic 1 0
c date and time created 87/06/03 13:47:40 by bostic
e
u
U
t
T
I 1
D 2
OBJS=		endgame.o extern.o getguess.o getword.o main.o playgame.o \
		prdata.o prman.o prword.o setup.o
CFILES=		endgame.c extern.c getguess.c getword.c main.c playgame.c \
		prdata.c prman.c prword.c setup.c
HDRS=		hangman.h
CFLAGS=		-O
LDFLAGS=	-g
E 2
I 2
#
# Copyright (c) 1987 Regents of the University of California.
D 5
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# All rights reserved.
E 5
#
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	%W% (Berkeley) %G%
E 5
#
CFLAGS=	-O
LIBC=	/lib/libc.a
LIBS=	-lcurses -ltermlib
SRCS=	endgame.c extern.c getguess.c getword.c main.c playgame.c \
	prdata.c prman.c prword.c setup.c
OBJS=	endgame.o extern.o getguess.o getword.o main.o playgame.o \
	prdata.o prman.o prword.o setup.o
E 2

all: hangman

D 2
tags: $(HDRS) $(CFILES)
	ctags $(HDRS) $(CFILES)
E 2
I 2
hangman: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS} ${LIBS}
E 2

D 2
install: hangman
	install -s hangman $(DESTDIR)/usr/games/hangman
	
hangman: $(OBJS)
	$(CC) $(LDFLAGS) -o hangman $(OBJS) -lcurses -ltermlib
E 2
I 2
clean: FRC
	rm -f ${OBJS} core hangman
E 2

D 2
clean:
	rm -f $(OBJS) hangman ? core
E 2
I 2
depend: FRC
	mkdep ${CFLAGS} ${SRCS}
E 2

D 2
depend:
E 2
I 2
install: FRC
D 4
	install -s -o bin -g bin -m 755 hangman ${DESTDIR}/etc/hangman
E 4
I 4
	install -s -o games -g bin -m 700 hangman ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f hangman; ln -s dm hangman; chown games.bin hangman)
E 4

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

endgame.o: endgame.c hangman.h /usr/include/curses.h /usr/include/stdio.h
endgame.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
endgame.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
endgame.o: /usr/include/sys/types.h /usr/include/sys/stat.h
endgame.o: /usr/include/ctype.h /usr/include/signal.h
extern.o: extern.c hangman.h /usr/include/curses.h /usr/include/stdio.h
extern.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
extern.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
extern.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
extern.o: /usr/include/signal.h
getguess.o: getguess.c hangman.h /usr/include/curses.h /usr/include/stdio.h
getguess.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
getguess.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
getguess.o: /usr/include/sys/types.h /usr/include/sys/stat.h
getguess.o: /usr/include/ctype.h /usr/include/signal.h
getword.o: getword.c hangman.h /usr/include/curses.h /usr/include/stdio.h
getword.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
getword.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
getword.o: /usr/include/sys/types.h /usr/include/sys/stat.h
getword.o: /usr/include/ctype.h /usr/include/signal.h
main.o: main.c hangman.h /usr/include/curses.h /usr/include/stdio.h
main.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
main.o: /usr/include/signal.h
playgame.o: playgame.c hangman.h /usr/include/curses.h /usr/include/stdio.h
playgame.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
playgame.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
playgame.o: /usr/include/sys/types.h /usr/include/sys/stat.h
playgame.o: /usr/include/ctype.h /usr/include/signal.h
prdata.o: prdata.c hangman.h /usr/include/curses.h /usr/include/stdio.h
prdata.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
prdata.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
prdata.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
prdata.o: /usr/include/signal.h
prman.o: prman.c hangman.h /usr/include/curses.h /usr/include/stdio.h
prman.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
prman.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
prman.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
prman.o: /usr/include/signal.h
prword.o: prword.c hangman.h /usr/include/curses.h /usr/include/stdio.h
prword.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
prword.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
prword.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
prword.o: /usr/include/signal.h
setup.o: setup.c hangman.h /usr/include/curses.h /usr/include/stdio.h
setup.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
setup.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
setup.o: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/ctype.h
setup.o: /usr/include/signal.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
