
============================================
libtmt - a simple terminal emulation library
============================================

libtmt is the Tiny Mock Terminal Library.  It provides emulation of a classic
smart text terminal, by maintaining an in-memory screen image.  Sending text
and command sequences to libtmt causes it to update this in-memory image,
which can then be examined and rendered however the user sees fit.

The imagined primary goal for libtmt is to for terminal emulators and
multiplexers; it provides the terminal emulation layer for the `mtm`_
terminal multiplexer, for example. Other uses include screen-scraping and
automated test harnesses.

This fork comes from deadpixi's original, which can be found `here`_. The main
aims of this fork are:

- to fix any outstanding bugs
- to provide assurance of correctness through testing
- to allow for easier inclusion in projects - initially as a CMake library
- to match as closely as reasonable the terminfo definition of an "ansi"
  terminal.

libtmt is similar in purpose to `libtsm`_, but considerably smaller (500
lines versus 6500 lines). libtmt is also, in this author's humble opinion,
considerably easier to use.

.. _`here`: https://github.com/deadpixi/libtmt
.. _`mtm`: https://github.com/deadpixi/mtm
.. _`libtsm`: https://www.freedesktop.org/wiki/Software/kmscon/libtsm/

Status
======

This library is essentially finalised. I don't have any work I plan to do on
it in the near future. There are a few areas that aren't necessarily perfect,
but I don't plan to work on them until someone needs me to.

These are:

- Seeing how well the CMake Library make system works
- Testing alternate character sets
- Adding more in depth testing that character attributes are handled properly
  (I think they are, but some more testing would be nice)

As always though, feel free to add PRs or issues covering these or any other
things. I'll work on anything that comes up!

Documentation
=============

For full documentation, see the `docs folder <docs/Index.md>`_

Major Features and Advantages
=============================

Works Out-of-the-Box
    libtmt emulates a well-known terminal type (`ansi`), the definition of
    which has been in the terminfo database since at least 1995.  There's no
    need to install a custom terminfo entry.  There's no claiming to be an
    xterm but only emulating a small subset of its features. Any program
    using terminfo works automatically: this includes vim, emacs, mc,
    cmus, nano, nethack, ...

Portable
    Written in pure C99.
    Optionally, the POSIX-mandated `wcwidth` function can be used, which
    provides minimal support for combining characters.

Small
    Less than 500 lines of C, including comments and whitespace.

Free
    Released under a BSD-style license, free for commercial and
    non-commercial use, with no restrictions on source code release or
    redistribution.

Simple
    Only 8 functions to learn, and really you can get by with 6!

International
    libtmt internally uses wide characters exclusively, and uses your C
    library's multibyte encoding functions.
    This means that the library automatically supports any encoding that
    your operating system does.

Example Code
============

Below is a simple program fragment giving the flavor of libtmt.
Note that another good example is the `mtm`_ terminal multiplexer:

.. code:: c

    #include <stdio.h>
    #include <stdlib.h>
    #include "tmt.h"

    /* Forward declaration of a callback.
     * libtmt will call this function when the terminal's state changes.
     */
    void callback(tmt_msg_t m, TMT *vt, const void *a, void *p);

    int
    main(void)
    {
        /* Open a virtual terminal with 2 lines and 10 columns.
         * The first NULL is just a pointer that will be provided to the
         * callback; it can be anything. The second NULL specifies that
         * we want to use the default Alternate Character Set; this
         * could be a pointer to a wide string that has the desired
         * characters to be displayed when in ACS mode.
         */
        TMT *vt = tmt_open(2, 10, callback, NULL, NULL);
        if (!vt)
            return perror("could not allocate terminal"), EXIT_FAILURE;

        /* Write some text to the terminal, using escape sequences to
         * use a bold rendition.
         *
         * The final argument is the length of the input; 0 means that
         * libtmt will determine the length dynamically using strlen.
         */
        tmt_write(vt, "\033[1mhello, world (in bold!)\033[0m", 0);

        /* Writing input to the virtual terminal can (and in this case, did)
         * call the callback letting us know the screen was updated. See the
         * callback below to see how that works.
         */
        tmt_close(vt);
        return EXIT_SUCCESS;
    }

    void
    callback(tmt_msg_t m, TMT *vt, const void *a, void *p)
    {
        /* grab a pointer to the virtual screen */
        const TMTSCREEN *s = tmt_screen(vt);
        const TMTPOINT *c = tmt_cursor(vt);

        switch (m){
            case TMT_MSG_BELL:
                /* the terminal is requesting that we ring the bell/flash the
                 * screen/do whatever ^G is supposed to do; a is NULL
                 */
                printf("bing!\n");
                break;

            case TMT_MSG_UPDATE:
                /* the screen image changed; a is a pointer to the TMTSCREEN */
                for (size_t r = 0; r < s->nline; r++){
                    if (s->lines[r]->dirty){
                        for (size_t c = 0; c < s->ncol; c++){
                            printf("contents of %zd,%zd: %lc (%s bold)\n", r, c,
                                   s->lines[r]->chars[c].c,
                                   s->lines[r]->chars[c].a.bold? "is" : "is not");
                        }
                    }
                }

                /* let tmt know we've redrawn the screen */
                tmt_clean(vt);
                break;

            case TMT_MSG_ANSWER:
                /* the terminal has a response to give to the program; a is a
                 * pointer to a string */
                printf("terminal answered %s\n", (const char *)a);
                break;

            case TMT_MSG_MOVED:
                /* the cursor moved; a is a pointer to the cursor's TMTPOINT */
                printf("cursor is now at %zd,%zd\n", c->r, c->c);
                break;

            case TMT_MSG_CURSOR:
                /* the cursor's visibility changed; a is a pointer to a string
                 * containing "t" if the cursor should be visible, "f"
                 * otherwise. */
                if (((const char *)a)[0] == 't'){
                    printf("display cursor\n");
                } else{
                    printf("hide cursor\n");
                }
                break;
        }
    }
