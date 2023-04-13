# Alternate Character Set

The terminal can be switched to and from its "Alternate Character Set" (ACS)
using escape sequences. The ACS traditionally contained box-drawing and other
semigraphic characters.

The characters in the ACS are configurable at runtime, by passing a wide string
to `tmt_open`. The default if none is provided (i.e. the argument is `NULL`)
uses ASCII characters to approximate the traditional characters.

The string passed to `tmt_open` must be 31 characters long. The characters,
and their default ASCII-safe values, are in order:

- RIGHT ARROW ">"
- LEFT ARROW "<"
- UP ARROW "^"
- DOWN ARROW "v"
- BLOCK "#"
- DIAMOND "+"
- CHECKERBOARD "#"
- DEGREE "o"
- PLUS/MINUS "+"
- BOARD ":"
- LOWER RIGHT CORNER "+"
- UPPER RIGHT CORNER "+"
- UPPER LEFT CORNER "+"
- LOWER LEFT CORNER "+"
- CROSS "+"
- SCAN LINE 1 "~"
- SCAN LINE 3 "-"
- HORIZONTAL LINE "-"
- SCAN LINE 7 "-"
- SCAN LINE 9 "_"
- LEFT TEE "+"
- RIGHT TEE "+"
- BOTTOM TEE "+"
- TOP TEE "+"
- VERTICAL LINE "|"
- LESS THAN OR EQUAL "<"
- GREATER THAN OR EQUAL ">"
- PI "*"
- NOT EQUAL "!"
- POUND STERLING "f"
- BULLET "o"

If your system's wide character type's character set corresponds to the
Universal Character Set (UCS/Unicode), the following wide string is a
good option to use:

    L"→←↑↓■◆▒°±▒┘┐┌└┼⎺───⎽├┤┴┬│≤≥π≠£•"

**Note that multibyte decoding is disabled in ACS mode.** The traditional
implementations of the "ansi" terminal type (i.e. IBM PCs and compatibles)
had no concept of multibyte encodings and used the character codes
outside the ASCII range for various special semigraphic characters.
(Technically they had an entire alternate character set as well via the
code page mechanism, but that's beyond the scope of this explanation.)

The end result is that the terminfo definition of "ansi" sends characters
with the high bit set when in ACS mode. This breaks several multibyte
encoding schemes (including, most importantly, UTF-8).

As a result, libtmt does not attempt to decode multibyte characters in
ACS mode, since that would break the multibyte encoding, the semigraphic
characters, or both.

In general this isn't a problem, since programs explicitly switch to and
from ACS mode using escape sequences.

When in ACS mode, bytes that are not special members of the alternate
character set (that is, bytes not mapped to the string provided to
`tmt_open`) are passed unchanged to the terminal.
