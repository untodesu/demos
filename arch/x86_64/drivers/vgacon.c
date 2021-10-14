#include <drivers/vgacon.h>
#include <lib/ctype.h>
#include <lib/string.h>
#include <sys/ports.h>
#include <sys/stivale2.h>

#define VGA_CRTC 0x3D4

#define VGA_CRTC_MAX_SCANLINE   0x09
#define VGA_CRTC_CURSOR_START   0x0A
#define VGA_CRTC_CURSOR_END     0x0B
#define VGA_CRTC_CURSOR_LOC_HI  0x0E
#define VGA_CRTC_CURSOR_LOC_LO  0x0F

static uint16_t *fill16(uint16_t *s, uint16_t v, size_t n)
{
    size_t i = 0;
    while(n--)
        s[i++] = v;
    return s;
}

static struct stivale2_struct_tag_textmode vgainfo = { 0 };
static size_t cursor = 0, vidbuffer_size = 0;
static uint16_t *vidbuffer = NULL;

static void update_cursor(void)
{
    outb(VGA_CRTC, VGA_CRTC_CURSOR_LOC_HI);
    outb(VGA_CRTC + 1, (cursor >> 8) & 0xFF);
    outb(VGA_CRTC, VGA_CRTC_CURSOR_LOC_LO);
    outb(VGA_CRTC + 1, cursor & 0xFF);
}

int init_vgacon(const struct stivale2_struct_tag_textmode *tag)
{
    uint8_t endc;

    cursor = 0;
    vidbuffer_size = 0;
    vidbuffer = NULL;

    if(tag) {
        memcpy(&vgainfo, tag, sizeof(struct stivale2_struct_tag_textmode));
        cursor = 0;
        vidbuffer_size = vgainfo.rows * vgainfo.cols;
        vidbuffer = (uint16_t *)vgainfo.address;

        endc = 0;
        outb(VGA_CRTC, VGA_CRTC_MAX_SCANLINE);
        endc |= inb(VGA_CRTC + 1) & 0x1F;
        outb(VGA_CRTC, VGA_CRTC_CURSOR_END);
        endc |= inb(VGA_CRTC + 1) & 0xE0;

        outb(VGA_CRTC, VGA_CRTC_CURSOR_START);
        outb(VGA_CRTC + 1, 0x00);
        outb(VGA_CRTC, VGA_CRTC_CURSOR_END);
        outb(VGA_CRTC + 1, endc);

        fill16(vidbuffer, 0x0700, vidbuffer_size);

        update_cursor();

        return 1;
    }

    return 0;
}

void vgacon_write(const void *s, size_t n)
{
    char c;
    size_t i, lim;
    const char *sp = s;

    if(vidbuffer) {
        lim = (size_t)(vgainfo.rows - 1);
        
        while(n--) {
            switch(c = *sp++) {
                case '\b':
                    if(cursor % vgainfo.rows)
                        cursor--;
                    break;
                case '\r':
                    cursor = (cursor / vgainfo.cols) * vgainfo.cols;
                    break;
                case '\n':
                    cursor = ((cursor / vgainfo.cols) + 1) * vgainfo.cols;
                    break;
                default:
                    vidbuffer[cursor++] = 0x0700 | c;
                    break;
            }

            if((cursor / vgainfo.cols) > lim) {
                for(i = 0; i < lim; i++)
                    memcpy(vidbuffer + i * vgainfo.cols, vidbuffer + (i + 1) * vgainfo.cols, sizeof(uint16_t) * vgainfo.cols);
                fill16(vidbuffer + vgainfo.cols * lim, 0x0700, vgainfo.cols);
                cursor -= vgainfo.cols;
            }
        }

        update_cursor();
    }
}
