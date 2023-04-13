# Special Keys

To send special keys to a program that is using libtmt for its display,
write one of the `TMT_KEY_*` strings to that program's standard input
(*not* to libtmt; it makes no sense to send any of these constants to
libtmt itself).

The following macros are defined, and are all constant strings:

- TMT_KEY_UP
- TMT_KEY_DOWN
- TMT_KEY_RIGHT
- TMT_KEY_LEFT
- TMT_KEY_HOME
- TMT_KEY_END
- TMT_KEY_INSERT
- TMT_KEY_BACKSPACE
- TMT_KEY_ESCAPE
- TMT_KEY_BACK_TAB
- TMT_KEY_PAGE_UP
- TMT_KEY_PAGE_DOWN
- TMT_KEY_F1 through TMT_KEY_F10

Note also that the classic PC console sent the enter key as
a carriage return, not a linefeed. Many programs don't care,
but some do.
