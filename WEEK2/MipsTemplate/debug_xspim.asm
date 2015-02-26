	.text
	.globl	main
main:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	sb	$0,4($fp)
	sb	$0,5($fp)
	sw	$0,0($fp)
	j	.L2
.L3:
	lbu	$2,4($fp)
	andi	$3,$2,0x00ff
	lbu	$2,4($fp)
	andi	$2,$2,0x00ff
	addu	$2,$3,$2
	andi	$2,$2,0x00ff
	addiu	$2,$2,1
	andi	$2,$2,0x00ff
	sb	$2,4($fp)
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
.L2:
	lw	$2,0($fp)
	slt	$2,$2,10
	bne	$2,$0,.L3
	lbu	$2,4($fp)
	andi	$2,$2,0x00ff
	sb	$2,5($fp)
 #APP
 # 11 "mips_fw.c" 1
	syscall
 # 0 "" 2
 #NO_APP
	move	$2,$0
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	.end	main
