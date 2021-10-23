#ifndef _VTCONSOLE_H_
#define _VTCONSOLE_H_ 1
#include <stddef.h>

#define VTCONSOLE_COLOR_BLACK   0
#define VTCONSOLE_COLOR_RED     1
#define VTCONSOLE_COLOR_GREEN   2
#define VTCONSOLE_COLOR_YELLOW  3
#define VTCONSOLE_COLOR_BLUE    4
#define VTCONSOLE_COLOR_MAGENTA 5
#define VTCONSOLE_COLOR_CYAN    6
#define VTCONSOLE_COLOR_GRAY    7

#define VTCONSOLE_FLAG_BOLD     (1 << 0)
#define VTCONSOLE_FLAG_ITALIC   (1 << 1)
#define VTCONSOLE_FLAG_UNDERL   (1 << 2)
#define VTCONSOLE_FLAG_SLOWBLNK (1 << 3)
#define VTCONSOLE_FLAG_FASTBLNK (1 << 4)
#define VTCONSOLE_FLAG_INVERT   (1 << 5)
#define VTCONSOLE_FLAG_STRIKE   (1 << 6)

#define VTCONSOLE_PARSER_STACK  8

#define VTCONSOLE_STATE_ESCAPE  0
#define VTCONSOLE_STATE_BRACKET 1
#define VTCONSOLE_STATE_ATTRIB  2
#define VTCONSOLE_STATE_ENDVAL  3

struct vtconsole_parser {
    int priv;
    int state;
    int stack_pos;
    int stack[VTCONSOLE_PARSER_STACK];
    int stack_map[VTCONSOLE_PARSER_STACK];
};

struct vtconsole_attrib {
    int flags;
    int back, fore;
};

struct vtconsole_cell {
    int ch;
    struct vtconsole_attrib attrib;
};

struct vtconsole_cursor {
    int x, y;
};

struct vtconsole;
typedef void(*vtconsole_cursor_handler_t)(struct vtconsole *vt, const struct vtconsole_cursor *cursor);
typedef void(*vtconsole_paint_handler_t)(struct vtconsole *vt, const struct vtconsole_cell *cell, int x, int y);
typedef void(*vtconsole_misc_csi_handler_t)(struct vtconsole *vt, int c);

struct vtconsole {
    int width, height;
    struct vtconsole_attrib attrib;
    struct vtconsole_parser parser;
    struct vtconsole_cell *buffer;
    struct vtconsole_cursor cursor;
    vtconsole_cursor_handler_t on_cursor;
    vtconsole_paint_handler_t on_paint;
    vtconsole_misc_csi_handler_t on_misc_csi;
};

void init_vtconsole(struct vtconsole *vt, int width, int height, vtconsole_cursor_handler_t on_cursor, vtconsole_paint_handler_t on_paint, vtconsole_misc_csi_handler_t on_misc_csi);
void shutdown_vtconsole(struct vtconsole *vt);
int vtconsole_write(struct vtconsole *vt, const void *s, size_t n);

#endif
