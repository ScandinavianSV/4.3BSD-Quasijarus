#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
#
#	@(#)makefile	3.2 (Berkeley) 3/28/88
#
# msdos versus unix defines
O	= .o
#PC_O	= .obj

X	=
#PC_X	= .exe

L	=
#PC_L	= -link

CC	= cc
#PC_CC	= cl

MV	= mv
#PC_MV	= rename

RM	= rm -f
#PC_RM= erase

LINT_ARGS =
#PC_LINT_ARGS = -DLINT_ARGS

DEBUG_FLAGS = -g
#PC_DEBUG_FLAGS = -Zi -Od

AR	= ar
AR1	= cr
AR2	=
AR3	=
#PC_AR	= lib
#PC_AR1	=
#PC_AR2	= +
#PC_AR3	= ";"

RANLIB	= ranlib
#PC_RANLIB = echo "Done with "

PRINT	= print

DEFINES = ${LINT_ARGS}

INCLUDES = -I.

OPTIMIZE = -O
OPTIMIZE = ${DEBUG_FLAGS}

CFLAGS	= $(OPTIMIZE) $(INCLUDES) $(DEFINES)

# Lint flags
LINTFLAGS	= -hbxaz

# Which keyboard are we emulating.
KBD	= 3180.kbd
KBD	= 3270pc.kbd
KBD	= unix.kbd

# The source files...
ALLH =	api.h function.h hostctlr.h inbound.ext oia.h \
	options.ext options.h outbound.ext screen.h scrnctlr.h

ALLC =	api.c function.c inbound.c oia.c options.c outbound.c

# Note: NO function.o!
ALLO =	api$O inbound$O oia$O options$O outbound$O

ALLPRINT =	3180.kbd 3270pc.kbd unix.kbd ${ALLH} ${ALLC}

ALLSOURCE =	${ALLPRINT} makefile makefile.mak

.s.o:
	/lib/cpp -E $< | as -o $@

.c.obj:
	${CC} ${CFLAGS} -c $<

ctlrlib.a:	${ALLO}
	${RM} $@
	for i in ${ALLO}; do (${AR} ${AR1} $@ ${AR2} $$i${AR3}); done
	${RANLIB} $@

clean:
	for i in $(ALLO) mset tn3270 prt3270 m4.out errs \
		makefile.bak ctlrlib.a kbd.out TMPfunc.out; \
			do (${RM} $$i); done

sccsclean:
	-sccs clean
	-sccs get makefile

sourcelist:	${ALLSOURCE}
	@for i in ${ALLSOURCE}; \
		do (echo ${DIRPATH}$$i); done

print:
	${PRINT} ${ALLPRINT}

tags:	${ALLC} ${ALLH}
	ctags -t ${ALLC} ${ALLH}

action:
	${ACTION}

lint:
	lint ${LINTFLAGS} ${INCLUDES} ${DEFINES} -DTN3270 ${ALLC} -lcurses

.DEFAULT:
	sccs get $<

kbd.out:	$(KBD) hostctlr.h
	(cd ../tools; make mkhits$X )
	${RM} $@ TMPfunc.out
	$(CC) $(CFLAGS) -E function.c > TMPfunc.out
	../tools/mkhits - ../ctlr/TMPfunc.out < $(KBD) > $@
	${RM} TMPfunc.out

depend:
	grep '^#include' ${ALLC} | grep -v '<' | \
	sed -e 's/:[^"]*"\([^"]*\)".*/: \1/' \
	    -e 's/\.c/$$O/' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '$$r makedep' >>eddep
	echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	-rm -f makefile.bak
	cp makefile makefile.bak
	ed - makefile < eddep
	rm eddep makedep

# DO NOT DELETE THIS LINE

api$O: api.h ../general/general.h ../api/disp_asc.h screen.h oia.h
api$O: ../general/globals.h
function$O: function.h
inbound$O: ../general/general.h function.h hostctlr.h oia.h scrnctlr.h screen.h
inbound$O: options.h ../api/dctype.h ../api/ebc_disp.h ../general/globals.h
inbound$O: inbound.ext outbound.ext ../telnet.ext kbd.out
oia$O: ../general/general.h oia.h ../general/globals.h
options$O: options.h ../general/globals.h options.ext
outbound$O: ../general/general.h hostctlr.h oia.h screen.h ../api/ebc_disp.h
outbound$O: ../general/globals.h options.ext ../telnet.ext inbound.ext
outbound$O: outbound.ext ../general/bsubs.ext
