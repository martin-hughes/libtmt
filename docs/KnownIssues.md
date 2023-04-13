# Known Issues

Please feel free to work on any of these!

- Combining characters are "handled" by ignoring them
  (when compiled with `TMT_HAS_WCWIDTH`) or by printing them separately.
- Double-width characters are rendered as single-width invalid
  characters.
- The documentation and error messages are available only in English.
