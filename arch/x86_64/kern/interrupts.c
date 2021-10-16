#include <arch/interrupts.h>
#include <arch/segment.h>
#include <demos/klog.h>
#include <string.h>

#define IDT_TRAP    (15 << 0)
#define IDT_INTR    (14 << 0)
#define IDT_RING_0  ( 0 << 5)
#define IDT_RING_3  ( 3 << 5)
#define IDT_PRESENT ( 1 << 7)

struct idt_entry {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t ist_off;
    uint8_t flags;
    uint16_t offset_1;
    uint32_t offset_2;
    uint32_t reserved;
} __packed;

struct idt_pointer {
    uint16_t limit;
    uintptr_t base;
} __packed;

extern void __isr_00(void);
extern void __isr_01(void);
extern void __isr_02(void);
extern void __isr_03(void);
extern void __isr_04(void);
extern void __isr_05(void);
extern void __isr_06(void);
extern void __isr_07(void);
extern void __isr_08(void);
extern void __isr_09(void);
extern void __isr_0A(void);
extern void __isr_0B(void);
extern void __isr_0C(void);
extern void __isr_0D(void);
extern void __isr_0E(void);
extern void __isr_0F(void);
extern void __isr_10(void);
extern void __isr_11(void);
extern void __isr_12(void);
extern void __isr_13(void);
extern void __isr_14(void);
extern void __isr_15(void);
extern void __isr_16(void);
extern void __isr_17(void);
extern void __isr_18(void);
extern void __isr_19(void);
extern void __isr_1A(void);
extern void __isr_1B(void);
extern void __isr_1C(void);
extern void __isr_1D(void);
extern void __isr_1E(void);
extern void __isr_1F(void);
extern void __isr_20(void);
extern void __isr_21(void);
extern void __isr_22(void);
extern void __isr_23(void);
extern void __isr_24(void);
extern void __isr_25(void);
extern void __isr_26(void);
extern void __isr_27(void);
extern void __isr_28(void);
extern void __isr_29(void);
extern void __isr_2A(void);
extern void __isr_2B(void);
extern void __isr_2C(void);
extern void __isr_2D(void);
extern void __isr_2E(void);
extern void __isr_2F(void);
extern void __isr_30(void);
extern void __isr_31(void);
extern void __isr_32(void);
extern void __isr_33(void);
extern void __isr_34(void);
extern void __isr_35(void);
extern void __isr_36(void);
extern void __isr_37(void);
extern void __isr_38(void);
extern void __isr_39(void);
extern void __isr_3A(void);
extern void __isr_3B(void);
extern void __isr_3C(void);
extern void __isr_3D(void);
extern void __isr_3E(void);
extern void __isr_3F(void);
extern void __isr_40(void);
extern void __isr_41(void);
extern void __isr_42(void);
extern void __isr_43(void);
extern void __isr_44(void);
extern void __isr_45(void);
extern void __isr_46(void);
extern void __isr_47(void);
extern void __isr_48(void);
extern void __isr_49(void);
extern void __isr_4A(void);
extern void __isr_4B(void);
extern void __isr_4C(void);
extern void __isr_4D(void);
extern void __isr_4E(void);
extern void __isr_4F(void);
extern void __isr_50(void);
extern void __isr_51(void);
extern void __isr_52(void);
extern void __isr_53(void);
extern void __isr_54(void);
extern void __isr_55(void);
extern void __isr_56(void);
extern void __isr_57(void);
extern void __isr_58(void);
extern void __isr_59(void);
extern void __isr_5A(void);
extern void __isr_5B(void);
extern void __isr_5C(void);
extern void __isr_5D(void);
extern void __isr_5E(void);
extern void __isr_5F(void);
extern void __isr_60(void);
extern void __isr_61(void);
extern void __isr_62(void);
extern void __isr_63(void);
extern void __isr_64(void);
extern void __isr_65(void);
extern void __isr_66(void);
extern void __isr_67(void);
extern void __isr_68(void);
extern void __isr_69(void);
extern void __isr_6A(void);
extern void __isr_6B(void);
extern void __isr_6C(void);
extern void __isr_6D(void);
extern void __isr_6E(void);
extern void __isr_6F(void);
extern void __isr_70(void);
extern void __isr_71(void);
extern void __isr_72(void);
extern void __isr_73(void);
extern void __isr_74(void);
extern void __isr_75(void);
extern void __isr_76(void);
extern void __isr_77(void);
extern void __isr_78(void);
extern void __isr_79(void);
extern void __isr_7A(void);
extern void __isr_7B(void);
extern void __isr_7C(void);
extern void __isr_7D(void);
extern void __isr_7E(void);
extern void __isr_7F(void);
extern void __isr_80(void);
extern void __isr_81(void);
extern void __isr_82(void);
extern void __isr_83(void);
extern void __isr_84(void);
extern void __isr_85(void);
extern void __isr_86(void);
extern void __isr_87(void);
extern void __isr_88(void);
extern void __isr_89(void);
extern void __isr_8A(void);
extern void __isr_8B(void);
extern void __isr_8C(void);
extern void __isr_8D(void);
extern void __isr_8E(void);
extern void __isr_8F(void);
extern void __isr_90(void);
extern void __isr_91(void);
extern void __isr_92(void);
extern void __isr_93(void);
extern void __isr_94(void);
extern void __isr_95(void);
extern void __isr_96(void);
extern void __isr_97(void);
extern void __isr_98(void);
extern void __isr_99(void);
extern void __isr_9A(void);
extern void __isr_9B(void);
extern void __isr_9C(void);
extern void __isr_9D(void);
extern void __isr_9E(void);
extern void __isr_9F(void);
extern void __isr_A0(void);
extern void __isr_A1(void);
extern void __isr_A2(void);
extern void __isr_A3(void);
extern void __isr_A4(void);
extern void __isr_A5(void);
extern void __isr_A6(void);
extern void __isr_A7(void);
extern void __isr_A8(void);
extern void __isr_A9(void);
extern void __isr_AA(void);
extern void __isr_AB(void);
extern void __isr_AC(void);
extern void __isr_AD(void);
extern void __isr_AE(void);
extern void __isr_AF(void);
extern void __isr_B0(void);
extern void __isr_B1(void);
extern void __isr_B2(void);
extern void __isr_B3(void);
extern void __isr_B4(void);
extern void __isr_B5(void);
extern void __isr_B6(void);
extern void __isr_B7(void);
extern void __isr_B8(void);
extern void __isr_B9(void);
extern void __isr_BA(void);
extern void __isr_BB(void);
extern void __isr_BC(void);
extern void __isr_BD(void);
extern void __isr_BE(void);
extern void __isr_BF(void);
extern void __isr_C0(void);
extern void __isr_C1(void);
extern void __isr_C2(void);
extern void __isr_C3(void);
extern void __isr_C4(void);
extern void __isr_C5(void);
extern void __isr_C6(void);
extern void __isr_C7(void);
extern void __isr_C8(void);
extern void __isr_C9(void);
extern void __isr_CA(void);
extern void __isr_CB(void);
extern void __isr_CC(void);
extern void __isr_CD(void);
extern void __isr_CE(void);
extern void __isr_CF(void);
extern void __isr_D0(void);
extern void __isr_D1(void);
extern void __isr_D2(void);
extern void __isr_D3(void);
extern void __isr_D4(void);
extern void __isr_D5(void);
extern void __isr_D6(void);
extern void __isr_D7(void);
extern void __isr_D8(void);
extern void __isr_D9(void);
extern void __isr_DA(void);
extern void __isr_DB(void);
extern void __isr_DC(void);
extern void __isr_DD(void);
extern void __isr_DE(void);
extern void __isr_DF(void);
extern void __isr_E0(void);
extern void __isr_E1(void);
extern void __isr_E2(void);
extern void __isr_E3(void);
extern void __isr_E4(void);
extern void __isr_E5(void);
extern void __isr_E6(void);
extern void __isr_E7(void);
extern void __isr_E8(void);
extern void __isr_E9(void);
extern void __isr_EA(void);
extern void __isr_EB(void);
extern void __isr_EC(void);
extern void __isr_ED(void);
extern void __isr_EE(void);
extern void __isr_EF(void);
extern void __isr_F0(void);
extern void __isr_F1(void);
extern void __isr_F2(void);
extern void __isr_F3(void);
extern void __isr_F4(void);
extern void __isr_F5(void);
extern void __isr_F6(void);
extern void __isr_F7(void);
extern void __isr_F8(void);
extern void __isr_F9(void);
extern void __isr_FA(void);
extern void __isr_FB(void);
extern void __isr_FC(void);
extern void __isr_FD(void);
extern void __isr_FE(void);
extern void __isr_FF(void);

