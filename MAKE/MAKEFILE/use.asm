
.\Build\use.o:     file format elf32-littlearm
.\Build\use.o
architecture: arm, flags 0x00000011:
HAS_RELOC, HAS_SYMS
start address 0x00000000
private flags = 5000000: [Version5 EABI]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000000  00000000  00000000  00000034  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000034  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000034  2**0
                  ALLOC
  3 .text.setup   0000006c  00000000  00000000  00000034  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  4 .text.loop    00000002  00000000  00000000  000000a0  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  5 .debug_info   00000230  00000000  00000000  000000a2  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  6 .debug_abbrev 000000e7  00000000  00000000  000002d2  2**0
                  CONTENTS, READONLY, DEBUGGING
  7 .debug_loc    00000020  00000000  00000000  000003b9  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  8 .debug_aranges 00000028  00000000  00000000  000003d9  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
  9 .debug_ranges 00000018  00000000  00000000  00000401  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
 10 .debug_line   000001be  00000000  00000000  00000419  2**0
                  CONTENTS, RELOC, READONLY, DEBUGGING
 11 .debug_str    0000027a  00000000  00000000  000005d7  2**0
                  CONTENTS, READONLY, DEBUGGING
 12 .comment      00000080  00000000  00000000  00000851  2**0
                  CONTENTS, READONLY
 13 .debug_frame  00000040  00000000  00000000  000008d4  2**2
                  CONTENTS, RELOC, READONLY, DEBUGGING
 14 .ARM.attributes 00000033  00000000  00000000  00000914  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
00000000 l    df *ABS*	00000000 use.c
00000000 l    d  .text	00000000 .text
00000000 l    d  .data	00000000 .data
00000000 l    d  .bss	00000000 .bss
00000000 l    d  .text.setup	00000000 .text.setup
00000000 l    d  .text.loop	00000000 .text.loop
00000000 l    d  .debug_info	00000000 .debug_info
00000000 l    d  .debug_abbrev	00000000 .debug_abbrev
00000000 l    d  .debug_loc	00000000 .debug_loc
00000000 l    d  .debug_aranges	00000000 .debug_aranges
00000000 l    d  .debug_ranges	00000000 .debug_ranges
00000000 l    d  .debug_line	00000000 .debug_line
00000000 l    d  .debug_str	00000000 .debug_str
00000000 l    d  .debug_frame	00000000 .debug_frame
00000000 l    d  .comment	00000000 .comment
00000000 l    d  .ARM.attributes	00000000 .ARM.attributes
00000000         *UND*	00000000 __aeabi_fadd
00000000         *UND*	00000000 __aeabi_fsub
00000000         *UND*	00000000 __aeabi_fmul
00000000         *UND*	00000000 __aeabi_fdiv
00000000 g     F .text.setup	0000006c setup
00000004       O *COM*	00000004 a
00000004       O *COM*	00000004 b
00000004       O *COM*	00000004 sum
00000004       O *COM*	00000004 subtraction
00000004       O *COM*	00000004 multiplication
00000004       O *COM*	00000004 division
00000004       O *COM*	00000004 end
00000000 g     F .text.loop	00000002 loop



Disassembly of section .text.setup:

00000000 <setup>:

volatile float a,b;
volatile float sum, subtraction, multiplication, division;
volatile uint32_t end;

extern void setup(void){
   0:	b538      	push	{r3, r4, r5, lr}
	a = 1.618;
   2:	4d11      	ldr	r5, [pc, #68]	; (48 <setup+0x48>)
   4:	4b11      	ldr	r3, [pc, #68]	; (4c <setup+0x4c>)
   6:	602b      	str	r3, [r5, #0]
	b = 3.124;
   8:	4c11      	ldr	r4, [pc, #68]	; (50 <setup+0x50>)
   a:	4b12      	ldr	r3, [pc, #72]	; (54 <setup+0x54>)
   c:	6023      	str	r3, [r4, #0]

	sum = a+ b;
   e:	6828      	ldr	r0, [r5, #0]
  10:	6821      	ldr	r1, [r4, #0]
  12:	f7ff fffe 	bl	0 <__aeabi_fadd>
			12: R_ARM_THM_CALL	__aeabi_fadd
  16:	4b10      	ldr	r3, [pc, #64]	; (58 <setup+0x58>)
  18:	6018      	str	r0, [r3, #0]
	subtraction = a- b;
  1a:	6828      	ldr	r0, [r5, #0]
  1c:	6821      	ldr	r1, [r4, #0]
  1e:	f7ff fffe 	bl	0 <__aeabi_fsub>
			1e: R_ARM_THM_CALL	__aeabi_fsub
  22:	4b0e      	ldr	r3, [pc, #56]	; (5c <setup+0x5c>)
  24:	6018      	str	r0, [r3, #0]
	multiplication  = a* b;
  26:	6828      	ldr	r0, [r5, #0]
  28:	6821      	ldr	r1, [r4, #0]
  2a:	f7ff fffe 	bl	0 <__aeabi_fmul>
			2a: R_ARM_THM_CALL	__aeabi_fmul
  2e:	4b0c      	ldr	r3, [pc, #48]	; (60 <setup+0x60>)
  30:	6018      	str	r0, [r3, #0]
	division = a/ b;
  32:	6828      	ldr	r0, [r5, #0]
  34:	6821      	ldr	r1, [r4, #0]
  36:	f7ff fffe 	bl	0 <__aeabi_fdiv>
			36: R_ARM_THM_CALL	__aeabi_fdiv
  3a:	4b0a      	ldr	r3, [pc, #40]	; (64 <setup+0x64>)
  3c:	6018      	str	r0, [r3, #0]

	end = 0xf0f0f0f0;
  3e:	4b0a      	ldr	r3, [pc, #40]	; (68 <setup+0x68>)
  40:	f04f 32f0 	mov.w	r2, #4042322160	; 0xf0f0f0f0
  44:	601a      	str	r2, [r3, #0]
}
  46:	bd38      	pop	{r3, r4, r5, pc}
  48:	00000000 	.word	0x00000000
			48: R_ARM_ABS32	a
  4c:	3fcf1aa0 	.word	0x3fcf1aa0
  50:	00000000 	.word	0x00000000
			50: R_ARM_ABS32	b
  54:	4047ef9e 	.word	0x4047ef9e
	...
			58: R_ARM_ABS32	sum
			5c: R_ARM_ABS32	subtraction
			60: R_ARM_ABS32	multiplication
			64: R_ARM_ABS32	division
			68: R_ARM_ABS32	end

Disassembly of section .text.loop:

00000000 <loop>:

extern void loop(void){
}
   0:	4770      	bx	lr
