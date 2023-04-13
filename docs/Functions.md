# Function reference

A brief description for all 8 functions in libtmt.

- [tmt_open()](#tmtopen)
- [tmt_close()](#tmtclose)
- [tmt_resize()](#tmtresize)
- [tmt_write()](#tmtwrite)
- [tmt_screen()](#tmtscreen)
- [tmt_cursor()](#tmtcursor)
- [tmt_clean()](#tmtclean)
- [tmt_reset()](#tmtreset)

## tmt_open()

`TMT *tmt_open(size_t nrows, size_t ncols, TMTCALLBACK cb, VOID *p, const wchar *acs);`

Creates a new virtual terminal, with `nrows` rows and `ncols` columns.
The callback `cb` will be called on updates, and passed `p` as a final
argument. See the definition of `tmt_msg_t` above for possible values
of each argument to the callback.

Terminals must have a size of at least two rows and two columns.

`acs` specifies the characters to use when in Alternate Character Set
(ACS) mode. The default string (used if `NULL` is specified) is:

     L"><^v#+:o##+++++~---_++++|<>*!fo"

See [Alternate Character Set](ACS.md) for more information.

Note that the callback must be ready to be called immediately, as
it will be called after initialization of the terminal is done, but
before the call to `tmt_open` returns.

## tmt_close()

`void tmt_close(TMT *vt)`

Close and free all resources associated with `vt`.

## tmt_resize()

`bool tmt_resize(TMT *vt, size_t nrows, size_t ncols)`

Resize the virtual terminal to have `nrows` rows and `ncols` columns.
The contents of the area in common between the two sizes will be preserved.

Terminals must have a size of at least two rows and two columns.

If this function returns false, the resize failed (only possible in
out-of-memory conditions or invalid sizes). If this happens, the terminal
is trashed and the only valid operation is the close the terminal.

## tmt_write()

`void tmt_write(TMT *vt, const char *s, size_t n)`

Write the provided string to the terminal, interpreting any escape
sequences contained therein, and update the screen image. The last
argument is the length of the input. If set to 0, the length is
determined using `strlen`.

The terminal's callback function may be invoked one or more times before
a call to this function returns.

The string is converted internally to a wide-character string using the
system's current multibyte encoding. Each terminal maintains a private
multibyte decoding state, and correctly handles multibyte characters that
span multiple calls to this function (that is, the final byte(s) of `s`
may be a partial multibyte character to be completed on the next call).

## tmt_screen()

`const TMTSCREEN *tmt_screen(const TMT *vt)`

Returns a pointer to the terminal's screen image.

## tmt_cursor()

`const TMTPOINT *tmt_cursor(const TMT *vt)`

Returns a pointer to the terminal's cursor position.

## tmt_clean()

`void tmt_clean(TMT *vt)`

Call this after receiving a `TMT_MSG_UPDATE` or `TMT_MSG_MOVED` callback
to let the library know that the program has handled all reported changes
to the screen image.

## tmt_reset()

`void tmt_reset(TMT *vt)`

Resets the virtual terminal to its default state (colors, multibyte
decoding state, rendition, etc).
