#include <arch/interrupts.h>
#include <arch/segment.h>
#include <demos/cdefs.h>
#include <string.h>

#define IDT_SIZE (256)

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
    uint64_t base;
} __packed;

static struct idt_entry idt[256] = { 0 };
static struct idt_pointer idt_ptr = { 0 };
static interrupt_handler_t handlers[256] = { 0 };

static void set_idt_entry(uint8_t int_no, uint16_t selector, const void *offset, uint8_t flags)
{
    uint64_t offset_i = (uint64_t)offset;
    struct idt_entry entry = { 0 };
    entry.offset_0 = offset_i & 0xFFFF;
    entry.offset_1 = (offset_i >> 16) & 0xFFFF;
    entry.offset_2 = (offset_i >> 32) & 0xFFFFFFFF;
    entry.selector = selector;
    entry.flags = flags | IDT_PRESENT;
    memcpy(idt + int_no, &entry, sizeof(entry));
}

void kprintf(const char *fmt, ...);

void __used common_interrupt_handler(struct interrupt_frame *frame)
{
    interrupt_handler_t handler;
    if((handler = handlers[frame->int_no & 0xFF]))
        handler(frame);
}

extern void interrupt_00(void);
extern void interrupt_01(void);
extern void interrupt_02(void);
extern void interrupt_03(void);
extern void interrupt_04(void);
extern void interrupt_05(void);
extern void interrupt_06(void);
extern void interrupt_07(void);
extern void interrupt_08(void);
extern void interrupt_09(void);
extern void interrupt_0A(void);
extern void interrupt_0B(void);
extern void interrupt_0C(void);
extern void interrupt_0D(void);
extern void interrupt_0E(void);
extern void interrupt_0F(void);
extern void interrupt_10(void);
extern void interrupt_11(void);
extern void interrupt_12(void);
extern void interrupt_13(void);
extern void interrupt_14(void);
extern void interrupt_15(void);
extern void interrupt_16(void);
extern void interrupt_17(void);
extern void interrupt_18(void);
extern void interrupt_19(void);
extern void interrupt_1A(void);
extern void interrupt_1B(void);
extern void interrupt_1C(void);
extern void interrupt_1D(void);
extern void interrupt_1E(void);
extern void interrupt_1F(void);
extern void interrupt_20(void);
extern void interrupt_21(void);
extern void interrupt_22(void);
extern void interrupt_23(void);
extern void interrupt_24(void);
extern void interrupt_25(void);
extern void interrupt_26(void);
extern void interrupt_27(void);
extern void interrupt_28(void);
extern void interrupt_29(void);
extern void interrupt_2A(void);
extern void interrupt_2B(void);
extern void interrupt_2C(void);
extern void interrupt_2D(void);
extern void interrupt_2E(void);
extern void interrupt_2F(void);
extern void interrupt_30(void);
extern void interrupt_31(void);
extern void interrupt_32(void);
extern void interrupt_33(void);
extern void interrupt_34(void);
extern void interrupt_35(void);
extern void interrupt_36(void);
extern void interrupt_37(void);
extern void interrupt_38(void);
extern void interrupt_39(void);
extern void interrupt_3A(void);
extern void interrupt_3B(void);
extern void interrupt_3C(void);
extern void interrupt_3D(void);
extern void interrupt_3E(void);
extern void interrupt_3F(void);
extern void interrupt_40(void);
extern void interrupt_41(void);
extern void interrupt_42(void);
extern void interrupt_43(void);
extern void interrupt_44(void);
extern void interrupt_45(void);
extern void interrupt_46(void);
extern void interrupt_47(void);
extern void interrupt_48(void);
extern void interrupt_49(void);
extern void interrupt_4A(void);
extern void interrupt_4B(void);
extern void interrupt_4C(void);
extern void interrupt_4D(void);
extern void interrupt_4E(void);
extern void interrupt_4F(void);
extern void interrupt_50(void);
extern void interrupt_51(void);
extern void interrupt_52(void);
extern void interrupt_53(void);
extern void interrupt_54(void);
extern void interrupt_55(void);
extern void interrupt_56(void);
extern void interrupt_57(void);
extern void interrupt_58(void);
extern void interrupt_59(void);
extern void interrupt_5A(void);
extern void interrupt_5B(void);
extern void interrupt_5C(void);
extern void interrupt_5D(void);
extern void interrupt_5E(void);
extern void interrupt_5F(void);
extern void interrupt_60(void);
extern void interrupt_61(void);
extern void interrupt_62(void);
extern void interrupt_63(void);
extern void interrupt_64(void);
extern void interrupt_65(void);
extern void interrupt_66(void);
extern void interrupt_67(void);
extern void interrupt_68(void);
extern void interrupt_69(void);
extern void interrupt_6A(void);
extern void interrupt_6B(void);
extern void interrupt_6C(void);
extern void interrupt_6D(void);
extern void interrupt_6E(void);
extern void interrupt_6F(void);
extern void interrupt_70(void);
extern void interrupt_71(void);
extern void interrupt_72(void);
extern void interrupt_73(void);
extern void interrupt_74(void);
extern void interrupt_75(void);
extern void interrupt_76(void);
extern void interrupt_77(void);
extern void interrupt_78(void);
extern void interrupt_79(void);
extern void interrupt_7A(void);
extern void interrupt_7B(void);
extern void interrupt_7C(void);
extern void interrupt_7D(void);
extern void interrupt_7E(void);
extern void interrupt_7F(void);
extern void interrupt_80(void);
extern void interrupt_81(void);
extern void interrupt_82(void);
extern void interrupt_83(void);
extern void interrupt_84(void);
extern void interrupt_85(void);
extern void interrupt_86(void);
extern void interrupt_87(void);
extern void interrupt_88(void);
extern void interrupt_89(void);
extern void interrupt_8A(void);
extern void interrupt_8B(void);
extern void interrupt_8C(void);
extern void interrupt_8D(void);
extern void interrupt_8E(void);
extern void interrupt_8F(void);
extern void interrupt_90(void);
extern void interrupt_91(void);
extern void interrupt_92(void);
extern void interrupt_93(void);
extern void interrupt_94(void);
extern void interrupt_95(void);
extern void interrupt_96(void);
extern void interrupt_97(void);
extern void interrupt_98(void);
extern void interrupt_99(void);
extern void interrupt_9A(void);
extern void interrupt_9B(void);
extern void interrupt_9C(void);
extern void interrupt_9D(void);
extern void interrupt_9E(void);
extern void interrupt_9F(void);
extern void interrupt_A0(void);
extern void interrupt_A1(void);
extern void interrupt_A2(void);
extern void interrupt_A3(void);
extern void interrupt_A4(void);
extern void interrupt_A5(void);
extern void interrupt_A6(void);
extern void interrupt_A7(void);
extern void interrupt_A8(void);
extern void interrupt_A9(void);
extern void interrupt_AA(void);
extern void interrupt_AB(void);
extern void interrupt_AC(void);
extern void interrupt_AD(void);
extern void interrupt_AE(void);
extern void interrupt_AF(void);
extern void interrupt_B0(void);
extern void interrupt_B1(void);
extern void interrupt_B2(void);
extern void interrupt_B3(void);
extern void interrupt_B4(void);
extern void interrupt_B5(void);
extern void interrupt_B6(void);
extern void interrupt_B7(void);
extern void interrupt_B8(void);
extern void interrupt_B9(void);
extern void interrupt_BA(void);
extern void interrupt_BB(void);
extern void interrupt_BC(void);
extern void interrupt_BD(void);
extern void interrupt_BE(void);
extern void interrupt_BF(void);
extern void interrupt_C0(void);
extern void interrupt_C1(void);
extern void interrupt_C2(void);
extern void interrupt_C3(void);
extern void interrupt_C4(void);
extern void interrupt_C5(void);
extern void interrupt_C6(void);
extern void interrupt_C7(void);
extern void interrupt_C8(void);
extern void interrupt_C9(void);
extern void interrupt_CA(void);
extern void interrupt_CB(void);
extern void interrupt_CC(void);
extern void interrupt_CD(void);
extern void interrupt_CE(void);
extern void interrupt_CF(void);
extern void interrupt_D0(void);
extern void interrupt_D1(void);
extern void interrupt_D2(void);
extern void interrupt_D3(void);
extern void interrupt_D4(void);
extern void interrupt_D5(void);
extern void interrupt_D6(void);
extern void interrupt_D7(void);
extern void interrupt_D8(void);
extern void interrupt_D9(void);
extern void interrupt_DA(void);
extern void interrupt_DB(void);
extern void interrupt_DC(void);
extern void interrupt_DD(void);
extern void interrupt_DE(void);
extern void interrupt_DF(void);
extern void interrupt_E0(void);
extern void interrupt_E1(void);
extern void interrupt_E2(void);
extern void interrupt_E3(void);
extern void interrupt_E4(void);
extern void interrupt_E5(void);
extern void interrupt_E6(void);
extern void interrupt_E7(void);
extern void interrupt_E8(void);
extern void interrupt_E9(void);
extern void interrupt_EA(void);
extern void interrupt_EB(void);
extern void interrupt_EC(void);
extern void interrupt_ED(void);
extern void interrupt_EE(void);
extern void interrupt_EF(void);
extern void interrupt_F0(void);
extern void interrupt_F1(void);
extern void interrupt_F2(void);
extern void interrupt_F3(void);
extern void interrupt_F4(void);
extern void interrupt_F5(void);
extern void interrupt_F6(void);
extern void interrupt_F7(void);
extern void interrupt_F8(void);
extern void interrupt_F9(void);
extern void interrupt_FA(void);
extern void interrupt_FB(void);
extern void interrupt_FC(void);
extern void interrupt_FD(void);
extern void interrupt_FE(void);
extern void interrupt_FF(void);

