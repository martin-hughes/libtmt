# Supported Input and Escape Sequences

Internally libtmt uses your C library's/compiler's idea of a wide character
for all characters, so you should be able to use whatever characters you want
when writing to the virtual terminal (but see
[Alternate Character Set](ACS.md)).

The following escape sequences are recognized and will be processed
specially.

In the descriptions below, "ESC" means a literal escape character and "Ps"
means zero or more decimal numeric arguments separated by semicolons.
In descriptions "P1", "P2", etc, refer to the first parameter, second
parameter, and so on.  If a required parameter is omitted, it defaults
to the smallest meaningful value (zero if the command accepts zero as
an argument, one otherwise).  Any number of parameters may be passed,
but any after the first eight are ignored.

Unless explicitly stated below, cursor motions past the edges of the screen
are ignored and do not result in scrolling.  When characters are moved,
the spaces left behind are filled with blanks and any characters moved
off the edges of the screen are lost.

| Sequence               | Action                                                                         |
|------------------------|--------------------------------------------------------------------------------|
| 0x07 (Bell)            | Callback with TMT_MSG_BELL                                                     |
| 0x08 (Backspace)       | Cursor left one cell                                                           |
| 0x09 (Tab)             | Cursor to next tab stop or end of line                                         |
| 0x0a (Carriage Return) | Cursor to first cell on this line                                              |
| 0x0d (Linefeed)        | Cursor to same column one line down, scroll if needed                          |
| ESC H                  | Set a tabstop in this column                                                   |
| ESC 7                  | Save cursor position and current graphical state                               |
| ESC 8                  | Restore saved cursor position and current graphical state                      |
| ESC c                  | Reset terminal to default state                                                |
| ESC [ Ps A             | Cursor up P1 rows                                                              |
| ESC [ Ps B             | Cursor down P1 rows                                                            |
| ESC [ Ps C             | Cursor right P1 columns                                                        |
| ESC [ Ps D             | Cursor left P1 columns                                                         |
| ESC [ Ps E             | Cursor to first column of line P1 rows down from current                       |
| ESC [ Ps F             | Cursor to first column of line P1 rows up from current                         |
| ESC [ Ps G             | Cursor to column P1                                                            |
| ESC [ Ps d             | Cursor to row P1                                                               |
| ESC [ Ps H             | Cursor to row P1, column P2                                                    |
| ESC [ Ps f             | Alias for ESC [ Ps H                                                           |
| ESC [ Ps I             | Cursor to next tab stop                                                        |
| ESC [ Ps J             | Clear screen                                                                   |
|                        | P1 == 0: from cursor to end of screen                                          |
|                        | P1 == 1: from beginning of screen to cursor                                    |
|                        | P1 == 2: entire screen                                                         |
| ESC [ Ps K             | Clear line                                                                     |
|                        | P1 == 0: from cursor to end of line                                            |
|                        | P1 == 1: from beginning of line to cursor                                      |
|                        | P1 == 2: entire line                                                           |
| ESC [ Ps L             | Insert P1 lines at cursor, scrolling lines below down                          |
| ESC [ Ps M             | Delete P1 lines at cursor, scrolling lines below up                            |
| ESC [ Ps P             | Delete P1 characters at cursor, moving characters to the right over            |
| ESC [ Ps S             | Scroll screen up P1 lines                                                      |
| ESC [ Ps T             | Scroll screen down P1 lines                                                    |
| ESC [ Ps X             | Erase P1 characters at cursor (overwrite with spaces)                          |
| ESC [ Ps Z             | Go to previous tab stop                                                        |
| ESC [ Ps b             | Repeat previous character P1 times                                             |
| ESC [ Ps c             | Callback with TMT_MSG_ANSWER "\033[?6c"                                        |
| ESC [ Ps g             | If P1 == 3, clear all tabstops                                                 |
| ESC [ Ps h             | If P1 == 25, show the cursor (if it was hidden)                                |
| ESC [ Ps m             | Change graphical rendition state; see below                                    |
| ESC [ Ps l             | If P1 == 25, hide the cursor                                                   |
| ESC [ Ps n             | If P1 == 6, callback with TMT_MSG_ANSWER "\033[%d;%dR" with cursor row, column |
| ESC [ Ps s             | Alias for ESC 7                                                                |
| ESC [ Ps u             | Alias for ESC 8                                                                |
| ESC [ Ps @             | Insert P1 blank spaces at cursor, moving characters to the right over          |

For the `ESC [ Ps m` escape sequence above ("Set Graphic Rendition"),
up to eight parameters may be passed; the results are cumulative:

| Rendition Code | Meaning                                           |
|----------------|---------------------------------------------------|
| 0              | Reset all graphic rendition attributes to default |
| 1              | Bold                                              |
| 2              | Dim (half bright)                                 |
| 4              | Underline                                         |
| 5              | Blink                                             |
| 7              | Reverse video                                     |
| 8              | Invisible                                         |
| 10             | Leave ACS mode                                    |
| 11             | Enter ACS mode                                    |
| 22             | Bold off                                          |
| 23             | Dim (half bright) off                             |
| 24             | Underline off                                     |
| 25             | Blink off                                         |
| 27             | Reverse video off                                 |
| 28             | Invisible off                                     |
| 30             | Foreground black                                  |
| 31             | Foreground red                                    |
| 32             | Foreground green                                  |
| 33             | Foreground yellow                                 |
| 34             | Foreground blue                                   |
| 35             | Foreground magenta                                |
| 36             | Foreground cyan                                   |
| 37             | Foreground white                                  |
| 39             | Foreground default color                          |
| 40             | Background black                                  |
| 41             | Background red                                    |
| 42             | Background green                                  |
| 43             | Background yellow                                 |
| 44             | Background blue                                   |
| 45             | Background magenta                                |
| 46             | Background cyan                                   |
| 47             | Background white                                  |
| 49             | Background default color                          |

Other escape sequences are recognized but ignored.  This includes escape
sequences for switching out codesets (officially, all code sets are defined
as equivalent in libtmt), and the various "Media Copy" escape sequences
used to print output on paper (officially, there is no printer attached
to libtmt).

Additionally, "?" characters are stripped out of escape sequence parameter
lists for compatibility purposes.
