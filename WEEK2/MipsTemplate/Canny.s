
Canny.elf:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <convolution>:
   0:	27bdffd8 	addiu	sp,sp,-40
   4:	afbe0024 	sw	s8,36(sp)
   8:	03a0f021 	move	s8,sp
   c:	afc40028 	sw	a0,40(s8)
  10:	afc5002c 	sw	a1,44(s8)
  14:	afc60030 	sw	a2,48(s8)
  18:	afc70034 	sw	a3,52(s8)
  1c:	afc00000 	sw	zero,0(s8)
  20:	0800007a 	j	1e8 <convolution+0x1e8>
  24:	00000000 	nop
  28:	afc00004 	sw	zero,4(s8)
  2c:	08000072 	j	1c8 <convolution+0x1c8>
  30:	00000000 	nop
  34:	afc00010 	sw	zero,16(s8)
  38:	afc0000c 	sw	zero,12(s8)
  3c:	08000050 	j	140 <convolution+0x140>
  40:	00000000 	nop
  44:	afc00008 	sw	zero,8(s8)
  48:	08000048 	j	120 <convolution+0x120>
  4c:	00000000 	nop
  50:	8fc20034 	lw	v0,52(s8)
  54:	00021fc2 	srl	v1,v0,0x1f
  58:	00621021 	addu	v0,v1,v0
  5c:	00021043 	sra	v0,v0,0x1
  60:	00401821 	move	v1,v0
  64:	8fc20008 	lw	v0,8(s8)
  68:	00431823 	subu	v1,v0,v1
  6c:	8fc20004 	lw	v0,4(s8)
  70:	00621021 	addu	v0,v1,v0
  74:	28430000 	slti	v1,v0,0
  78:	0003100b 	movn	v0,zero,v1
  7c:	afc20014 	sw	v0,20(s8)
  80:	8fc20030 	lw	v0,48(s8)
  84:	00021fc2 	srl	v1,v0,0x1f
  88:	00621021 	addu	v0,v1,v0
  8c:	00021043 	sra	v0,v0,0x1
  90:	00401821 	move	v1,v0
  94:	8fc2000c 	lw	v0,12(s8)
  98:	00431823 	subu	v1,v0,v1
  9c:	8fc20000 	lw	v0,0(s8)
  a0:	00621021 	addu	v0,v1,v0
  a4:	28430000 	slti	v1,v0,0
  a8:	0003100b 	movn	v0,zero,v1
  ac:	afc20018 	sw	v0,24(s8)
  b0:	8fc3000c 	lw	v1,12(s8)
  b4:	8fc20034 	lw	v0,52(s8)
  b8:	00620018 	mult	v1,v0
  bc:	8fc20008 	lw	v0,8(s8)
  c0:	00001812 	mflo	v1
  c4:	00621021 	addu	v0,v1,v0
  c8:	00401821 	move	v1,v0
  cc:	8fc20028 	lw	v0,40(s8)
  d0:	00431021 	addu	v0,v0,v1
  d4:	90420000 	lbu	v0,0(v0)
  d8:	00402821 	move	a1,v0
  dc:	8f820000 	lw	v0,0(gp)
  e0:	8fc40018 	lw	a0,24(s8)
  e4:	8fc3003c 	lw	v1,60(s8)
  e8:	00830018 	mult	a0,v1
  ec:	8fc30014 	lw	v1,20(s8)
  f0:	00002012 	mflo	a0
  f4:	00831821 	addu	v1,a0,v1
  f8:	00431021 	addu	v0,v0,v1
  fc:	90420000 	lbu	v0,0(v0)
 100:	00a20018 	mult	a1,v0
 104:	8fc20010 	lw	v0,16(s8)
 108:	00002812 	mflo	a1
 10c:	00451021 	addu	v0,v0,a1
 110:	afc20010 	sw	v0,16(s8)
 114:	8fc20008 	lw	v0,8(s8)
 118:	24420001 	addiu	v0,v0,1
 11c:	afc20008 	sw	v0,8(s8)
 120:	8fc30008 	lw	v1,8(s8)
 124:	8fc20034 	lw	v0,52(s8)
 128:	0062102a 	slt	v0,v1,v0
 12c:	1440ffc8 	bnez	v0,50 <convolution+0x50>
 130:	00000000 	nop
 134:	8fc2000c 	lw	v0,12(s8)
 138:	24420001 	addiu	v0,v0,1
 13c:	afc2000c 	sw	v0,12(s8)
 140:	8fc3000c 	lw	v1,12(s8)
 144:	8fc20030 	lw	v0,48(s8)
 148:	0062102a 	slt	v0,v1,v0
 14c:	1440ffbd 	bnez	v0,44 <convolution+0x44>
 150:	00000000 	nop
 154:	8f820000 	lw	v0,0(gp)
 158:	8fc40000 	lw	a0,0(s8)
 15c:	8fc3003c 	lw	v1,60(s8)
 160:	00830018 	mult	a0,v1
 164:	8fc30004 	lw	v1,4(s8)
 168:	00002012 	mflo	a0
 16c:	00831821 	addu	v1,a0,v1
 170:	00431021 	addu	v0,v0,v1
 174:	8f830000 	lw	v1,0(gp)
 178:	8fc50000 	lw	a1,0(s8)
 17c:	8fc4003c 	lw	a0,60(s8)
 180:	00a40018 	mult	a1,a0
 184:	8fc40004 	lw	a0,4(s8)
 188:	00002812 	mflo	a1
 18c:	00a42021 	addu	a0,a1,a0
 190:	00641821 	addu	v1,v1,a0
 194:	90640000 	lbu	a0,0(v1)
 198:	8fc50010 	lw	a1,16(s8)
 19c:	8fc3002c 	lw	v1,44(s8)
 1a0:	00a3001a 	div	zero,a1,v1
 1a4:	00001810 	mfhi	v1
 1a8:	00001812 	mflo	v1
 1ac:	306300ff 	andi	v1,v1,0xff
 1b0:	00831821 	addu	v1,a0,v1
 1b4:	306300ff 	andi	v1,v1,0xff
 1b8:	a0430000 	sb	v1,0(v0)
 1bc:	8fc20004 	lw	v0,4(s8)
 1c0:	24420001 	addiu	v0,v0,1
 1c4:	afc20004 	sw	v0,4(s8)
 1c8:	8fc30004 	lw	v1,4(s8)
 1cc:	8fc2003c 	lw	v0,60(s8)
 1d0:	0062102a 	slt	v0,v1,v0
 1d4:	1440ff97 	bnez	v0,34 <convolution+0x34>
 1d8:	00000000 	nop
 1dc:	8fc20000 	lw	v0,0(s8)
 1e0:	24420001 	addiu	v0,v0,1
 1e4:	afc20000 	sw	v0,0(s8)
 1e8:	8fc30000 	lw	v1,0(s8)
 1ec:	8fc20038 	lw	v0,56(s8)
 1f0:	0062102a 	slt	v0,v1,v0
 1f4:	1440ff8c 	bnez	v0,28 <convolution+0x28>
 1f8:	00000000 	nop
 1fc:	03c0e821 	move	sp,s8
 200:	8fbe0024 	lw	s8,36(sp)
 204:	27bd0028 	addiu	sp,sp,40
 208:	03e00008 	jr	ra
 20c:	00000000 	nop

