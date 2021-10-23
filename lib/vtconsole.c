#include <ctype.h>
#include <demos/km.h>
#include <string.h>
#include <vtconsole.h>

#define vtcallback_invoke(x, ...) do { (x)(__VA_ARGS__); break; } while(x)

static struct vtconsole_attrib default_attrib = {
    .flags = 0,
    .back = VTCONSOLE_COLOR_BLACK,
    .fore = VTCONSOLE_COLOR_GRAY
};

static void vt_clear(struct vtconsole *vt, int x0, int y0, int x1, int y1)
{
    int i, beg, end;
    struct vtconsole_cell *cell;
    beg = x0 + (y0 * vt->width);
    end = x1 + (y1 * vt->width);
    for(i = beg; i < end; i++) {
        cell = vt->buffer + i;
        cell->attrib = default_attrib;
        cell->ch = 0;
        vtcallback_invoke(vt->on_paint, vt, cell, i % vt->width, i / vt->width);
    }
}

static void vt_scroll(struct vtconsole *vt, int nl)
{
    int i, end_line, end_idx;
    struct vtconsole_cell *cell;

    if(nl > 0) {
        if(nl > vt->height)
            nl = vt->height;
        end_line = vt->height - nl;
        end_idx = vt->width * end_line;

        for(i = 0; i < end_idx; i++) {
            cell = vt->buffer + i;
            memcpy(cell, cell + vt->width, sizeof(struct vtconsole_cell));
            vtcallback_invoke(vt->on_paint, vt, cell, i % vt->width, i / vt->width);
        }

        for(i = 0; i < vt->width; i++) {
            cell = vt->buffer + i + end_idx;
            cell->attrib = default_attrib;
            cell->ch = 0;
            vtcallback_invoke(vt->on_paint, vt, cell, i, end_line);
        }

        vt->cursor.y -= nl;
        if(vt->cursor.y < 0)
            vt->cursor.y = 0;
        vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
    }
}

static void vt_newline(struct vtconsole *vt)
{
    vt->cursor.x = 0;
    vt->cursor.y++;

    if(vt->cursor.y == vt->height) {
        vt_scroll(vt, 1);
        return;
    }

    vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
}

static void vt_print(struct vtconsole *vt, int c)
{
    int i, scratch;
    struct vtconsole_cell *cell;
    switch(c) {
        case '\n':
            vt_newline(vt);
            break;
        case '\r':
            vt->cursor.x = 0;
            vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
            break;
        case '\t':
            scratch = 4 - (vt->cursor.x % 8);
            for(i = 0; i < scratch; i++)
                vt_print(vt, ' ');
            break;
        case '\b':
            if(vt->cursor.x >= 1) {
                vt->cursor.x--;
                vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
            }
            break;
        default:
            if(vt->cursor.x >= vt->width)
                vt_newline(vt);
            cell = vt->buffer + vt->cursor.x + (vt->cursor.y * vt->width);
            cell->attrib = vt->attrib;
            cell->ch = c;
            vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
            vtcallback_invoke(vt->on_paint, vt, cell, vt->cursor.x++, vt->cursor.y);
            break;
    }
}

/* Cursor X.
 * Moves the cursor. */
static void vt_csi_cux(struct vtconsole *vt, int dc)
{
    int attrib = vt->parser.stack[0];
    if(!vt->parser.stack_map[0] || !attrib)
        attrib = 1;
    int dir = (dc == 'B' || dc == 'C') ? 1 : -1;
    int *pp = (dc == 'A' || dc == 'B') ? &vt->cursor.y : &vt->cursor.x;
    int max = (dc == 'A' || dc == 'B') ? vt->height : vt->width;
    int val = *pp + dir * attrib;
    if(val < 0)
        val = 0;
    if(val > max)
        val = max;
    *pp = val;
    vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
}

/* Cursor position.
 * Moves the cursor. */
