# Compile-Time Options

There are two preprocessor macros that affect libtmt:

`TMT_INVALID_CHAR`

Define this to a wide-character. This character will be added to
the virtual display when an invalid multibyte character sequence
is encountered.

By default (if you don't define it as something else before compiling),
this is `((wchar_t)0xfffd)`, which is the codepoint for the Unicode
'REPLACEMENT CHARACTER'. Note that your system might not use Unicode,
and its wide-character type might not be able to store a constant as
large as `0xfffd`, in which case you'll want to use an alternative.

`TMT_HAS_WCWIDTH`

By default, libtmt uses only standard C99 features.  If you define
TMT_HAS_WCWIDTH before compiling, libtmt will use the POSIX `wcwidth`
function to detect combining characters.

Note that combining characters are still not handled particularly
well, regardless of whether this was defined. Also note that what
your C library's `wcwidth` considers a combining character and what
the written language in question considers one could be different.
