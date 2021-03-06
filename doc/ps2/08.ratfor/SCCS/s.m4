h40260
s 00000/00000/00136
d D 6.1 86/04/29 21:34:11 cuccia 3 2
c document for 4.3BSD release
e
s 00000/00000/00136
d D 5.1 86/04/29 21:34:05 cuccia 2 1
c document distributed with 4.2BSD
e
s 00136/00000/00000
d D 4.1 86/04/29 21:33:59 cuccia 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
.\"	%W% (Berkeley) %G%
.\"
.NH
EXPERIENCE
.SH
Good Things
.PP
``It's
so much better than Fortran''
is the most common response of users
when asked how well
Ratfor
meets their needs.
Although cynics might consider this to be vacuous,
it does seem to be true that 
decent control flow and cosmetics converts Fortran
from a bad language into quite a reasonable one,
assuming that Fortran data structures are adequate
for the task at hand.
.PP
Although there are no quantitative results,
users feel that coding in
Ratfor
is at least twice as fast as in Fortran.
More important, debugging and subsequent revision
are much faster than in Fortran.
Partly this is simply because the code can be
.ul
read.
The looping statements
which test at the top instead of the bottom
seem to eliminate or at least
reduce the occurrence of a wide class of
boundary errors.
And of course it is easy to do structured programming in 
Ratfor;
this self-discipline also contributes
markedly to reliability.
.PP
One interesting and encouraging fact is that
programs written in
Ratfor
tend to be as readable as programs
written in more modern languages
like Pascal.
Once one is freed from the shackles of Fortran's
clerical detail and rigid input format,
it is easy to write code that is readable, even esthetically pleasing.
For example,
here is a
Ratfor
implementation of the linear table search discussed by
Knuth [7]:
.P1
A(m+1) = x
for (i = 1; A(i) != x; i = i + 1)
	;
if (i > m) {
	m = i
	B(i) = 1
}
else
	B(i) = B(i) + 1
.P2
A large corpus (5400 lines) of Ratfor, including a subset of
the Ratfor preprocessor itself,
can be found in
[8].
.SH
Bad Things
.PP
The biggest single problem is that many Fortran syntax errors
are not detected by
Ratfor
but by the local Fortran compiler.
The compiler then prints a message
in terms of the generated Fortran,
and in a few cases this may be difficult
to relate back to the offending
Ratfor
line,
especially if the implementation conceals the generated Fortran.
This problem could be dealt with
by tagging each generated line with some indication
of the source line that created it,
but this is inherently implementation-dependent,
so no action has yet been taken.
Error message interpretation
is actually not so arduous as might be thought.
Since Ratfor generates no variables,
only a simple pattern of
.UC IF 's
and
.UC GOTO 's,
data-related errors like missing
.UC DIMENSION
statements
are easy to find in the Fortran.
Furthermore, there has been a steady improvement
in Ratfor's ability to catch trivial syntactic
errors like unbalanced parentheses and quotes.
.PP
There are a number of implementation weaknesses
that are a nuisance, especially to new users.
For example,
keywords are reserved.
This rarely makes any difference, except for those hardy souls
who want to use an Arithmetic 
.UC IF .
A few standard Fortran
constructions are not accepted by 
Ratfor,
and this is perceived as a problem by users with a large corpus
of existing Fortran programs.
Protecting every line with a `%' is not really a
complete solution, although it serves as a stop-gap.
The best long-term solution is provided by the program
Struct [9],
which converts arbitrary Fortran programs into Ratfor.
.PP
Users who export programs often complain that the generated Fortran is
``unreadable'' because it is not 
tastefully formatted and contains extraneous
.UC CONTINUE
statements.
To some extent this can be ameliorated
(Ratfor now has an option to copy Ratfor comments into
the generated Fortran),
but it has always seemed that effort is better spent
on the input language than on the output esthetics.
.PP
One final problem is partly attributable to success _
since Ratfor is relatively easy to modify,
there are now several dialects of Ratfor.
Fortunately, so far most of the differences are in character set,
or in invisible aspects like code generation.
E 1