00000210 <sobel_gx>:
 210:	27bdffd0 	addiu	sp,sp,-48
 214:	afbf002c 	sw	ra,44(sp)
 218:	afbe0028 	sw	s8,40(sp)
 21c:	03a0f021 	move	s8,sp
 220:	afc40030 	sw	a0,48(s8)
 224:	afc50034 	sw	a1,52(s8)
 228:	3c010000 	lui	at,0x0
 22c:	88220000 	lwl	v0,0(at)
 230:	00401821 	move	v1,v0
 234:	3c010000 	lui	at,0x0
 238:	98230003 	lwr	v1,3(at)
 23c:	3c010000 	lui	at,0x0
 240:	88220004 	lwl	v0,4(at)
 244:	3c010000 	lui	at,0x0
 248:	98220007 	lwr	v0,7(at)
 24c:	afc30018 	sw	v1,24(s8)
 250:	afc2001c 	sw	v0,28(s8)
 254:	3c020000 	lui	v0,0x0
 258:	90420008 	lbu	v0,8(v0)
 25c:	a3c20020 	sb	v0,32(s8)
 260:	8fc20034 	lw	v0,52(s8)
 264:	afa20010 	sw	v0,16(sp)
 268:	8fc20030 	lw	v0,48(s8)
 26c:	afa20014 	sw	v0,20(sp)
 270:	27c20018 	addiu	v0,s8,24
 274:	00402021 	move	a0,v0
 278:	24050001 	li	a1,1
 27c:	24060003 	li	a2,3
 280:	24070003 	li	a3,3
 284:	0c000000 	jal	0 <convolution>
 288:	00000000 	nop
 28c:	03c0e821 	move	sp,s8
 290:	8fbf002c 	lw	ra,44(sp)
 294:	8fbe0028 	lw	s8,40(sp)
 298:	27bd0030 	addiu	sp,sp,48
 29c:	03e00008 	jr	ra
 2a0:	00000000 	nop

