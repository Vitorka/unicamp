	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.align	2
	.global	_start
	.type	_start, %function
_start:
.LFB0:
	.file 1 "main.c"
	.loc 1 7 0
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI0:
	add	fp, sp, #4
.LCFI1:
	sub	sp, sp, #16
.LCFI2:
	.loc 1 14 0
	mov	r3, #36
	strb	r3, [fp, #-15]
	.loc 1 15 0
	mov	r3, #36
	strb	r3, [fp, #-19]
	.loc 1 16 0
	mov	r3, #0
	strb	r3, [fp, #-16]
	.loc 1 17 0
	mov	r3, #1
	strb	r3, [fp, #-20]
	.loc 1 19 0
	sub	r2, fp, #16
	sub	r3, fp, #20
	mov	r0, r2
	mov	r1, r3
	bl	set_motors_speed
	.loc 1 20 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
.L7:
	.loc 1 25 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 26 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	.loc 1 28 0
	b	.L2
.L4:
	.loc 1 30 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 31 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
.L2:
	.loc 1 28 0
	ldr	r3, [fp, #-12]
	cmp	r3, #1200
	bls	.L3
	ldr	r3, [fp, #-8]
	cmp	r3, #1200
	bhi	.L4
.L3:
	.loc 1 34 0
	mov	r3, #0
	strb	r3, [fp, #-15]
	.loc 1 35 0
	mov	r3, #1
	strb	r3, [fp, #-19]
	.loc 1 36 0
	sub	r2, fp, #16
	sub	r3, fp, #20
	mov	r0, r2
	mov	r1, r3
	bl	set_motors_speed
	.loc 1 38 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 39 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
	.loc 1 41 0
	mov	r3, #0
	strb	r3, [fp, #-15]
	.loc 1 42 0
	mov	r3, #5
	strb	r3, [fp, #-19]
	.loc 1 43 0
	sub	r2, fp, #16
	sub	r3, fp, #20
	mov	r0, r2
	mov	r1, r3
	bl	set_motors_speed
	.loc 1 45 0
	b	.L5
.L6:
	.loc 1 47 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-12]
	.loc 1 48 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-8]
.L5:
	.loc 1 45 0
	ldr	r2, [fp, #-12]
	ldr	r3, .L9
	cmp	r2, r3
	bls	.L6
	ldr	r2, [fp, #-8]
	ldr	r3, .L9
	cmp	r2, r3
	bls	.L6
	.loc 1 51 0
	mov	r3, #36
	strb	r3, [fp, #-15]
	.loc 1 52 0
	mov	r3, #36
	strb	r3, [fp, #-19]
	.loc 1 53 0
	sub	r2, fp, #16
	sub	r3, fp, #20
	mov	r0, r2
	mov	r1, r3
	bl	set_motors_speed
	.loc 1 55 0
	b	.L7
.L10:
	.align	2
.L9:
	.word	1199
.LFE0:
	.size	_start, .-_start
	.align	2
	.global	para_robo
	.type	para_robo, %function
para_robo:
.LFB1:
	.loc 1 59 0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI3:
	add	fp, sp, #4
.LCFI4:
	.loc 1 60 0
	mov	r0, #0
	mov	r1, #0
	bl	set_motors_speed
	.loc 1 61 0
	ldmfd	sp!, {fp, pc}
.LFE1:
	.size	para_robo, .-para_robo
	.align	2
	.global	para_robo2
	.type	para_robo2, %function
para_robo2:
.LFB2:
	.loc 1 63 0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI5:
	add	fp, sp, #4
.LCFI6:
	.loc 1 64 0
	mov	r0, #2
	bl	read_sonar
	.loc 1 65 0
	ldmfd	sp!, {fp, pc}
.LFE2:
	.size	para_robo2, .-para_robo2
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI3-.LFB1
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI4-.LCFI3
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI5-.LFB2
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE4:
	.text
.Letext0:
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB0-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0-.Ltext0
	.4byte	.LCFI1-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST1:
	.4byte	.LFB1-.Ltext0
	.4byte	.LCFI3-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3-.Ltext0
	.4byte	.LCFI4-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI4-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST2:
	.4byte	.LFB2-.Ltext0
	.4byte	.LCFI5-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5-.Ltext0
	.4byte	.LCFI6-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI6-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
	.file 2 "api_robot2.h"
	.section	.debug_info
	.4byte	0xd9
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF9
	.byte	0x1
	.4byte	.LASF10
	.4byte	.LASF11
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x2
	.byte	0x16
	.4byte	0x49
	.uleb128 0x3
	.ascii	"id\000"
	.byte	0x2
	.byte	0x17
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x4
	.4byte	.LASF0
	.byte	0x2
	.byte	0x18
	.4byte	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x6
	.4byte	.LASF12
	.byte	0x2
	.byte	0x19
	.4byte	0x25
	.uleb128 0x7
	.byte	0x1
	.4byte	.LASF13
	.byte	0x1
	.byte	0x6
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LLST0
	.4byte	0xad
	.uleb128 0x8
	.4byte	.LASF1
	.byte	0x1
	.byte	0x8
	.4byte	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x8
	.4byte	.LASF2
	.byte	0x1
	.byte	0x9
	.4byte	0xad
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x8
	.4byte	.LASF3
	.byte	0x1
	.byte	0xb
	.4byte	0x50
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.4byte	.LASF4
	.byte	0x1
	.byte	0xc
	.4byte	0x50
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.byte	0x0
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF7
	.byte	0x1
	.byte	0x3b
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LLST1
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF8
	.byte	0x1
	.byte	0x3f
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LLST2
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x36
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0xdd
	.4byte	0x5b
	.ascii	"_start\000"
	.4byte	0xb4
	.ascii	"para_robo\000"
	.4byte	0xc8
	.ascii	"para_robo2\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",%progbits,1
.LASF11:
	.ascii	"/home/ec2015/ra178474/ec/mc404/Trabalho2/Trabfinal\000"
.LASF13:
	.ascii	"_start\000"
.LASF3:
	.ascii	"motor0\000"
.LASF6:
	.ascii	"unsigned int\000"
.LASF12:
	.ascii	"motor_cfg_t\000"
.LASF0:
	.ascii	"speed\000"
.LASF4:
	.ascii	"motor1\000"
.LASF7:
	.ascii	"para_robo\000"
.LASF8:
	.ascii	"para_robo2\000"
.LASF10:
	.ascii	"main.c\000"
.LASF5:
	.ascii	"unsigned char\000"
.LASF1:
	.ascii	"distancia3\000"
.LASF2:
	.ascii	"distancia4\000"
.LASF9:
	.ascii	"GNU C 4.4.3\000"
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
