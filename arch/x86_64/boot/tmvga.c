/* SPDX-License-Identifier: BSD-2-Clause */
#include <arch/io.h>
#include <sys/km.h>
#include <ctype.h>
#include <stivale2.h>
#include <string.h>
#include <libvterm.h>

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

static struct vterm vt = { 0 };
static uint16_t *vidbuffer = NULL;

static const uint8_t colormap[8] = {
    [VTERM_COLOR_BLK] = VGA_COLOR_BLACK,
    [VTERM_COLOR_RED] = VGA_COLOR_RED,
    [VTERM_COLOR_GRN] = VGA_COLOR_GREEN,
    [VTERM_COLOR_YLW] = VGA_COLOR_BROWN,
    [VTERM_COLOR_BLU] = VGA_COLOR_BLUE,
    [VTERM_COLOR_MAG] = VGA_COLOR_MAGENTA,
    [VTERM_COLOR_CYN] = VGA_COLOR_CYAN,
    [VTERM_COLOR_WHT] = VGA_COLOR_LIGHT_GRAY
};

static const uint8_t colormap_b[8] = {
    [VTERM_COLOR_BLK] = VGA_COLOR_BLACK,
    [VTERM_COLOR_RED] = VGA_COLOR_LIGHT_RED,
    [VTERM_COLOR_GRN] = VGA_COLOR_LIGHT_GREEN,
    [VTERM_COLOR_YLW] = VGA_COLOR_LIGHT_YELLOW,
    [VTERM_COLOR_BLU] = VGA_COLOR_LIGHT_BLUE,
    [VTERM_COLOR_MAG] = VGA_COLOR_LIGHT_MAGENTA,
    [VTERM_COLOR_CYN] = VGA_COLOR_LIGHT_CYAN,
    [VTERM_COLOR_WHT] = VGA_COLOR_WHITE
};

static void on_misc_sequence(const struct vterm *vt, int chr)
{
    uint8_t csr;

    /* VT220 show/hide cursor sequences */
    if(vt->parser.prefix_chr == '?' && vt->parser.argv_map[0] && vt->parser.argv_val[0] == 25) {
        io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_START);
        csr = io_read8(VGA_CRTC_IO + 1);

        switch(chr) {
            case 'h':
                csr &= ~VGA_CSR_CURSOR_DISABLE;
                break;
            case 'l':
                csr |= VGA_CSR_CURSOR_DISABLE;
                break;
        }

        io_write8(VGA_CRTC_IO + 1, csr);
    }
}

static void on_set_cursor(const struct vterm *vt, const struct vterm_cursor *cursor)
{
    unsigned int pos = cursor->y * vt->mode.scr_w + cursor->x;
    io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_LOC_HI);
    io_write8(VGA_CRTC_IO + 1, (pos >> 8) & 0xFF);
    io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_LOC_LO);
    io_write8(VGA_CRTC_IO + 1, pos & 0xFF);
}

static void on_draw_cell(const struct vterm *vt, int chr, unsigned int x, unsigned int y, const struct vterm_attrib *attrib)
{
    const uint8_t *swap_colormap;
    const uint8_t *back_colormap = colormap;
    const uint8_t *fore_colormap = colormap;
    int back_idx, fore_idx;
    uint16_t word;

    if((attrib->attr & VTERM_ATTR_BOLD) || (attrib->attr & VTERM_ATTR_BRIGHT))
        fore_colormap = colormap_b;

    if(attrib->attr & VTERM_ATTR_INVERT) {
        swap_colormap = fore_colormap;
        fore_colormap = back_colormap;
        back_colormap = swap_colormap;
        fore_idx = attrib->bg;
        back_idx = attrib->fg;
    }
    else {
        fore_idx = attrib->fg;
        back_idx = attrib->bg;
    }

    word = 0;
    word |= (back_colormap[back_idx] & 0x0F) << 12;
    word |= (fore_colormap[fore_idx] & 0x0F) << 8;
    word |= (chr & 0xFF);
    vidbuffer[y * vt->mode.scr_w + x] = word;
}

int init_tmvga(const struct stivale2_struct_tag_textmode *tag)
{
    uint8_t endc;
    struct vterm_callbacks callbacks;

    if(tag) {
        vidbuffer = (uint16_t *)tag->address;

        callbacks.mem_alloc = &kmalloc;
        callbacks.mem_free = &kmfree;
        callbacks.misc_sequence = &on_misc_sequence;
        callbacks.set_cursor = &on_set_cursor;
        callbacks.draw_cell = &on_draw_cell;
        vterm_init(&vt, &callbacks, NULL);

        endc = 0;
        io_write8(VGA_CRTC_IO, VGA_CRTC_MAX_SCANLINE);
        endc |= io_read8(VGA_CRTC_IO + 1) & 0x1F;
        io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_END);
        endc |= io_read8(VGA_CRTC_IO + 1) & 0xE0;

        io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_START);
        io_write8(VGA_CRTC_IO + 1, io_read8(VGA_CRTC_IO + 1) & 0xE0);
        io_write8(VGA_CRTC_IO, VGA_CRTC_CURSOR_END);
        io_write8(VGA_CRTC_IO + 1, endc);

        return 1;
    }

    vidbuffer = NULL;
    return 0;
}

void tmvga_write(const void *s, size_t n)
{
    vterm_write(&vt, s, n);
}
