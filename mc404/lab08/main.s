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
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI0:
	add	fp, sp, #4
.LCFI1:
	sub	sp, sp, #64
.LCFI2:
	.loc 1 10 0
	mov	r0, #60
	mov	r1, #60
	bl	set_speed_motors
.L10:
	.loc 1 15 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-56]
	.loc 1 16 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-52]
	.loc 1 19 0
	b	.L2
.L4:
	.loc 1 21 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-56]
	.loc 1 22 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-52]
.L2:
	.loc 1 19 0
	ldr	r3, [fp, #-56]
	cmp	r3, #1200
	bls	.L3
	ldr	r3, [fp, #-52]
	cmp	r3, #1200
	bhi	.L4
.L3:
	.loc 1 26 0
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 27 0
	sub	r3, fp, #68
	mov	r0, r3
	bl	read_sonars
	.loc 1 30 0
	ldr	r2, [fp, #-40]
	ldr	r3, [fp, #-68]
	cmp	r2, r3
	bhi	.L5
	ldr	r2, [fp, #-36]
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	bls	.L6
.L5:
	.loc 1 32 0
	mov	r0, #0
	mov	r1, #5
	bl	set_speed_motors
	.loc 1 30 0
	mov	r0, r0	@ nop
	.loc 1 41 0
	b	.L8
.L6:
	.loc 1 37 0
	mov	r0, #5
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 41 0
	b	.L8
.L9:
	.loc 1 43 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-56]
	.loc 1 44 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	str	r3, [fp, #-52]
.L8:
	.loc 1 41 0
	ldr	r2, [fp, #-56]
	ldr	r3, .L12
	cmp	r2, r3
	bls	.L9
	ldr	r2, [fp, #-52]
	ldr	r3, .L12
	cmp	r2, r3
	bls	.L9
	.loc 1 46 0
	mov	r0, #60
	mov	r1, #60
	bl	set_speed_motors
	.loc 1 47 0
	b	.L10
.L13:
	.align	2
.L12:
	.word	1199
.LFE0:
	.size	_start, .-_start
	.align	2
	.global	delay
	.type	delay, %function
delay:
.LFB1:
	.loc 1 52 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI3:
	add	fp, sp, #0
.LCFI4:
	sub	sp, sp, #12
.LCFI5:
	.loc 1 55 0
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L15
.L16:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L15:
	ldr	r2, [fp, #-8]
	ldr	r3, .L18
	cmp	r2, r3
	ble	.L16
	.loc 1 56 0
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L19:
	.align	2
.L18:
	.word	9999
.LFE1:
	.size	delay, .-delay
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
	.uleb128 0x4
	.byte	0x11
	.uleb128 0xb
	.sleb128 1
	.byte	0x4
	.4byte	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0xb
	.align	2
.LEFDE2:
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
	.sleb128 4
	.4byte	.LCFI4-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
	.section	.debug_info
	.4byte	0x91
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF2
	.byte	0x1
	.4byte	.LASF3
	.4byte	.LASF4
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.4byte	.LASF5
	.byte	0x1
	.byte	0x6
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LLST0
	.4byte	0x4e
	.uleb128 0x3
	.4byte	.LASF0
	.byte	0x1
	.byte	0x8
	.4byte	0x4e
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.byte	0x0
	.uleb128 0x4
	.4byte	0x61
	.4byte	0x5e
	.uleb128 0x5
	.4byte	0x5e
	.byte	0xf
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.byte	0x7
	.uleb128 0x7
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.uleb128 0x8
	.byte	0x1
	.4byte	.LASF6
	.byte	0x1
	.byte	0x33
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LLST1
	.4byte	0x8d
	.uleb128 0x9
	.ascii	"i\000"
	.byte	0x1
	.byte	0x35
	.4byte	0x8d
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0xa
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
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
	.uleb128 0x3
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
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xa
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x23
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x95
	.4byte	0x25
	.ascii	"_start\000"
	.4byte	0x68
	.ascii	"delay\000"
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
.LASF1:
	.ascii	"unsigned int\000"
.LASF5:
	.ascii	"_start\000"
.LASF2:
	.ascii	"GNU C 4.4.3\000"
.LASF3:
	.ascii	"main.c\000"
.LASF4:
	.ascii	"/home/vaoki/ec/mc404/lab08\000"
.LASF0:
	.ascii	"distances\000"
.LASF6:
	.ascii	"delay\000"
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
