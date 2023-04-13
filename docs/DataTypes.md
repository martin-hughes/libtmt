# Data Types and Enumerations

A brief description of all data types used by libtmt

```c
/* an opaque structure */
typedef struct TMT TMT;

/* possible messages sent to the callback */
typedef enum{
    TMT_MSG_MOVED,  /* the cursor changed position       */
    TMT_MSG_UPDATE, /* the screen image changed          */
    TMT_MSG_ANSWER, /* the terminal responded to a query */
    TMT_MSG_BELL,   /* the terminal bell was rung        */
    TMT_MSG_CURSOR  /* the cursor visibility changed     */
} tmt_msg_T;

/* a callback for the library
 * m is one of the message constants above
 * vt is a pointer to the vt structure
 * r is NULL for TMT_MSG_BELL
 *   is a pointer to the cursor's TMTPOINT for TMT_MSG_MOVED
 *   is a pointer to the terminal's TMTSCREEN for TMT_MSG_UPDATE
 *   is a pointer to a string for TMT_MSG_ANSWER
 *   is a pointer to a string containing "t" or "f" for TMT_MSG_CURSOR
 * p is whatever was passed to tmt_open (see below).
 */
typedef void (*TMTCALLBACK)(tmt_msg_t m, struct TMT *vt,
                            const void *r, void *p);

/* color definitions */
typedef enum{
    TMT_COLOR_BLACK,
    TMT_COLOR_RED,
    TMT_COLOR_GREEN,
    TMT_COLOR_YELLOW,
    TMT_COLOR_BLUE,
    TMT_COLOR_MAGENTA,
    TMT_COLOR_CYAN,
    TMT_COLOR_WHITE,
    TMT_COLOR_DEFAULT /* whatever the host terminal wants it to mean */
} tmt_color_t;

/* graphical rendition */
typedef struct TMTATTRS TMTATTRS;
struct TMTATTRS{
    bool bold;      /* character is bold             */
    bool dim;       /* character is half-bright      */
    bool underline; /* character is underlined       */
    bool blink;     /* character is blinking         */
    bool reverse;   /* character is in reverse video */
    bool invisible; /* character is invisible        */
    tmt_color_t fg; /* character foreground color    */
    tmt_color_t bg; /* character background color    */
};

/* characters */
typedef struct TMTCHAR TMTCHAR;
struct TMTCHAR{
    wchar_t  c; /* the character */
    TMTATTRS a; /* its rendition */
};

/* a position on the screen; upper left corner is 0,0 */
typedef struct TMTPOINT TMTPOINT;
struct TMTPOINT{
    size_t r; /* row    */
    size_t c; /* column */
};

/* a line of characters on the screen;
 * every line is always as wide as the screen
 */
typedef struct TMTLINE TMTLINE;
struct TMTLINE{
    bool dirty;     /* line has changed since it was last drawn */
    TMTCHAR chars[];  /* the contents of the line                 */
};

/* a virtual terminal screen image */
typedef struct TMTSCREEN TMTSCREEN;
struct TMTSCREEN{
    size_t nline;    /* number of rows          */
    size_t ncol;     /* number of columns       */
    TMTLINE **lines; /* the lines on the screen */
};
```