void set_interrupt_handler(uint8_t int_no, interrupt_handler_t handler)
{
    handlers[int_no] = handler;
}

void init_interrupts(void)
{
    memset(idt, 0, sizeof(idt));

    set_idt_entry(0x00, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_00, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x01, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_01, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x02, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_02, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x03, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_03, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x04, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_04, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x05, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_05, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x06, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_06, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x07, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_07, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x08, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_08, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x09, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_09, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0A, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0B, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0C, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0D, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0E, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x0F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_0F, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x10, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_10, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x11, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_11, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x12, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_12, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x13, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_13, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x14, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_14, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x15, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_15, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x16, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_16, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x17, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_17, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x18, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_18, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x19, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_19, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1A, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1B, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1C, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1D, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1E, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x1F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_1F, IDT_RING_0 | IDT_TRAP);
    set_idt_entry(0x20, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_20, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x21, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_21, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x22, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_22, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x23, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_23, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x24, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_24, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x25, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_25, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x26, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_26, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x27, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_27, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x28, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_28, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x29, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_29, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x2F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_2F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x30, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_30, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x31, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_31, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x32, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_32, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x33, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_33, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x34, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_34, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x35, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_35, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x36, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_36, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x37, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_37, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x38, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_38, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x39, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_39, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x3F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_3F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x40, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_40, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x41, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_41, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x42, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_42, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x43, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_43, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x44, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_44, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x45, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_45, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x46, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_46, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x47, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_47, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x48, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_48, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x49, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_49, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x4F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_4F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x50, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_50, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x51, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_51, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x52, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_52, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x53, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_53, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x54, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_54, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x55, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_55, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x56, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_56, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x57, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_57, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x58, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_58, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x59, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_59, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x5F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_5F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x60, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_60, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x61, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_61, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x62, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_62, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x63, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_63, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x64, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_64, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x65, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_65, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x66, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_66, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x67, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_67, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x68, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_68, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x69, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_69, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x6F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_6F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x70, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_70, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x71, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_71, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x72, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_72, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x73, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_73, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x74, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_74, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x75, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_75, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x76, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_76, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x77, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_77, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x78, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_78, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x79, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_79, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x7F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_7F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x80, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_80, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x81, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_81, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x82, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_82, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x83, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_83, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x84, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_84, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x85, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_85, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x86, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_86, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x87, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_87, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x88, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_88, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x89, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_89, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x8F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_8F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x90, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_90, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x91, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_91, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x92, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_92, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x93, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_93, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x94, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_94, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x95, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_95, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x96, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_96, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x97, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_97, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x98, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_98, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x99, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_99, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9A, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9A, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9B, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9B, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9C, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9C, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9D, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9D, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9E, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9E, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0x9F, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_9F, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xA9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_A9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAD, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AD, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xAF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_AF, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xB9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_B9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBD, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BD, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xBF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_BF, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xC9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_C9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCD, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CD, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xCF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_CF, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xD9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_D9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDD, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DD, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xDF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_DF, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xE9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_E9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xEA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_EA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xEB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_EB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xEC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_EC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xED, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_ED, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xEE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_EE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xEF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_EF, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF0, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F0, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF1, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F1, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF2, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F2, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF3, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F3, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF4, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F4, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF5, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F5, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF6, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F6, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF7, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F7, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF8, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F8, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xF9, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_F9, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFA, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FA, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFB, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FB, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFC, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FC, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFD, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FD, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFE, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FE, IDT_RING_0 | IDT_INTR);
    set_idt_entry(0xFF, SEG_SELECTOR(0, 0, SEG_INDEX_CODE64), interrupt_FF, IDT_RING_0 | IDT_INTR);

    idt_ptr.limit = (uint16_t)(sizeof(idt) - 1);
    idt_ptr.base = (uint64_t)(idt);

    asm volatile("lidtq %0"::"m"(idt_ptr));
}