000002a4 <sobel_gy>:
 2a4:	27bdffd0 	addiu	sp,sp,-48
 2a8:	afbf002c 	sw	ra,44(sp)
 2ac:	afbe0028 	sw	s8,40(sp)
 2b0:	03a0f021 	move	s8,sp
 2b4:	afc40030 	sw	a0,48(s8)
 2b8:	afc50034 	sw	a1,52(s8)
 2bc:	3c010000 	lui	at,0x0
 2c0:	8822000c 	lwl	v0,12(at)
 2c4:	00401821 	move	v1,v0
 2c8:	3c010000 	lui	at,0x0
 2cc:	9823000f 	lwr	v1,15(at)
 2d0:	3c010000 	lui	at,0x0
 2d4:	88220010 	lwl	v0,16(at)
 2d8:	3c010000 	lui	at,0x0
 2dc:	98220013 	lwr	v0,19(at)
 2e0:	afc30018 	sw	v1,24(s8)
 2e4:	afc2001c 	sw	v0,28(s8)
 2e8:	3c020000 	lui	v0,0x0
 2ec:	90420014 	lbu	v0,20(v0)
 2f0:	a3c20020 	sb	v0,32(s8)
 2f4:	8fc20034 	lw	v0,52(s8)
 2f8:	afa20010 	sw	v0,16(sp)
 2fc:	8fc20030 	lw	v0,48(s8)
 300:	afa20014 	sw	v0,20(sp)
 304:	27c20018 	addiu	v0,s8,24
 308:	00402021 	move	a0,v0
 30c:	24050001 	li	a1,1
 310:	24060003 	li	a2,3
 314:	24070003 	li	a3,3
 318:	0c000000 	jal	0 <convolution>
 31c:	00000000 	nop
 320:	03c0e821 	move	sp,s8
 324:	8fbf002c 	lw	ra,44(sp)
 328:	8fbe0028 	lw	s8,40(sp)
 32c:	27bd0030 	addiu	sp,sp,48
 330:	03e00008 	jr	ra
 334:	00000000 	nop

00000338 <main>:
 338:	27bdffe0 	addiu	sp,sp,-32
 33c:	afbf001c 	sw	ra,28(sp)
 340:	afbe0018 	sw	s8,24(sp)
 344:	03a0f021 	move	s8,sp
 348:	24020060 	li	v0,96
 34c:	afc20010 	sw	v0,16(s8)
 350:	24020060 	li	v0,96
 354:	afc20014 	sw	v0,20(s8)
 358:	8fc40010 	lw	a0,16(s8)
 35c:	8fc50014 	lw	a1,20(s8)
 360:	0c000000 	jal	0 <convolution>
 364:	00000000 	nop
 368:	8fc40010 	lw	a0,16(s8)
 36c:	8fc50014 	lw	a1,20(s8)
 370:	0c000000 	jal	0 <convolution>
 374:	00000000 	nop
 378:	0000000c 	syscall
 37c:	00001021 	move	v0,zero
 380:	03c0e821 	move	sp,s8
 384:	8fbf001c 	lw	ra,28(sp)
 388:	8fbe0018 	lw	s8,24(sp)
 38c:	27bd0020 	addiu	sp,sp,32
 390:	03e00008 	jr	ra
 394:	00000000 	nop
