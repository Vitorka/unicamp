	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 18, 4
	.file	"prova.c"
	.text
	.align	2
	.global	_start
	.type	_start, %function
_start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	_start, .-_start
	.align	2
	.global	do_something
	.type	do_something, %function
do_something:
	@ args = 8, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L8
	str	lr, [sp, #-4]!
	ldrsh	r3, [r3, #0]
	sub	sp, sp, #12
	mov	ip, #0
.L4:
	ldrh	lr, [r0, ip]
	strh	lr, [sp, #6]	@ movhi
	mov	lr, lr, asl #16
	cmp	r3, lr, asr #16
	add	ip, ip, #2
	bne	.L4
	mov	r1, r2
	add	r0, sp, #6
	bl	check
	ldrh	r3, [sp, #6]
	ldr	r0, [sp, #20]
	add	r0, r0, r3
	mov	r0, r0, asl #16
	mov	r0, r0, asr #16
	add	sp, sp, #12
	ldmfd	sp!, {pc}
.L9:
	.align	2
.L8:
	.word	key
	.size	do_something, .-do_something
	.comm	key,2,2
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
