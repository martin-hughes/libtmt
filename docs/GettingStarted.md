# Getting Started

- [What is libtmt?](#what-is-libtmt)
- [What can libtmt be used for?](#what-can-libtmt-be-used-for)
- [Adding libtmt to your project](#adding-libtmt-to-your-project)
- [Using libtmt](#using-libtmt)

## What is libtmt?

First, what is a terminal? Traditionally, it's a device that has a keyboard and
screen and is attached to a computer via a serial (or similar) interface. When
the user presses keys they are transmitted to the computer, which responds with
a string of characters to display.

The terminal then displays those characters on its screen. Some sequences of
characters control how the terminal works, so the terminal interprets those as
part of its job of displaying what it receives.

libtmt is a *Tiny Mock Terminal*. It receives the same strings of characters as
a real terminal, but instead of displaying them directly on a screen, it stores
them in a buffer internally. That buffer can be thought of as a virtual
terminal screen. libtmt does the same parsing of control sequences as a real
terminal, placing characters in the right places in its buffer.

You, the user, can then do what you need with the contents.

libtmt aims to be - as far as possible - an ansi terminal. There isn't, as far
as this author can tell, a single defintion of an ansi terminal. Therefore,
libtmt aims to match the definition given by `terminfo`, as that is probably
the most widely used set of terminal definitions used anywhere.

## What can libtmt be used for?

Anywhere you need a virtual terminal is a candidate for libtmt. Some examples

- If you're writing a replacement for `xterm`
- Hobby kernel or IoT device code where you want a terminal like-experience
- The [`mtm` terminal multiplexer](https://github.com/deadpixi/mtm)

## Adding libtmt to your project

You have two options:

1.  The simplest way is to just copy `tmt.c` and `tmt.h` to your project.
    Include `tmt.h` as needed. This has the disadvantage that you can't
    automatically keep up to date with fixes, etc.
2.  Use CMake's `FindLibrary` functionality to include libtmt in a CMake-based
    project.

In both cases, see the available [compiler options](CompilerOptions.md).

## Using libtmt

The following sample shows the basic libtmt functions. You can see in the
definition of `callback` how to read the contents of the mock terminal. There's
no need to wait for a callback though, you can use `tmt_screen()` anywhere in
your program to get the `TMTSCREEN` pointer that contains the current state of
the mock terminal.

> Note: if you're using libtmt in a C++-based project, you may need to add
> `extern "C"` wrappers around `#include "tmt.h"`

```c
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
            /* the screen image changed; a is a pointer to the TMTSCREEN.
             * Instead of writing out lots of details here, a real application
             * would probably do something more useful, like updating a display
             */
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
```