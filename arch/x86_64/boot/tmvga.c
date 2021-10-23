#include <arch/io.h>
#include <ctype.h>
#include <stivale2.h>
#include <string.h>
#include <vtconsole.h>

#define VGA_CSR_CURSOR_DISABLE (1 << 5)

#define VGA_CRTC_IO             0x3D4
#define VGA_CRTC_MAX_SCANLINE   0x09
#define VGA_CRTC_CURSOR_START   0x0A
#define VGA_CRTC_CURSOR_END     0x0B
#define VGA_CRTC_CURSOR_LOC_HI  0x0E
#define VGA_CRTC_CURSOR_LOC_LO  0x0F

#define VGA_COLOR_BLACK         0x00
#define VGA_COLOR_BLUE          0x01
#define VGA_COLOR_GREEN         0x02
#define VGA_COLOR_CYAN          0x03
#define VGA_COLOR_RED           0x04
#define VGA_COLOR_MAGENTA       0x05
#define VGA_COLOR_BROWN         0x06
#define VGA_COLOR_LIGHT_GRAY    0x07
#define VGA_COLOR_GRAY          0x08
#define VGA_COLOR_LIGHT_BLUE    0x09
#define VGA_COLOR_LIGHT_GREEN   0x0A
#define VGA_COLOR_LIGHT_CYAN    0x0B
#define VGA_COLOR_LIGHT_RED     0x0C
#define VGA_COLOR_LIGHT_MAGENTA 0x0D
#define VGA_COLOR_LIGHT_YELLOW  0x0E
#define VGA_COLOR_WHITE         0x0F

static struct vtconsole vt = { 0 };
static uint16_t *vidbuffer = NULL;

static const uint8_t colormap[8] = {
    [VTCONSOLE_COLOR_BLACK]     = VGA_COLOR_BLACK,
    [VTCONSOLE_COLOR_RED]       = VGA_COLOR_RED,
    [VTCONSOLE_COLOR_GREEN]     = VGA_COLOR_GREEN,
    [VTCONSOLE_COLOR_YELLOW]    = VGA_COLOR_BROWN,
    [VTCONSOLE_COLOR_BLUE]      = VGA_COLOR_BLUE,
    [VTCONSOLE_COLOR_MAGENTA]   = VGA_COLOR_MAGENTA,
    [VTCONSOLE_COLOR_CYAN]      = VGA_COLOR_CYAN,
    [VTCONSOLE_COLOR_GRAY]      = VGA_COLOR_LIGHT_GRAY
};

static const uint8_t colormap_b[8] = {
    [VTCONSOLE_COLOR_BLACK]     = VGA_COLOR_BLACK,
    [VTCONSOLE_COLOR_RED]       = VGA_COLOR_LIGHT_RED,
    [VTCONSOLE_COLOR_GREEN]     = VGA_COLOR_LIGHT_GREEN,
    [VTCONSOLE_COLOR_YELLOW]    = VGA_COLOR_LIGHT_YELLOW,
    [VTCONSOLE_COLOR_BLUE]      = VGA_COLOR_LIGHT_BLUE,
    [VTCONSOLE_COLOR_MAGENTA]   = VGA_COLOR_LIGHT_MAGENTA,
    [VTCONSOLE_COLOR_CYAN]      = VGA_COLOR_LIGHT_CYAN,
    [VTCONSOLE_COLOR_GRAY]      = VGA_COLOR_WHITE
};

static void paint_callback(struct vtconsole *vt, const struct vtconsole_cell *cell, int x, int y)
{
    const uint8_t *swap_colormap;
    const uint8_t *back_colormap = colormap;
    const uint8_t *fore_colormap = colormap;
    int back_idx, fore_idx;
    uint16_t word;

    if(cell->attrib.flags & VTCONSOLE_FLAG_BOLD)
        fore_colormap = colormap_b;

    if(cell->attrib.flags & VTCONSOLE_FLAG_INVERT) {
        swap_colormap = fore_colormap;
        fore_colormap = back_colormap;
        back_colormap = swap_colormap;
        fore_idx = cell->attrib.back;
        back_idx = cell->attrib.fore;
    }
    else {
        fore_idx = cell->attrib.fore;
        back_idx = cell->attrib.back;
    }

    word = 0;
    word |= (back_colormap[back_idx] & 0x0F) << 12;
    word |= (fore_colormap[fore_idx] & 0x0F) << 8;
    word |= (cell->ch & 0xFF);
    vidbuffer[y * vt->width + x] = word;
}

static void cursor_callback(struct vtconsole *vt, const struct vtconsole_cursor *cursor)
{
    unsigned int pos = cursor->y * vt->width + cursor->x;
    outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_LOC_HI);
    outb(VGA_CRTC_IO + 1, (pos >> 8) & 0xFF);
    outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_LOC_LO);
    outb(VGA_CRTC_IO + 1, pos & 0xFF);
}

static void misc_csi_callback(struct vtconsole *vt, int c)
{
    uint8_t csr;

    /* VT220 show/hide cursor sequences */
    if(vt->parser.priv == '?' && vt->parser.stack_map[0] && vt->parser.stack[0] == 25) {
        outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_START);
        csr = inb(VGA_CRTC_IO + 1);

        switch(c) {
            case 'h':
                csr &= ~VGA_CSR_CURSOR_DISABLE;
                break;
            case 'l':
                csr |= VGA_CSR_CURSOR_DISABLE;
                break;
        }

        outb(VGA_CRTC_IO + 1, csr);
    }
}

int init_tmvga(const struct stivale2_struct_tag_textmode *tag)
{
    uint8_t endc;

    if(tag) {
        vidbuffer = (uint16_t *)tag->address;
        init_vtconsole(&vt, (int)tag->cols, (int)tag->rows, &cursor_callback, &paint_callback, &misc_csi_callback);

        endc = 0;
        outb(VGA_CRTC_IO, VGA_CRTC_MAX_SCANLINE);
        endc |= inb(VGA_CRTC_IO + 1) & 0x1F;
        outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_END);
        endc |= inb(VGA_CRTC_IO + 1) & 0xE0;

        outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_START);
        outb(VGA_CRTC_IO + 1, inb(VGA_CRTC_IO + 1) & 0xE0);
        outb(VGA_CRTC_IO, VGA_CRTC_CURSOR_END);
        outb(VGA_CRTC_IO + 1, endc);

        return 1;
    }

    vidbuffer = NULL;
    return 0;
}

void tmvga_write(const void __unused *s, size_t __unused n)
{
    vtconsole_write(&vt, s, n);
}
