	.file	1 "Canny_Simplified.c"
	.globl	src
	.align	2
src:
	.word	8192
	.globl	dst
	.align	2
dst:
	.word	16384
	.text
	.align	2
	.globl	convolution
convolution:
	.frame	$fp,40,$31		# vars= 32, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$fp,36($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	sw	$5,44($fp)
	sw	$6,48($fp)
	sw	$7,52($fp)
	sw	$0,0($fp)
	j	.L2
.L9:
	sw	$0,4($fp)
	j	.L3
.L8:
	sw	$0,16($fp)
	sw	$0,12($fp)
	j	.L4
.L7:
	sw	$0,8($fp)
	j	.L5
.L6:
	lw	$2,52($fp)
	srl	$3,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	move	$3,$2
	lw	$2,8($fp)
	subu	$3,$2,$3
	lw	$2,4($fp)
	addu	$2,$3,$2
	slt	$3,$2,0
	movn	$2,$0,$3
	sw	$2,20($fp)
	lw	$2,48($fp)
	srl	$3,$2,31
	addu	$2,$3,$2
	sra	$2,$2,1
	move	$3,$2
	lw	$2,12($fp)
	subu	$3,$2,$3
	lw	$2,0($fp)
	addu	$2,$3,$2
	slt	$3,$2,0
	movn	$2,$0,$3
	sw	$2,24($fp)
	lw	$3,12($fp)
	lw	$2,52($fp)
	mult	$3,$2
	lw	$2,8($fp)
	mflo	$3
	addu	$2,$3,$2
	move	$3,$2
	lw	$2,40($fp)
	addu	$2,$2,$3
	lbu	$2,0($2)
	move	$5,$2
	lw	$2,src
	lw	$4,24($fp)
	lw	$3,60($fp)
	mult	$4,$3
	lw	$3,20($fp)
	mflo	$4
	addu	$3,$4,$3
	addu	$2,$2,$3
	lbu	$2,0($2)
	mult	$5,$2
	lw	$2,16($fp)
	mflo	$5
	addu	$2,$2,$5
	sw	$2,16($fp)
	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
.L5:
	lw	$3,8($fp)
	lw	$2,52($fp)
	slt	$2,$3,$2
	bne	$2,$0,.L6
	lw	$2,12($fp)
	addiu	$2,$2,1
	sw	$2,12($fp)
.L4:
	lw	$3,12($fp)
	lw	$2,48($fp)
	slt	$2,$3,$2
	bne	$2,$0,.L7
	lw	$2,dst
	lw	$4,0($fp)
	lw	$3,60($fp)
	mult	$4,$3
	lw	$3,4($fp)
	mflo	$4
	addu	$3,$4,$3
	addu	$2,$2,$3
	lw	$3,dst
	lw	$5,0($fp)
	lw	$4,60($fp)
	mult	$5,$4
	lw	$4,4($fp)
	mflo	$5
	addu	$4,$5,$4
	addu	$3,$3,$4
	lbu	$4,0($3)
	lw	$5,16($fp)
	lw	$3,44($fp)
	div	$0,$5,$3
	mfhi	$3
	mflo	$3
	andi	$3,$3,0x00ff
	addu	$3,$4,$3
	andi	$3,$3,0x00ff
	sb	$3,0($2)
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
.L3:
	lw	$3,4($fp)
	lw	$2,60($fp)
	slt	$2,$3,$2
	bne	$2,$0,.L8
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
.L2:
	lw	$3,0($fp)
	lw	$2,56($fp)
	slt	$2,$3,$2
	bne	$2,$0,.L9
	move	$sp,$fp
	lw	$fp,36($sp)
	addiu	$sp,$sp,40
	j	$31
	.end	convolution
	.rdata
	.align	2
.LC0:
	.byte	-1
	.byte	0
	.byte	1
	.byte	-2
	.byte	0
	.byte	2
	.byte	-1
	.byte	0
	.byte	1
	.text
	.align	2
	.globl	sobel_gx
sobel_gx:
	.frame	$fp,48,$31		# vars= 16, regs= 2/0, args= 24, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	sw	$5,52($fp)
	lwl	$2,.LC0
	move	$3,$2
	lwr	$3,.LC0+3
	lwl	$2,.LC0+4
	lwr	$2,.LC0+7
	sw	$3,24($fp)
	sw	$2,28($fp)
	lbu	$2,.LC0+8
	sb	$2,32($fp)
	lw	$2,52($fp)
	sw	$2,16($sp)
	lw	$2,48($fp)
	sw	$2,20($sp)
	addiu	$2,$fp,24
	move	$4,$2
	li	$5,1			# 0x1
	li	$6,3			# 0x3
	li	$7,3			# 0x3
	jal	convolution
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	j	$31
	.end	sobel_gx
	.rdata
	.align	2
.LC1:
	.byte	-1
	.byte	-2
	.byte	-1
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	2
	.byte	1
	.text
	.align	2
	.globl	sobel_gy
sobel_gy:
	.frame	$fp,48,$31		# vars= 16, regs= 2/0, args= 24, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	move	$fp,$sp
	sw	$4,48($fp)
	sw	$5,52($fp)
	lwl	$2,.LC1
	move	$3,$2
	lwr	$3,.LC1+3
	lwl	$2,.LC1+4
	lwr	$2,.LC1+7
	sw	$3,24($fp)
	sw	$2,28($fp)
	lbu	$2,.LC1+8
	sb	$2,32($fp)
	lw	$2,52($fp)
	sw	$2,16($sp)
	lw	$2,48($fp)
	sw	$2,20($sp)
	addiu	$2,$fp,24
	move	$4,$2
	li	$5,1			# 0x1
	li	$6,3			# 0x3
	li	$7,3			# 0x3
	jal	convolution
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	addiu	$sp,$sp,48
	j	$31
	.end	sobel_gy
	.align	2
	.globl	main
main:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	li	$2,96			# 0x60
	sw	$2,16($fp)
	li	$2,96			# 0x60
	sw	$2,20($fp)
	lw	$4,16($fp)
	lw	$5,20($fp)
	jal	sobel_gy
	lw	$4,16($fp)
	lw	$5,20($fp)
	jal	sobel_gx
 #APP
 # 55 "Canny_Simplified.c" 1
	syscall
 # 0 "" 2
 #NO_APP
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	.end	main