static void vt_csi_cup(struct vtconsole *vt)
{
    int x = 1, y = 1;
    if(vt->parser.stack_map[0] && vt->parser.stack[0])
        x = vt->parser.stack[0];
    if(vt->parser.stack_map[1] && vt->parser.stack[1])
        y = vt->parser.stack[1];
    if(x > vt->width)
        x = vt->width;
    if(y >= vt->height)
        y = vt->height;
    vt->cursor.x = x - 1;
    vt->cursor.y = y - 1;
    vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
}

/* Erase in Display.
 * Clears a part of the screen. */
static void vt_csi_ed(struct vtconsole *vt)
{
    int attrib = vt->parser.stack[0];
    if(!vt->parser.stack_map[0])
        attrib = 0;
    switch(attrib) {
        case 0:
            vt_clear(vt, vt->cursor.x, vt->cursor.y, vt->width, vt->height - 1);
            break;
        case 1:
            vt_clear(vt, 0, 0, vt->cursor.x, vt->cursor.y);
            break;
        case 2:
            vt_clear(vt, 0, 0, vt->width, vt->height - 1);
            break;
    }
}

/* Erase in Line.
 * Erases a part of the line. */
static void vt_csi_el(struct vtconsole *vt)
{
    int attrib = vt->parser.stack[0];
    if(!vt->parser.stack_map[0])
        attrib = 0;
    switch(attrib) {
        case 0:
            vt_clear(vt, vt->cursor.x, vt->cursor.y, vt->width, vt->cursor.y);
            break;
        case 1:
            vt_clear(vt, 0, vt->cursor.y, vt->cursor.x, vt->cursor.y);
            break;
        case 2:
            vt_clear(vt, 0, vt->cursor.y, vt->width, vt->cursor.y);
            break;
    }
}

/* Select Graphic Rendition.
 * Sets colors and style of the characters. */
static void vt_csi_sgr(struct vtconsole *vt)
{
    int i, attrib;
    for(i = 0; i < vt->parser.stack_pos; i++) {
        if(!vt->parser.stack_map[i] || !vt->parser.stack[i]) {
            vt->attrib = default_attrib;
            continue;
        }

        attrib = vt->parser.stack[i];

        switch(attrib) {
            case 1:
                vt->attrib.flags |= VTCONSOLE_FLAG_BOLD;
                continue;
            case 2:
                vt->attrib.flags &= ~VTCONSOLE_FLAG_BOLD;
                continue;
            case 3:
                vt->attrib.flags |= VTCONSOLE_FLAG_ITALIC;
                continue;
            case 4:
                vt->attrib.flags |= VTCONSOLE_FLAG_UNDERL;
                continue;
            case 5:
                vt->attrib.flags |= VTCONSOLE_FLAG_SLOWBLNK;
                vt->attrib.flags &= ~VTCONSOLE_FLAG_FASTBLNK;
                continue;
            case 6:
                vt->attrib.flags |= VTCONSOLE_FLAG_FASTBLNK;
                vt->attrib.flags &= ~VTCONSOLE_FLAG_SLOWBLNK;
                continue;
            case 7:
                vt->attrib.flags |= VTCONSOLE_FLAG_INVERT;
                continue;
            case 9:
                vt->attrib.flags |= VTCONSOLE_FLAG_STRIKE;
                continue;
        }

        switch(attrib / 10) {
            case 3:
                vt->attrib.fore = (attrib % 10) % 8;
                continue;
            case 4:
                vt->attrib.back = (attrib % 10) % 8;
                continue;
        }
    }
}

