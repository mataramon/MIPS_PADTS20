#include "mips32.h"

void mips32::pic(uint8_t n)
{
	bool STATUS_IE = (CP0R.Status & 0x1) ? true : false;

	uint8_t STATUS_IM = ((CP0R.Status & 0xFF00) >> 8);

	irq_handler = entry_addr + (2 << 3) + (n << 2);

	if (STATUS_IE) {
		if ((1 << n) & STATUS_IM) {
			if (verbose) printf("\n\nMIPS IRQ %d Received\n\n", n);
			irq_evt = true;
			sleep = false;
		}
		else {
			irq_evt = false;
		}
	}
	else {
		irq_evt = false;
	}
}

mips32::mips32(bool vb)
{
	verbose = vb;
	sleep = true;
	done = false;
	CP0RP = (uint32_t*)&CP0R;
	cntr = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
}

bool mips32::get_status(uint8_t param)
{
	bool res;

	switch (param) {
	case 0: res = sleep; break;
	case 1: res = done; break;
	}

	return res;
}

void mips32::reset(uint32_t init_PC)
{
	if (verbose) printf("\n\n*** MIPS32 Reset ***\n\n");

	for (int i = 0; i < 32; i++)
		GPR[i] = 0;
	HI = 0;
	LO = 0;
	entry_addr = init_PC;
	PC = entry_addr;
	next_PC = entry_addr;

	for (int i = 0; i < 32; i++)
		CP0RP[i] = 0;

	for (int i = 0; i < 32; i++)
		FPR[i] = 0;
	FCR0 = 0;
	FCR25 = 0;
	FCR26 = 0;
	FCR28 = 0;
	FCSR = 0;
	LLbit = 0;
	irq_evt = false;
	sleep = true;
}

void mips32::run(void)
{
	sleep = false;
}

uint32_t mips32::fetch(void)
{
	if (irq_evt == true) {
		PC = irq_handler;
		CP0R.EPC = next_PC;
		irq_evt = false;
	}
	else {
		PC = next_PC;
	}
	uint32_t pAddr = AddressTranslation(PC, MIPS32::INSTRUCTION, MIPS32::LOAD);
	int32_t memword = LoadMemory(MIPS32::WORD, pAddr, PC, MIPS32::INSTRUCTION);

	return memword;
}

MIPS32::instr_t mips32::decode(uint32_t idata)
{
	MIPS32::instr_t instr;

	instr.opcode = (idata & 0xFC000000) >> 26;
	instr.funct_3 = (idata & 0x03E00000) >> 21;
	instr.rs = (idata & 0x03E00000) >> 21;
	instr.rt = (idata & 0x001F0000) >> 16;
	instr.rd = (idata & 0x0000F800) >> 11;
	instr.immediate = (idata & 0x0000FFFF) >> 16;
	instr.funct_1=(idata &0x0000003F) >> 6;
	instr.offset=(idata & 0x0000FFFF) >> 16;
	instr.base=(idata & 0x03E00000) >> 21;
	

	switch (instr.opcode) {
	case OP_SPECIAL:
		switch (instr.funct_1) {
		case S1F1_TEQ:     instr.name = MIPS32::TEQ; break;
		case S1F1_TNE:     instr.name = MIPS32::TNE; break;
		case S1F1_SLT:     instr.name = MIPS32::SLT; break; //NEW
		default:           instr.name = MIPS32::IERR; break;
		}
		break;
	case OP_REGIMM:
		switch (instr.funct_2) {
		case RF2_BLTZ:    instr.name = MIPS32::BLTZ; break;
		case RF2_BGEZ:    instr.name = MIPS32::BGEZ; break;
		default:          instr.name = MIPS32::IERR; break;
		}
		break;
	case OP_J:     instr.name = MIPS32::J; break;
	case OP_JAL:   instr.name = MIPS32::JAL; break;
	
	/************************************************/
	case OP_ADDIU: instr.name = MIPS32::ADDIU; break; 
	case OP_SW:    instr.name = MIPS32::SW; break;
	case OP_LW:    instr.name = MIPS32::LW; break;
	case OP_BNE:   instr.name = MIPS32::BNE; break;
	/************************************************/
	
	default:       instr.name = MIPS32::IERR; break;
	}

	return instr;
}

