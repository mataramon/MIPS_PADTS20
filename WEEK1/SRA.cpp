MIPS32::instr_t mips32::decode(uint32_t idata)
{
	
	switch (instr.opcode) {
	case OP_SPECIAL:
		switch (instr.funct_1) {
		case S1F1_SRA:		instr.name = MIPS32::SRA; break;
}

void mips32::execute(MIPS32::instr_t instr)
{

		// ************************
		// Shift Instructions
		// ************************
	case MIPS32::SRA: // Shift Word Right Arithmetic
		if (verbose) printf("SRA instruction catched, 0x%08x: SUB r%d, r%d, r%d\n", PC, instr.rd, instr.rt, instr.sa);
		int8_t s;
		uint32_t temp32;

		s = instr.sa;
		temp32 = GPR[inst.rt] >> s;	
		GPR[instr.rd] = temp32;	

}
