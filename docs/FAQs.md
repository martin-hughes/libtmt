Frequently Asked Questions
==========================

What programs work with libtmt?
-------------------------------

Pretty much all of them.  Any program that doesn't assume what terminal
it's running under should work without problem; this includes any program
that uses the terminfo, termcap, or (pd|n)?curses libraries.  Any program
that assumes it's running under some specific terminal might fail if its
assumption is wrong, and not just under libtmt.

I've tested quite a few applications in libtmt and they've worked flawlessly:
vim, GNU emacs, nano, cmus, mc (Midnight Commander), and others just work
with no changes.

What programs don't work with libtmt?
-------------------------------------

Breakage with libtmt is of two kinds: breakage due to assuming a terminal
type, and reduced functionality.

In all my testing, I only found one program that didn't work correctly by
default with libtmt: recent versions of Debian's
[apt](https://wiki.debian.org/Apt) assume a terminal with definable scrolling
regions to draw a fancy progress bar during package installation.  Using apt
in its default configuration in libtmt will result in a corrupted display
(that can be fixed by clearing the screen).

In my (Rob's) honest opinion, this is a bug in apt: it shouldn't assume the
type of terminal it's running in.

The second kind of breakage is when not all of a program's features are
available.  The biggest missing feature here is mouse support: libtmt
doesn't, and probably never will, support mouse tracking.  I know of many
programs that *can* use mouse tracking in a terminal, but I don't know
of any that *require* it.  Most (if not all?) programs of this kind would
still be completely usable in libtmt.