static struct idt_entry idt[256] = { 0 };
static struct idt_pointer idt_ptr = { 0 };
static interrupt_handler_t handlers[256] = { 0 };

static void set_entry(unsigned int vector, uint16_t selector, uintptr_t offset, uint8_t flags)
{
    struct idt_entry entry = { 0 };
    entry.offset_0 = offset & 0xFFFF;
    entry.offset_1 = (offset >> 16) & 0xFFFF;
    entry.offset_2 = (offset >> 32) & 0xFFFFFFFF;
    entry.selector = selector;
    entry.flags = flags | IDT_PRESENT;
    memcpy(idt + vector, &entry, sizeof(entry));
}

void __used __isr_handler(struct interrupt_frame *frame)
{
    frame->vector &= 0xFF;
    if(!handlers[frame->vector])
        return;
    handlers[frame->vector](frame);
}

void set_interrupt_handler(unsigned int vector, interrupt_handler_t handler)
{
    vector &= 0xFF;
    handlers[vector] = handler;
}

void init_interrupts(void)
{
    memset(idt, 0, sizeof(idt));

    set_entry(0x00, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_00), IDT_RING_0 | IDT_TRAP);
    set_entry(0x01, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_01), IDT_RING_0 | IDT_TRAP);
    set_entry(0x02, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_02), IDT_RING_0 | IDT_INTR);
    set_entry(0x03, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_03), IDT_RING_0 | IDT_TRAP);
    set_entry(0x04, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_04), IDT_RING_0 | IDT_TRAP);
    set_entry(0x05, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_05), IDT_RING_0 | IDT_TRAP);
    set_entry(0x06, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_06), IDT_RING_0 | IDT_TRAP);
    set_entry(0x07, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_07), IDT_RING_0 | IDT_TRAP);
    set_entry(0x08, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_08), IDT_RING_0 | IDT_TRAP);
    set_entry(0x09, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_09), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0A), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0B), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0C), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0D), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0E), IDT_RING_0 | IDT_TRAP);
    set_entry(0x0F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_0F), IDT_RING_0 | IDT_TRAP);
    set_entry(0x10, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_10), IDT_RING_0 | IDT_TRAP);
    set_entry(0x11, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_11), IDT_RING_0 | IDT_TRAP);
    set_entry(0x12, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_12), IDT_RING_0 | IDT_TRAP);
    set_entry(0x13, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_13), IDT_RING_0 | IDT_TRAP);
    set_entry(0x14, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_14), IDT_RING_0 | IDT_TRAP);
    set_entry(0x15, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_15), IDT_RING_0 | IDT_TRAP);
    set_entry(0x16, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_16), IDT_RING_0 | IDT_TRAP);
    set_entry(0x17, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_17), IDT_RING_0 | IDT_TRAP);
    set_entry(0x18, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_18), IDT_RING_0 | IDT_TRAP);
    set_entry(0x19, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_19), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1A), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1B), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1C), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1D), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1E), IDT_RING_0 | IDT_TRAP);
    set_entry(0x1F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_1F), IDT_RING_0 | IDT_TRAP);
    set_entry(0x20, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_20), IDT_RING_0 | IDT_INTR);
    set_entry(0x21, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_21), IDT_RING_0 | IDT_INTR);
    set_entry(0x22, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_22), IDT_RING_0 | IDT_INTR);
    set_entry(0x23, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_23), IDT_RING_0 | IDT_INTR);
    set_entry(0x24, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_24), IDT_RING_0 | IDT_INTR);
    set_entry(0x25, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_25), IDT_RING_0 | IDT_INTR);
    set_entry(0x26, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_26), IDT_RING_0 | IDT_INTR);
    set_entry(0x27, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_27), IDT_RING_0 | IDT_INTR);
    set_entry(0x28, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_28), IDT_RING_0 | IDT_INTR);
    set_entry(0x29, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_29), IDT_RING_0 | IDT_INTR);
    set_entry(0x2A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2A), IDT_RING_0 | IDT_INTR);
    set_entry(0x2B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2B), IDT_RING_0 | IDT_INTR);
    set_entry(0x2C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2C), IDT_RING_0 | IDT_INTR);
    set_entry(0x2D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2D), IDT_RING_0 | IDT_INTR);
    set_entry(0x2E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2E), IDT_RING_0 | IDT_INTR);
    set_entry(0x2F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_2F), IDT_RING_0 | IDT_INTR);
    set_entry(0x30, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_30), IDT_RING_0 | IDT_INTR);
    set_entry(0x31, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_31), IDT_RING_0 | IDT_INTR);
    set_entry(0x32, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_32), IDT_RING_0 | IDT_INTR);
    set_entry(0x33, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_33), IDT_RING_0 | IDT_INTR);
    set_entry(0x34, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_34), IDT_RING_0 | IDT_INTR);
    set_entry(0x35, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_35), IDT_RING_0 | IDT_INTR);
    set_entry(0x36, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_36), IDT_RING_0 | IDT_INTR);
    set_entry(0x37, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_37), IDT_RING_0 | IDT_INTR);
    set_entry(0x38, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_38), IDT_RING_0 | IDT_INTR);
    set_entry(0x39, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_39), IDT_RING_0 | IDT_INTR);
    set_entry(0x3A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3A), IDT_RING_0 | IDT_INTR);
    set_entry(0x3B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3B), IDT_RING_0 | IDT_INTR);
    set_entry(0x3C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3C), IDT_RING_0 | IDT_INTR);
    set_entry(0x3D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3D), IDT_RING_0 | IDT_INTR);
    set_entry(0x3E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3E), IDT_RING_0 | IDT_INTR);
    set_entry(0x3F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_3F), IDT_RING_0 | IDT_INTR);
    set_entry(0x40, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_40), IDT_RING_0 | IDT_INTR);
    set_entry(0x41, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_41), IDT_RING_0 | IDT_INTR);
    set_entry(0x42, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_42), IDT_RING_0 | IDT_INTR);
    set_entry(0x43, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_43), IDT_RING_0 | IDT_INTR);
    set_entry(0x44, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_44), IDT_RING_0 | IDT_INTR);
    set_entry(0x45, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_45), IDT_RING_0 | IDT_INTR);
    set_entry(0x46, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_46), IDT_RING_0 | IDT_INTR);
    set_entry(0x47, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_47), IDT_RING_0 | IDT_INTR);
    set_entry(0x48, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_48), IDT_RING_0 | IDT_INTR);
    set_entry(0x49, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_49), IDT_RING_0 | IDT_INTR);
    set_entry(0x4A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4A), IDT_RING_0 | IDT_INTR);
    set_entry(0x4B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4B), IDT_RING_0 | IDT_INTR);
    set_entry(0x4C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4C), IDT_RING_0 | IDT_INTR);
    set_entry(0x4D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4D), IDT_RING_0 | IDT_INTR);
    set_entry(0x4E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4E), IDT_RING_0 | IDT_INTR);
    set_entry(0x4F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_4F), IDT_RING_0 | IDT_INTR);
    set_entry(0x50, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_50), IDT_RING_0 | IDT_INTR);
    set_entry(0x51, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_51), IDT_RING_0 | IDT_INTR);
    set_entry(0x52, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_52), IDT_RING_0 | IDT_INTR);
    set_entry(0x53, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_53), IDT_RING_0 | IDT_INTR);
    set_entry(0x54, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_54), IDT_RING_0 | IDT_INTR);
    set_entry(0x55, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_55), IDT_RING_0 | IDT_INTR);
    set_entry(0x56, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_56), IDT_RING_0 | IDT_INTR);
    set_entry(0x57, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_57), IDT_RING_0 | IDT_INTR);
    set_entry(0x58, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_58), IDT_RING_0 | IDT_INTR);
    set_entry(0x59, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_59), IDT_RING_0 | IDT_INTR);
    set_entry(0x5A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5A), IDT_RING_0 | IDT_INTR);
    set_entry(0x5B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5B), IDT_RING_0 | IDT_INTR);
    set_entry(0x5C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5C), IDT_RING_0 | IDT_INTR);
    set_entry(0x5D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5D), IDT_RING_0 | IDT_INTR);
    set_entry(0x5E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5E), IDT_RING_0 | IDT_INTR);
    set_entry(0x5F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_5F), IDT_RING_0 | IDT_INTR);
    set_entry(0x60, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_60), IDT_RING_0 | IDT_INTR);
    set_entry(0x61, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_61), IDT_RING_0 | IDT_INTR);
    set_entry(0x62, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_62), IDT_RING_0 | IDT_INTR);
    set_entry(0x63, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_63), IDT_RING_0 | IDT_INTR);
    set_entry(0x64, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_64), IDT_RING_0 | IDT_INTR);
    set_entry(0x65, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_65), IDT_RING_0 | IDT_INTR);
    set_entry(0x66, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_66), IDT_RING_0 | IDT_INTR);
    set_entry(0x67, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_67), IDT_RING_0 | IDT_INTR);
    set_entry(0x68, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_68), IDT_RING_0 | IDT_INTR);
    set_entry(0x69, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_69), IDT_RING_0 | IDT_INTR);
    set_entry(0x6A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6A), IDT_RING_0 | IDT_INTR);
    set_entry(0x6B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6B), IDT_RING_0 | IDT_INTR);
    set_entry(0x6C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6C), IDT_RING_0 | IDT_INTR);
    set_entry(0x6D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6D), IDT_RING_0 | IDT_INTR);
    set_entry(0x6E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6E), IDT_RING_0 | IDT_INTR);
    set_entry(0x6F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_6F), IDT_RING_0 | IDT_INTR);
    set_entry(0x70, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_70), IDT_RING_0 | IDT_INTR);
    set_entry(0x71, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_71), IDT_RING_0 | IDT_INTR);
    set_entry(0x72, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_72), IDT_RING_0 | IDT_INTR);
    set_entry(0x73, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_73), IDT_RING_0 | IDT_INTR);
    set_entry(0x74, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_74), IDT_RING_0 | IDT_INTR);
    set_entry(0x75, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_75), IDT_RING_0 | IDT_INTR);
    set_entry(0x76, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_76), IDT_RING_0 | IDT_INTR);
    set_entry(0x77, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_77), IDT_RING_0 | IDT_INTR);
    set_entry(0x78, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_78), IDT_RING_0 | IDT_INTR);
    set_entry(0x79, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_79), IDT_RING_0 | IDT_INTR);
    set_entry(0x7A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7A), IDT_RING_0 | IDT_INTR);
    set_entry(0x7B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7B), IDT_RING_0 | IDT_INTR);
    set_entry(0x7C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7C), IDT_RING_0 | IDT_INTR);
    set_entry(0x7D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7D), IDT_RING_0 | IDT_INTR);
    set_entry(0x7E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7E), IDT_RING_0 | IDT_INTR);
    set_entry(0x7F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_7F), IDT_RING_0 | IDT_INTR);
    set_entry(0x80, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_80), IDT_RING_0 | IDT_INTR);
    set_entry(0x81, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_81), IDT_RING_0 | IDT_INTR);
    set_entry(0x82, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_82), IDT_RING_0 | IDT_INTR);
    set_entry(0x83, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_83), IDT_RING_0 | IDT_INTR);
    set_entry(0x84, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_84), IDT_RING_0 | IDT_INTR);
    set_entry(0x85, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_85), IDT_RING_0 | IDT_INTR);
    set_entry(0x86, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_86), IDT_RING_0 | IDT_INTR);
    set_entry(0x87, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_87), IDT_RING_0 | IDT_INTR);
    set_entry(0x88, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_88), IDT_RING_0 | IDT_INTR);
    set_entry(0x89, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_89), IDT_RING_0 | IDT_INTR);
    set_entry(0x8A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8A), IDT_RING_0 | IDT_INTR);
    set_entry(0x8B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8B), IDT_RING_0 | IDT_INTR);
    set_entry(0x8C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8C), IDT_RING_0 | IDT_INTR);
    set_entry(0x8D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8D), IDT_RING_0 | IDT_INTR);
    set_entry(0x8E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8E), IDT_RING_0 | IDT_INTR);
    set_entry(0x8F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_8F), IDT_RING_0 | IDT_INTR);
    set_entry(0x90, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_90), IDT_RING_0 | IDT_INTR);
    set_entry(0x91, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_91), IDT_RING_0 | IDT_INTR);
    set_entry(0x92, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_92), IDT_RING_0 | IDT_INTR);
    set_entry(0x93, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_93), IDT_RING_0 | IDT_INTR);
    set_entry(0x94, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_94), IDT_RING_0 | IDT_INTR);
    set_entry(0x95, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_95), IDT_RING_0 | IDT_INTR);
    set_entry(0x96, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_96), IDT_RING_0 | IDT_INTR);
    set_entry(0x97, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_97), IDT_RING_0 | IDT_INTR);
    set_entry(0x98, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_98), IDT_RING_0 | IDT_INTR);
    set_entry(0x99, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_99), IDT_RING_0 | IDT_INTR);
    set_entry(0x9A, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9A), IDT_RING_0 | IDT_INTR);
    set_entry(0x9B, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9B), IDT_RING_0 | IDT_INTR);
    set_entry(0x9C, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9C), IDT_RING_0 | IDT_INTR);
    set_entry(0x9D, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9D), IDT_RING_0 | IDT_INTR);
    set_entry(0x9E, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9E), IDT_RING_0 | IDT_INTR);
    set_entry(0x9F, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_9F), IDT_RING_0 | IDT_INTR);
    set_entry(0xA0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A0), IDT_RING_0 | IDT_INTR);
    set_entry(0xA1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A1), IDT_RING_0 | IDT_INTR);
    set_entry(0xA2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A2), IDT_RING_0 | IDT_INTR);
    set_entry(0xA3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A3), IDT_RING_0 | IDT_INTR);
    set_entry(0xA4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A4), IDT_RING_0 | IDT_INTR);
    set_entry(0xA5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A5), IDT_RING_0 | IDT_INTR);
    set_entry(0xA6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A6), IDT_RING_0 | IDT_INTR);
    set_entry(0xA7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A7), IDT_RING_0 | IDT_INTR);
    set_entry(0xA8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A8), IDT_RING_0 | IDT_INTR);
    set_entry(0xA9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_A9), IDT_RING_0 | IDT_INTR);
    set_entry(0xAA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AA), IDT_RING_0 | IDT_INTR);
    set_entry(0xAB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AB), IDT_RING_0 | IDT_INTR);
    set_entry(0xAC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AC), IDT_RING_0 | IDT_INTR);
    set_entry(0xAD, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AD), IDT_RING_0 | IDT_INTR);
    set_entry(0xAE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AE), IDT_RING_0 | IDT_INTR);
    set_entry(0xAF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_AF), IDT_RING_0 | IDT_INTR);
    set_entry(0xB0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B0), IDT_RING_0 | IDT_INTR);
    set_entry(0xB1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B1), IDT_RING_0 | IDT_INTR);
    set_entry(0xB2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B2), IDT_RING_0 | IDT_INTR);
    set_entry(0xB3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B3), IDT_RING_0 | IDT_INTR);
    set_entry(0xB4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B4), IDT_RING_0 | IDT_INTR);
    set_entry(0xB5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B5), IDT_RING_0 | IDT_INTR);
    set_entry(0xB6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B6), IDT_RING_0 | IDT_INTR);
    set_entry(0xB7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B7), IDT_RING_0 | IDT_INTR);
    set_entry(0xB8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B8), IDT_RING_0 | IDT_INTR);
    set_entry(0xB9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_B9), IDT_RING_0 | IDT_INTR);
    set_entry(0xBA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BA), IDT_RING_0 | IDT_INTR);
    set_entry(0xBB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BB), IDT_RING_0 | IDT_INTR);
    set_entry(0xBC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BC), IDT_RING_0 | IDT_INTR);
    set_entry(0xBD, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BD), IDT_RING_0 | IDT_INTR);
    set_entry(0xBE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BE), IDT_RING_0 | IDT_INTR);
    set_entry(0xBF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_BF), IDT_RING_0 | IDT_INTR);
    set_entry(0xC0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C0), IDT_RING_0 | IDT_INTR);
    set_entry(0xC1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C1), IDT_RING_0 | IDT_INTR);
    set_entry(0xC2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C2), IDT_RING_0 | IDT_INTR);
    set_entry(0xC3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C3), IDT_RING_0 | IDT_INTR);
    set_entry(0xC4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C4), IDT_RING_0 | IDT_INTR);
    set_entry(0xC5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C5), IDT_RING_0 | IDT_INTR);
    set_entry(0xC6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C6), IDT_RING_0 | IDT_INTR);
    set_entry(0xC7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C7), IDT_RING_0 | IDT_INTR);
    set_entry(0xC8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C8), IDT_RING_0 | IDT_INTR);
    set_entry(0xC9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_C9), IDT_RING_0 | IDT_INTR);
    set_entry(0xCA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CA), IDT_RING_0 | IDT_INTR);
    set_entry(0xCB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CB), IDT_RING_0 | IDT_INTR);
    set_entry(0xCC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CC), IDT_RING_0 | IDT_INTR);
    set_entry(0xCD, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CD), IDT_RING_0 | IDT_INTR);
    set_entry(0xCE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CE), IDT_RING_0 | IDT_INTR);
    set_entry(0xCF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_CF), IDT_RING_0 | IDT_INTR);
    set_entry(0xD0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D0), IDT_RING_0 | IDT_INTR);
    set_entry(0xD1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D1), IDT_RING_0 | IDT_INTR);
    set_entry(0xD2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D2), IDT_RING_0 | IDT_INTR);
    set_entry(0xD3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D3), IDT_RING_0 | IDT_INTR);
    set_entry(0xD4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D4), IDT_RING_0 | IDT_INTR);
    set_entry(0xD5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D5), IDT_RING_0 | IDT_INTR);
    set_entry(0xD6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D6), IDT_RING_0 | IDT_INTR);
    set_entry(0xD7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D7), IDT_RING_0 | IDT_INTR);
    set_entry(0xD8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D8), IDT_RING_0 | IDT_INTR);
    set_entry(0xD9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_D9), IDT_RING_0 | IDT_INTR);
    set_entry(0xDA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DA), IDT_RING_0 | IDT_INTR);
    set_entry(0xDB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DB), IDT_RING_0 | IDT_INTR);
    set_entry(0xDC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DC), IDT_RING_0 | IDT_INTR);
    set_entry(0xDD, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DD), IDT_RING_0 | IDT_INTR);
    set_entry(0xDE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DE), IDT_RING_0 | IDT_INTR);
    set_entry(0xDF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_DF), IDT_RING_0 | IDT_INTR);
    set_entry(0xE0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E0), IDT_RING_0 | IDT_INTR);
    set_entry(0xE1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E1), IDT_RING_0 | IDT_INTR);
    set_entry(0xE2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E2), IDT_RING_0 | IDT_INTR);
    set_entry(0xE3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E3), IDT_RING_0 | IDT_INTR);
    set_entry(0xE4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E4), IDT_RING_0 | IDT_INTR);
    set_entry(0xE5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E5), IDT_RING_0 | IDT_INTR);
    set_entry(0xE6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E6), IDT_RING_0 | IDT_INTR);
    set_entry(0xE7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E7), IDT_RING_0 | IDT_INTR);
    set_entry(0xE8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E8), IDT_RING_0 | IDT_INTR);
    set_entry(0xE9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_E9), IDT_RING_0 | IDT_INTR);
    set_entry(0xEA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_EA), IDT_RING_0 | IDT_INTR);
    set_entry(0xEB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_EB), IDT_RING_0 | IDT_INTR);
    set_entry(0xEC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_EC), IDT_RING_0 | IDT_INTR);
    set_entry(0xED, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_ED), IDT_RING_0 | IDT_INTR);
    set_entry(0xEE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_EE), IDT_RING_0 | IDT_INTR);
    set_entry(0xEF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_EF), IDT_RING_0 | IDT_INTR);
    set_entry(0xF0, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F0), IDT_RING_0 | IDT_INTR);
    set_entry(0xF1, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F1), IDT_RING_0 | IDT_INTR);
    set_entry(0xF2, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F2), IDT_RING_0 | IDT_INTR);
    set_entry(0xF3, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F3), IDT_RING_0 | IDT_INTR);
    set_entry(0xF4, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F4), IDT_RING_0 | IDT_INTR);
    set_entry(0xF5, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F5), IDT_RING_0 | IDT_INTR);
    set_entry(0xF6, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F6), IDT_RING_0 | IDT_INTR);
    set_entry(0xF7, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F7), IDT_RING_0 | IDT_INTR);
    set_entry(0xF8, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F8), IDT_RING_0 | IDT_INTR);
    set_entry(0xF9, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_F9), IDT_RING_0 | IDT_INTR);
    set_entry(0xFA, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FA), IDT_RING_0 | IDT_INTR);
    set_entry(0xFB, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FB), IDT_RING_0 | IDT_INTR);
    set_entry(0xFC, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FC), IDT_RING_0 | IDT_INTR);
    set_entry(0xFD, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FD), IDT_RING_0 | IDT_INTR);
    set_entry(0xFE, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FE), IDT_RING_0 | IDT_INTR);
    set_entry(0xFF, SEG_SELECTOR(SEG_INDEX_KERN_CODE, 0, 0), (uintptr_t)(&__isr_FF), IDT_RING_0 | IDT_INTR);

    idt_ptr.limit = (uint16_t)(sizeof(idt) - 1);
    idt_ptr.base = (uintptr_t)(&idt[0]);

    klog(KLOG_INFO, "idt: limit=%hu, base=%p", idt_ptr.limit, (void *)idt_ptr.base);

    asm volatile("lidtq %0"::"m"(idt_ptr));
}