static void vtconsole_putchar(struct vtconsole *vt, int c)
{
    int attrib;

    if(vt->parser.state == VTCONSOLE_STATE_ESCAPE) {
        if(c != 033) {
            vt_print(vt, c);
            goto done;
        }

        vt->parser.state = VTCONSOLE_STATE_BRACKET;
        vt->parser.stack_pos = 0;
        vt->parser.stack[vt->parser.stack_pos] = 0;
        vt->parser.stack_map[vt->parser.stack_pos] = 0;
        goto done;
    }

    if(vt->parser.state == VTCONSOLE_STATE_BRACKET) {
        if(c != '[') {
            vt->parser.priv = 0;
            vt->parser.state = VTCONSOLE_STATE_ESCAPE;
            vt_print(vt, c);
            goto done;
        }

        vt->parser.state = VTCONSOLE_STATE_ATTRIB;
        goto done;
    }

    if(vt->parser.state == VTCONSOLE_STATE_ATTRIB) {
        if(c == '<' || c == '=' || c == '>' || c == '?') {
            vt->parser.priv = c;
            goto done;
        }

        if(isdigit(c)) {
            vt->parser.stack[vt->parser.stack_pos] *= 10;
            vt->parser.stack[vt->parser.stack_pos] += (c - '0');
            vt->parser.stack_map[vt->parser.stack_pos] = 1;
        }
        else {
            if(vt->parser.stack_pos < VTCONSOLE_PARSER_STACK)
                vt->parser.stack_pos++;
            vt->parser.stack[vt->parser.stack_pos] = 0;
            vt->parser.stack_map[vt->parser.stack_pos] = 0;
            vt->parser.state = VTCONSOLE_STATE_ENDVAL;
        }

        goto done;
    }

done:
    if(vt->parser.state == VTCONSOLE_STATE_ENDVAL) {
        if(c == ';') {
            vt->parser.state = VTCONSOLE_STATE_ATTRIB;
            return;
        }

        switch(c) {
            case 'A': case 'B': case 'C': case 'D':
                vt_csi_cux(vt, c);
                break;
            case 'E':
                vt_newline(vt);
                break;
            case 'G':
                attrib = vt->parser.stack[0];
                if(!vt->parser.stack_map[0] || !attrib)
                    attrib = 1;
                if(attrib >= vt->width)
                    attrib = vt->width - 1;
                vt->cursor.x = attrib;
                vtcallback_invoke(vt->on_cursor, vt, &vt->cursor);
                break;
            case 'H':
                vt_csi_cup(vt);
                break;
            case 'J':
                vt_csi_ed(vt);
                break;
            case 'K':
                vt_csi_el(vt);
                break;
            case 'T':
                attrib = vt->parser.stack[0];
                if(!vt->parser.stack_map[0] || !attrib)
                    attrib = 1;
                vt_scroll(vt, attrib);
                break;
            case 'm':
                vt_csi_sgr(vt);
                break;
            default:
                /* Allows different implementations to parse
                 * standard and private control sequences like
                 * VT220's 'cursor ops in VGA textmode driver. */
                vtcallback_invoke(vt->on_misc_csi, vt, c);
                break;
        }

        vt->parser.priv = 0;
        vt->parser.state = VTCONSOLE_STATE_ESCAPE;
        return;
    }
}

void init_vtconsole(struct vtconsole *vt, int width, int height, vtconsole_cursor_handler_t on_cursor, vtconsole_paint_handler_t on_paint, vtconsole_misc_csi_handler_t on_misc_csi)
{
    memset(vt, 0, sizeof(struct vtconsole));
    vt->width = width;
    vt->height = height;
    vt->attrib = default_attrib;
    vt->parser.priv = 0;
    vt->parser.state = VTCONSOLE_STATE_ESCAPE;
    vt->parser.stack_pos = 0;
    memset(vt->parser.stack, 0, sizeof(vt->parser.stack));
    memset(vt->parser.stack_map, 0, sizeof(vt->parser.stack_map));
    vt->buffer = kmalloc(sizeof(struct vtconsole_cell) * vt->width * vt->height);
    vt->cursor.x = 0;
    vt->cursor.y = 0;
    vt->on_cursor = on_cursor;
    vt->on_paint = on_paint;
    vt->on_misc_csi = on_misc_csi;
    vt_clear(vt, 0, 0, vt->width, vt->height - 1);
}

void shutdown_vtconsole(struct vtconsole *vt)
{
    kmfree(vt->buffer);
    memset(vt, 0, sizeof(struct vtconsole));
}

int vtconsole_write(struct vtconsole *vt, const void *s, size_t n)
{
    const char *sp = s;
    while(n--)
        vtconsole_putchar(vt, *sp++);
    return 1;
}
