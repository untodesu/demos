#include <arch/interrupts.h>
#include <arch/segment.h>
#include <demos/string.h>

#define IDT_SIZE 256

#define GATE_TYPE_INTR 0x0E
#define GATE_TYPE_TRAP 0x0F

struct idt_gate {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t unused;
    uint8_t type    : 5;
    uint8_t dpl     : 2;
    uint8_t present : 1;
    uint16_t offset_1;
} __packed;

struct idt_descr {
    uint16_t size;
    uint32_t offset;
} __packed;

static struct idt_gate idt[IDT_SIZE] = { 0 };
static struct idt_descr idt_descr = { 0 };
static interrupt_handler_t handlers[IDT_SIZE] = { 0 };

extern void intr_00(void);
extern void intr_01(void);
extern void intr_02(void);
extern void intr_03(void);
extern void intr_04(void);
extern void intr_05(void);
extern void intr_06(void);
extern void intr_07(void);
extern void intr_08(void);
extern void intr_09(void);
extern void intr_0A(void);
extern void intr_0B(void);
extern void intr_0C(void);
extern void intr_0D(void);
extern void intr_0E(void);
extern void intr_0F(void);
extern void intr_10(void);
extern void intr_11(void);
extern void intr_12(void);
extern void intr_13(void);
extern void intr_14(void);
extern void intr_15(void);
extern void intr_16(void);
extern void intr_17(void);
extern void intr_18(void);
extern void intr_19(void);
extern void intr_1A(void);
extern void intr_1B(void);
extern void intr_1C(void);
extern void intr_1D(void);
extern void intr_1E(void);
extern void intr_1F(void);
extern void intr_20(void);
extern void intr_21(void);
extern void intr_22(void);
extern void intr_23(void);
extern void intr_24(void);
extern void intr_25(void);
extern void intr_26(void);
extern void intr_27(void);
extern void intr_28(void);
extern void intr_29(void);
extern void intr_2A(void);
extern void intr_2B(void);
extern void intr_2C(void);
extern void intr_2D(void);
extern void intr_2E(void);
extern void intr_2F(void);
extern void intr_30(void);
extern void intr_31(void);
extern void intr_32(void);
extern void intr_33(void);
extern void intr_34(void);
extern void intr_35(void);
extern void intr_36(void);
extern void intr_37(void);
extern void intr_38(void);
extern void intr_39(void);
extern void intr_3A(void);
extern void intr_3B(void);
extern void intr_3C(void);
extern void intr_3D(void);
extern void intr_3E(void);
extern void intr_3F(void);
extern void intr_40(void);
extern void intr_41(void);
extern void intr_42(void);
extern void intr_43(void);
extern void intr_44(void);
extern void intr_45(void);
extern void intr_46(void);
extern void intr_47(void);
extern void intr_48(void);
extern void intr_49(void);
extern void intr_4A(void);
extern void intr_4B(void);
extern void intr_4C(void);
extern void intr_4D(void);
extern void intr_4E(void);
extern void intr_4F(void);
extern void intr_50(void);
extern void intr_51(void);
extern void intr_52(void);
extern void intr_53(void);
extern void intr_54(void);
extern void intr_55(void);
extern void intr_56(void);
extern void intr_57(void);
extern void intr_58(void);
extern void intr_59(void);
extern void intr_5A(void);
extern void intr_5B(void);
extern void intr_5C(void);
extern void intr_5D(void);
extern void intr_5E(void);
extern void intr_5F(void);
extern void intr_60(void);
extern void intr_61(void);
extern void intr_62(void);
extern void intr_63(void);
extern void intr_64(void);
extern void intr_65(void);
extern void intr_66(void);
extern void intr_67(void);
extern void intr_68(void);
extern void intr_69(void);
extern void intr_6A(void);
extern void intr_6B(void);
extern void intr_6C(void);
extern void intr_6D(void);
extern void intr_6E(void);
extern void intr_6F(void);
extern void intr_70(void);
extern void intr_71(void);
extern void intr_72(void);
extern void intr_73(void);
extern void intr_74(void);
extern void intr_75(void);
extern void intr_76(void);
extern void intr_77(void);
extern void intr_78(void);
extern void intr_79(void);
extern void intr_7A(void);
extern void intr_7B(void);
extern void intr_7C(void);
extern void intr_7D(void);
extern void intr_7E(void);
extern void intr_7F(void);
extern void intr_80(void);
extern void intr_81(void);
extern void intr_82(void);
extern void intr_83(void);
extern void intr_84(void);
extern void intr_85(void);
extern void intr_86(void);
extern void intr_87(void);
extern void intr_88(void);
extern void intr_89(void);
extern void intr_8A(void);
extern void intr_8B(void);
extern void intr_8C(void);
extern void intr_8D(void);
extern void intr_8E(void);
extern void intr_8F(void);
extern void intr_90(void);
extern void intr_91(void);
extern void intr_92(void);
extern void intr_93(void);
extern void intr_94(void);
extern void intr_95(void);
extern void intr_96(void);
extern void intr_97(void);
extern void intr_98(void);
extern void intr_99(void);
extern void intr_9A(void);
extern void intr_9B(void);
extern void intr_9C(void);
extern void intr_9D(void);
extern void intr_9E(void);
extern void intr_9F(void);
extern void intr_A0(void);
extern void intr_A1(void);
extern void intr_A2(void);
extern void intr_A3(void);
extern void intr_A4(void);
extern void intr_A5(void);
extern void intr_A6(void);
extern void intr_A7(void);
extern void intr_A8(void);
extern void intr_A9(void);
extern void intr_AA(void);
extern void intr_AB(void);
extern void intr_AC(void);
extern void intr_AD(void);
extern void intr_AE(void);
extern void intr_AF(void);
extern void intr_B0(void);
extern void intr_B1(void);
extern void intr_B2(void);
extern void intr_B3(void);
extern void intr_B4(void);
extern void intr_B5(void);
extern void intr_B6(void);
extern void intr_B7(void);
extern void intr_B8(void);
extern void intr_B9(void);
extern void intr_BA(void);
extern void intr_BB(void);
extern void intr_BC(void);
extern void intr_BD(void);
extern void intr_BE(void);
extern void intr_BF(void);
extern void intr_C0(void);
extern void intr_C1(void);
extern void intr_C2(void);
extern void intr_C3(void);
extern void intr_C4(void);
extern void intr_C5(void);
extern void intr_C6(void);
extern void intr_C7(void);
extern void intr_C8(void);
extern void intr_C9(void);
extern void intr_CA(void);
extern void intr_CB(void);
extern void intr_CC(void);
extern void intr_CD(void);
extern void intr_CE(void);
extern void intr_CF(void);
extern void intr_D0(void);
extern void intr_D1(void);
extern void intr_D2(void);
extern void intr_D3(void);
extern void intr_D4(void);
extern void intr_D5(void);
extern void intr_D6(void);
extern void intr_D7(void);
extern void intr_D8(void);
extern void intr_D9(void);
extern void intr_DA(void);
extern void intr_DB(void);
extern void intr_DC(void);
extern void intr_DD(void);
extern void intr_DE(void);
extern void intr_DF(void);
extern void intr_E0(void);
extern void intr_E1(void);
extern void intr_E2(void);
extern void intr_E3(void);
extern void intr_E4(void);
extern void intr_E5(void);
extern void intr_E6(void);
extern void intr_E7(void);
extern void intr_E8(void);
extern void intr_E9(void);
extern void intr_EA(void);
extern void intr_EB(void);
extern void intr_EC(void);
extern void intr_ED(void);
extern void intr_EE(void);
extern void intr_EF(void);
extern void intr_F0(void);
extern void intr_F1(void);
extern void intr_F2(void);
extern void intr_F3(void);
extern void intr_F4(void);
extern void intr_F5(void);
extern void intr_F6(void);
extern void intr_F7(void);
extern void intr_F8(void);
extern void intr_F9(void);
extern void intr_FA(void);
extern void intr_FB(void);
extern void intr_FC(void);
extern void intr_FD(void);
extern void intr_FE(void);
extern void intr_FF(void);

