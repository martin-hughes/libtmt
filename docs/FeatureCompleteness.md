# Feature Completeness List

These tables show the complete list of capabilities defined in the terminfo
entry for `ansi` terminals. They also shows whether libtmt currently
implements that feature, and whether it is tested or not.

## Supported Capabilities

> See [features not tested](#features-not-tested) for limitations that might 
> apply even where a capability is described as 'tested'.

| Feature code | Keycode / value      | Tested             | Description                                        | Notes                                                                                                                                                                   |
|--------------|----------------------|--------------------|----------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| am           | n/a                  | :x:                | Automatic margin support                           | Partially tested, but with no specific tests                                                                                                                            |
| mc5i         | n/a                  |                    | Printer output will not display on screen          |                                                                                                                                                                         |
| mir          | n/a                  |                    | Safe to move in insert mode                        |                                                                                                                                                                         |
| msgr         | n/a                  |                    | Safe to move in standout mode                      |                                                                                                                                                                         |
| colors       | 8                    | :white_check_mark: | Number of supported colours                        |                                                                                                                                                                         |
| cols         | 80                   | n/a                | Number of columns in the terminal                  | libtmt allows any number of columns                                                                                                                                     |
| it           | 8                    |                    | Tabs initially every 'n' spaces                    |                                                                                                                                                                         |
| lines        | 24                   | n/a                | Number of lines in the terminal                    | libtmt allows any number of lines in a terminal                                                                                                                         |
| ncv          | 3                    |                    | No colour video                                    |                                                                                                                                                                         |
| pairs        | 64                   | :x:                | Maximum number of colour pairs displayed at a time | 64 (8 times 8) means any foreground/background pair is permissible. Not explicitly tested, but very likely to work.                                                     |
| acsc         | see notes            | :x:                | Supported alternate character set                  | terminfo specifies +\020\,\021-\030.^Y0\333`\004a\261f\370g\361h\260j\331k\277l\332m\300n\305o~p\304q\304r\304s_t\303u\264v\301w\302x\263y\363z\362{\343\330}\234~\376, |
| bel          | ^G / \x07            | :white_check_mark: | Terminal Bell                                      | Supported by the callback function                                                                                                                                      |
| blink        | \E[5m                | :white_check_mark: | Blinking text                                      | Note 1                                                                                                                                                                  |
| bold         | \E[1m                | :white_check_mark: | Bold text                                          | Note 1                                                                                                                                                                  |
| cbt          | \E[Z                 | :x:                | Back tab                                           |                                                                                                                                                                         |
| clear        | \E[H\E[J             | :x:                | Clear screen and home cursor                       |                                                                                                                                                                         |
| cr           | \r                   | :x:                | Carriage return                                    |                                                                                                                                                                         |
| cub          | \E[%p1%dD            | :x:                | Move cursor P1 places to the left                  |                                                                                                                                                                         |
| cub1 / kcub1 | \E[D                 | :x:                | Move cursor 1 place to the left                    |                                                                                                                                                                         |
| cud          | \E[%p1%dB            | :x:                | Move cursor P1 places down                         |                                                                                                                                                                         |
| cud1 / kcud1 | \E[B                 | :x:                | Move cursor 1 place down                           |                                                                                                                                                                         |
| cuf          | \E[%p1%dC            | :x:                | Move cursor P1 places right                        |                                                                                                                                                                         |
| cuf1 / kcuf1 | \E[C                 | :x:                | Move cursor 1 place right                          |                                                                                                                                                                         |
| cup          | \E[%i%p1%d;%p2%dH    | :x:                | Move cursor to row P1, column P2                   | libtmt also supports lowercase f as the final character                                                                                                                 |
| cuu          | \E[%p1%dA            | :x:                | Move cursor P1 places up                           |                                                                                                                                                                         |
| cuu1 / kcuu1 | \E[A                 | :x:                | Move cursor 1 place up                             |                                                                                                                                                                         |
| dch          | \E[%p1%dP            | :x:                | Delete P1 characters from the cursor, to the right |                                                                                                                                                                         |
| dch1         | \E[P                 | :x:                | Delete 1 character at the cursor position          |                                                                                                                                                                         |
| dl           | \E[%p1%dM            | :x:                | Delete P1 lines                                    |                                                                                                                                                                         |
| dl1          | \E[M                 | :x:                | Delete 1 line                                      |                                                                                                                                                                         |
| ech          | \E[%p1%dX            | :white_check_mark: | Erase P1 characters                                |                                                                                                                                                                         |
| ed           | \E[J                 | :x:                | Clear to end of screen                             |                                                                                                                                                                         |
| el           | \E[K                 | :x:                | Clear to end of line                               | Note 2                                                                                                                                                                  |
| el1          | \E[1K                | :x:                | Clear to beginning of line                         | Note 2                                                                                                                                                                  |
| home /khome  | \E[H                 | :x:                | Move cursor to home                                |                                                                                                                                                                         |
| hpa          | \E[%i%p1%dG          | :x:                | Set cursor column                                  |                                                                                                                                                                         |
| ht           | \E[I                 | :x:                | Move to next tab                                   | Note 3                                                                                                                                                                  |
| hts          | \EH                  | :x:                | Set a tab in this column for all rows              | Note 3                                                                                                                                                                  |
| ich          | \E[%p1%d@            | :x:                | Insert character P1 times                          |                                                                                                                                                                         |
| il           | \E[%p1%dL            | :x:                | Insert P1 lines                                    |                                                                                                                                                                         |
| il1          | \E[L                 | :x:                | Insert 1 line                                      |                                                                                                                                                                         |
| ind          | \n                   | :x:                | Scroll forward 1 line                              |                                                                                                                                                                         |
| indn         | \E[%p1%dS            | :x:                | Scroll forward P1 lines                            |                                                                                                                                                                         |
| invis        | \E[8m                | :white_check_mark: | Invisible characters                               | Note 1                                                                                                                                                                  |
| kbs          | ^H / \x08            | :x:                | Backspace (doesn't delete character)               |                                                                                                                                                                         |
| kcbt         | \E[Z                 | :x:                | Back tab                                           | Note 3                                                                                                                                                                  |
| kich1        | \E[L                 | :x:                | Insert character                                   | I don't know why this and `il1` share a code                                                                                                                            |
| nel          | \r\E[S               | :x:                | Newline                                            |                                                                                                                                                                         |
| op           | \E[39;49m            | :white_check_mark: | Set default pair to original value                 | Note 1                                                                                                                                                                  |
| rep          | %p1%c\E[%p2%{1}%-%db | :x:                | Repeat char P1 a total of P2 times                 |                                                                                                                                                                         |
| rev          | \E[7m                | :x:                | Turn on reverse video                              | Note 1                                                                                                                                                                  |
| rin          | \E[%p1%dT            | :white_check_mark: | Scroll back P1 lines                               |                                                                                                                                                                         |
| rmacs        | \E[10m               | :x:                | Exit alternate character set mode                  | Note 4                                                                                                                                                                  |
| rmpch        | \E[10m               | :x:                | Exit PC character set mode                         | Note 4                                                                                                                                                                  |
| rmso         | \E[m                 | :white_check_mark: | Exit standout mode                                 | Note 1                                                                                                                                                                  |
| rmul         | \E[m                 | :white_check_mark: | Exit underline mode                                | Note 1                                                                                                                                                                  |
| setab        | \E[4%p1%dm           | :white_check_mark: | Set background colour                              | Note 1                                                                                                                                                                  |
| setaf        | \E[3%p1%dm           | :white_check_mark: | Set foreground colour                              | Note 1                                                                                                                                                                  |
| sgr          | (see below)          | :white_check_mark: | Set attributes                                     | Note 1                                                                                                                                                                  |
| sgr0         | \E[0;10m             | :x:                | Turn off all attributes                            | Note 1                                                                                                                                                                  |
| smacs        | \E[11m               | :x:                | Start alternate character set mode                 | Note 4                                                                                                                                                                  |
| smpch        | \E[11m               | :x:                | Start PC character set mode                        | Note 4                                                                                                                                                                  |
| smso         | \E[7m                | :white_check_mark: | Start standout mode                                | Note 1                                                                                                                                                                  |
| smul         | \E[4m                | :white_check_mark: | Start underline mode                               | Note 1                                                                                                                                                                  |
| tbc          | \E[3g                | :x:                | Clear all tabs                                     | Note 3                                                                                                                                                                  |
| u7           | \E[6n                | :x:                | User string 7                                      |                                                                                                                                                                         |
| u8           | \E[?%[;0123456789]c  | :x:                | User string 8                                      |                                                                                                                                                                         |
| u9           | \E[c                 | :x:                | User string 9                                      |                                                                                                                                                                         |
| vpa          | \E[%i%p1%dd          | :x:                | Set cursor to row P1                               |                                                                                                                                                                         |

Notes:

1. libtmt stores attributes, but since it doesn't render text to a graphical
    display the user is responsible for dealing with the stored attributes.
    Most tests for attributes are in the `sgr` capability test.

2. libtmt also supports `\E[2K`, which clears the entire line.

3. When tabs are in use, libtmt seems to fill the gaps with '*' characters.
    I'm unsure if this is the correct behaviour - still tbd.

4. libtmt only supports one alternate character set - ACS mode - but the user
    can specify the ACS character set to use.

The full keycode string for `sgr` is `\E[0;10%?%p1%t;7%;%?%p2%t;4%;%?%p3%t;7%;%?%p4%t;5%;%?%p6%t;1%;%?%p7%t;8%;%?%p9%t;11%;m,`

## Unsupported Features

| Feature code | Keycode / value | Description        | Notes                |
|--------------|-----------------|--------------------|----------------------|
| mc4          | \E[4i           | Turn off printer   | Deliberately skipped |
| mc5          | \E[5i           | Turn on printer    | Deliberately skipped |
| s0ds         | \E(B            | Shift to codeset 0 |                      |
| s1ds         | \E)B            | Shift to codeset 1 |                      |
| s2ds         | \E*B            | Shift to codeset 2 |                      |
| s3ds         | \E+B            | Shift to codeset 3 |                      |
| u6           | \E[%i%d;%dR     | User string 6      |                      |

## Other features supported by libtmt

These control codes are supported by libtmt but aren't listed in the terminfo
for ansi terminals.

Strictly speaking these don't belong in libtmt if it's aiming to match the
terminfo definition of `ansi`, but they will be left in unless they cause
problems - this minimizes the risk of unintended consequences.

| Keycode       | Description                                   |
|---------------|-----------------------------------------------|
| \E7 or \E[s   | Store cursor position and current attributes  |
| \E8 or \E[u   | Retrieve cursor position and saved attributes |
| \Ec           | Reset the terminal                            |
| \E[ P1 E      | Cursor down P1 rows, move to first col        |
| \E[ P1 F      | Cursor up P1 rows, move to first col          |
| \E[ P1, P2 f  | Cursor to (P1, P2)                            |
| \E[ P1 h      | Show cursor if P1 == 25                       |
| \E[ P1 l      | Hide cursor if P1 == 25                       |
| \E[2m / \E23m | Dim text set / unset.                         |

## Features not tested

Even where a capability is described as being tested, the following aspects
are not covered yet:

- Character attributes
- The callback function is not examined in all tests (this could be flakey as
    exactly when the callback is called is not specified so it could change.)
    It should still have sufficient coverage to be considered tested though.
- Multibyte characters