void mips32::execute(MIPS32::instr_t instr)
{

	switch (instr.name) {

		// ***************************
		// CPU Arithmetic Instructions
		// ***************************

	case MIPS32::ADD: // Add Word
		if (verbose) printf("0x%08x: ADD r%d, r%d, r%d\n", PC, instr.rd, instr.rs, instr.rt);
		uint64_t temp64 = GPR[instr.rs] + GPR[instr.rt];
		if ((temp64 & 0x100000000) && (!(temp64 & 0x080000000)))
			SignalException(MIPS32::integerOverflow);
		else
			GPR[instr.rd] = temp64;
		next_PC = PC + 4;
		cntr.arithmetic++;
		break;
		
	case MIPS32::ADDIU: //NEW
	        if (verbose) printf("0x%08x: ADDIU r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.immediate);
		uint32_t temp32=GPR[instr.rs] + instr.immediate;
		GRP[instr.rt]=temp64;
		next_PC=PC+4;
		cntr.arithmetic++;
		break;

	case MIPS32::SLT: //NEW
	        if (verbose) printf("0x%08x: SLT r%d, r%d, r%d\n", PC, instr.rd, instr.rs, instr.rt);
		
		if (GPR[instr_t.rs] < GPR[instr_t.rt])
		    GPR[instr_t.rd] = 0x01;
		else 
		    GPR[instr_t.rd] = 0x00;
		
		next_PC=PC+4;
		cntr.arithmetic++;
		break;		
		
		// ********************************
		// Branch and Jump Instructions
		// ********************************

	case MIPS32::J: // Jump
		if (verbose) printf("0x%08x: J 0x%08x\n", PC, instr.instr_index);
		next_PC = (PC & 0xF0000000) | (instr.instr_index << 2);
		cntr.jump++;
		break;
	case MIPS32::JAL: // Jump and Link
		if (verbose) printf("0x%08x: JAL 0x%08x\n", PC, instr.instr_index);
		GPR[31] = PC + 8;
		next_PC = (PC & 0xF0000000) | (instr.instr_index << 2);
		cntr.jump++;
		break;
	case MIPS32::JALR: // Jump and Link Register
		if (verbose) printf("0x%08x: JALR r%d, r%d\n", PC, instr.rd, instr.rs);
		temp32 = GPR[instr.rs];
		GPR[instr.rd] = PC + 8;
		// no implement ASE
		next_PC = temp32;
		cntr.jump++;
		break;
	case MIPS32::BNE:  //Branch on Not Equal
		if (verbose) printf("0x%08x: BNE r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
		temp32 = instr.offset << 2;
		if (GPR[instr.rs] != GPR[instr.rt]){
		    next_PC = PC + temp32;
		    cntr.jump++;
		}
		break;
	

		// ************************************
		// Control Instructions
		// ************************************

		// ************************************************
		// Load, Store, and Memory Control Instructions
		// ************************************************
	case MIPS32::SW: //SW
	  temp64 = instr.offset+GPR[instr.base];
	    if (( temp64 & 0x30000000) != 0))
		SignalException(MIPS32::AddressError);
	    
		//(pAddr, CCA)=AddressTranslation(temp64, MIPS32::DATA, MIPS32::STORE)

		MIPS32::WORD = GPS[instr_t.rt];
		mips32::StoreMemory(MIPS32::WORD, )
		
		break;
		// ************************
		// Logical Instructions
		// ************************

		// *********************
		// Move Instructions
		// *********************

		// ************************
		// Shift Instructions
		// ************************

		// *****************
		// Trap Instructions
		// *****************
	case MIPS32::SYSCALL: // System Call
		if (verbose) printf("0x%08x: SYSCALL\n", PC);
		SignalException(MIPS32::SystemCall);
		next_PC = PC + 4;
		cntr.trap++;
		break;

		// ***********************
		// Privileged Instructions
		// ***********************

	case MIPS32::IERR:
		SignalException(MIPS32::InvalidInstruction);
		break;
	
}

void mips32::SignalException(MIPS32::exception_t exception)
{
	switch (exception) {
	case MIPS32::integerOverflow:
		printf("[MIPS Exception]: Integer Overflow\n");
		break;
	case MIPS32::TLBRefill:
		printf("[MIPS Exception]: TLBRefill\n");
		break;
	case MIPS32::TLBInvalid:
		printf("[MIPS Exception]: TLBInvalid\n");
		break;
	case MIPS32::AddressError:
		printf("[MIPS Exception]: AddressError\n");
		break;
	case MIPS32::SystemCall:
		printf("[MIPS Exception]: System Call\n");
		break;
	case MIPS32::InvalidInstruction:
		printf("[MIPS Exception]: Invalid Instruction\n");
		break;
	}
	done = true;
}

uint32_t mips32::AddressTranslation(uint32_t addr, MIPS32::mem_type_t mem_type, MIPS32::at_type_t at_type)
{
	return addr;
}