static inline void set_gate(uint8_t int_no, uint16_t selector, uint8_t type, uint8_t dpl, const void *ptr)
{
    struct idt_gate *gate = (idt + int_no);
    gate->offset_0 = ((uint32_t)ptr) & 0xFFFF;
    gate->selector = selector;
    gate->type = type;
    gate->dpl = dpl;
    gate->present = 1;
    gate->offset_1 = ((uint32_t)ptr >> 16) & 0xFFFF;
}

void common_interrupt_handler(struct interrupt_frame *frame)
{
    interrupt_handler_t handler = handlers[frame->int_no];
    if(handler != NULL)
        handler(frame);
}

void init_interrupts(void)
{
    memset(idt, 0, sizeof(idt));

    set_gate(0x00, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_00);
    set_gate(0x01, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_01);
    set_gate(0x02, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_02);
    set_gate(0x03, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_03);
    set_gate(0x04, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_04);
    set_gate(0x05, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_05);
    set_gate(0x06, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_06);
    set_gate(0x07, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_07);
    set_gate(0x08, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_08);
    set_gate(0x09, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_09);
    set_gate(0x0A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0A);
    set_gate(0x0B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0B);
    set_gate(0x0C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0C);
    set_gate(0x0D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0D);
    set_gate(0x0E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0E);
    set_gate(0x0F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_0F);
    set_gate(0x10, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_10);
    set_gate(0x11, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_11);
    set_gate(0x12, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_12);
    set_gate(0x13, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_13);
    set_gate(0x14, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_14);
    set_gate(0x15, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_15);
    set_gate(0x16, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_16);
    set_gate(0x17, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_17);
    set_gate(0x18, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_18);
    set_gate(0x19, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_19);
    set_gate(0x1A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1A);
    set_gate(0x1B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1B);
    set_gate(0x1C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1C);
    set_gate(0x1D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1D);
    set_gate(0x1E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1E);
    set_gate(0x1F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_TRAP, 0, intr_1F);
    set_gate(0x20, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_20);
    set_gate(0x21, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_21);
    set_gate(0x22, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_22);
    set_gate(0x23, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_23);
    set_gate(0x24, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_24);
    set_gate(0x25, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_25);
    set_gate(0x26, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_26);
    set_gate(0x27, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_27);
    set_gate(0x28, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_28);
    set_gate(0x29, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_29);
    set_gate(0x2A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2A);
    set_gate(0x2B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2B);
    set_gate(0x2C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2C);
    set_gate(0x2D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2D);
    set_gate(0x2E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2E);
    set_gate(0x2F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_2F);
    set_gate(0x30, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_30);
    set_gate(0x31, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_31);
    set_gate(0x32, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_32);
    set_gate(0x33, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_33);
    set_gate(0x34, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_34);
    set_gate(0x35, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_35);
    set_gate(0x36, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_36);
    set_gate(0x37, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_37);
    set_gate(0x38, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_38);
    set_gate(0x39, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_39);
    set_gate(0x3A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3A);
    set_gate(0x3B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3B);
    set_gate(0x3C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3C);
    set_gate(0x3D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3D);
    set_gate(0x3E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3E);
    set_gate(0x3F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_3F);
    set_gate(0x40, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_40);
    set_gate(0x41, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_41);
    set_gate(0x42, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_42);
    set_gate(0x43, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_43);
    set_gate(0x44, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_44);
    set_gate(0x45, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_45);
    set_gate(0x46, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_46);
    set_gate(0x47, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_47);
    set_gate(0x48, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_48);
    set_gate(0x49, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_49);
    set_gate(0x4A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4A);
    set_gate(0x4B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4B);
    set_gate(0x4C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4C);
    set_gate(0x4D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4D);
    set_gate(0x4E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4E);
    set_gate(0x4F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_4F);
    set_gate(0x50, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_50);
    set_gate(0x51, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_51);
    set_gate(0x52, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_52);
    set_gate(0x53, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_53);
    set_gate(0x54, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_54);
    set_gate(0x55, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_55);
    set_gate(0x56, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_56);
    set_gate(0x57, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_57);
    set_gate(0x58, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_58);
    set_gate(0x59, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_59);
    set_gate(0x5A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5A);
    set_gate(0x5B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5B);
    set_gate(0x5C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5C);
    set_gate(0x5D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5D);
    set_gate(0x5E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5E);
    set_gate(0x5F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_5F);
    set_gate(0x60, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_60);
    set_gate(0x61, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_61);
    set_gate(0x62, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_62);
    set_gate(0x63, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_63);
    set_gate(0x64, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_64);
    set_gate(0x65, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_65);
    set_gate(0x66, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_66);
    set_gate(0x67, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_67);
    set_gate(0x68, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_68);
    set_gate(0x69, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_69);
    set_gate(0x6A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6A);
    set_gate(0x6B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6B);
    set_gate(0x6C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6C);
    set_gate(0x6D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6D);
    set_gate(0x6E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6E);
    set_gate(0x6F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_6F);
    set_gate(0x70, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_70);
    set_gate(0x71, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_71);
    set_gate(0x72, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_72);
    set_gate(0x73, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_73);
    set_gate(0x74, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_74);
    set_gate(0x75, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_75);
    set_gate(0x76, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_76);
    set_gate(0x77, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_77);
    set_gate(0x78, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_78);
    set_gate(0x79, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_79);
    set_gate(0x7A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7A);
    set_gate(0x7B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7B);
    set_gate(0x7C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7C);
    set_gate(0x7D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7D);
    set_gate(0x7E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7E);
    set_gate(0x7F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_7F);
    set_gate(0x80, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_80);
    set_gate(0x81, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_81);
    set_gate(0x82, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_82);
    set_gate(0x83, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_83);
    set_gate(0x84, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_84);
    set_gate(0x85, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_85);
    set_gate(0x86, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_86);
    set_gate(0x87, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_87);
    set_gate(0x88, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_88);
    set_gate(0x89, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_89);
    set_gate(0x8A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8A);
    set_gate(0x8B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8B);
    set_gate(0x8C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8C);
    set_gate(0x8D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8D);
    set_gate(0x8E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8E);
    set_gate(0x8F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_8F);
    set_gate(0x90, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_90);
    set_gate(0x91, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_91);
    set_gate(0x92, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_92);
    set_gate(0x93, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_93);
    set_gate(0x94, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_94);
    set_gate(0x95, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_95);
    set_gate(0x96, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_96);
    set_gate(0x97, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_97);
    set_gate(0x98, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_98);
    set_gate(0x99, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_99);
    set_gate(0x9A, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9A);
    set_gate(0x9B, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9B);
    set_gate(0x9C, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9C);
    set_gate(0x9D, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9D);
    set_gate(0x9E, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9E);
    set_gate(0x9F, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_9F);
    set_gate(0xA0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A0);
    set_gate(0xA1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A1);
    set_gate(0xA2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A2);
    set_gate(0xA3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A3);
    set_gate(0xA4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A4);
    set_gate(0xA5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A5);
    set_gate(0xA6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A6);
    set_gate(0xA7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A7);
    set_gate(0xA8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A8);
    set_gate(0xA9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_A9);
    set_gate(0xAA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AA);
    set_gate(0xAB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AB);
    set_gate(0xAC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AC);
    set_gate(0xAD, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AD);
    set_gate(0xAE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AE);
    set_gate(0xAF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_AF);
    set_gate(0xB0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B0);
    set_gate(0xB1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B1);
    set_gate(0xB2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B2);
    set_gate(0xB3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B3);
    set_gate(0xB4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B4);
    set_gate(0xB5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B5);
    set_gate(0xB6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B6);
    set_gate(0xB7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B7);
    set_gate(0xB8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B8);
    set_gate(0xB9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_B9);
    set_gate(0xBA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BA);
    set_gate(0xBB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BB);
    set_gate(0xBC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BC);
    set_gate(0xBD, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BD);
    set_gate(0xBE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BE);
    set_gate(0xBF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_BF);
    set_gate(0xC0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C0);
    set_gate(0xC1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C1);
    set_gate(0xC2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C2);
    set_gate(0xC3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C3);
    set_gate(0xC4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C4);
    set_gate(0xC5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C5);
    set_gate(0xC6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C6);
    set_gate(0xC7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C7);
    set_gate(0xC8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C8);
    set_gate(0xC9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_C9);
    set_gate(0xCA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CA);
    set_gate(0xCB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CB);
    set_gate(0xCC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CC);
    set_gate(0xCD, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CD);
    set_gate(0xCE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CE);
    set_gate(0xCF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_CF);
    set_gate(0xD0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D0);
    set_gate(0xD1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D1);
    set_gate(0xD2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D2);
    set_gate(0xD3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D3);
    set_gate(0xD4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D4);
    set_gate(0xD5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D5);
    set_gate(0xD6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D6);
    set_gate(0xD7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D7);
    set_gate(0xD8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D8);
    set_gate(0xD9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_D9);
    set_gate(0xDA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DA);
    set_gate(0xDB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DB);
    set_gate(0xDC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DC);
    set_gate(0xDD, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DD);
    set_gate(0xDE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DE);
    set_gate(0xDF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_DF);
    set_gate(0xE0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E0);
    set_gate(0xE1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E1);
    set_gate(0xE2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E2);
    set_gate(0xE3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E3);
    set_gate(0xE4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E4);
    set_gate(0xE5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E5);
    set_gate(0xE6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E6);
    set_gate(0xE7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E7);
    set_gate(0xE8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E8);
    set_gate(0xE9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_E9);
    set_gate(0xEA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_EA);
    set_gate(0xEB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_EB);
    set_gate(0xEC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_EC);
    set_gate(0xED, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_ED);
    set_gate(0xEE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_EE);
    set_gate(0xEF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_EF);
    set_gate(0xF0, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F0);
    set_gate(0xF1, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F1);
    set_gate(0xF2, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F2);
    set_gate(0xF3, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F3);
    set_gate(0xF4, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F4);
    set_gate(0xF5, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F5);
    set_gate(0xF6, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F6);
    set_gate(0xF7, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F7);
    set_gate(0xF8, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F8);
    set_gate(0xF9, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_F9);
    set_gate(0xFA, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FA);
    set_gate(0xFB, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FB);
    set_gate(0xFC, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FC);
    set_gate(0xFD, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FD);
    set_gate(0xFE, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FE);
    set_gate(0xFF, GDT_SELECTOR(0, 0, 1), GATE_TYPE_INTR, 0, intr_FF);

    idt_descr.size = (uint16_t)(sizeof(idt) - 1);
    idt_descr.offset = (uint32_t)(&idt);
    asm volatile("lidtl %0"::"m"(idt_descr));
}

int set_interrupt_handler(uint8_t int_no, interrupt_handler_t handler)
{
    if(handlers[int_no] != NULL)
        return 0;
    
    handlers[int_no] = handler;
    return 1;
}
