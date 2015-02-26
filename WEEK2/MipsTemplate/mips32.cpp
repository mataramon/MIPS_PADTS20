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
        } else {
            irq_evt = false;
        }
    } else {
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
        case 0:
            res = sleep;
            break;
        case 1:
            res = done;
            break;
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
    } else {
        PC = next_PC;
    }
    uint32_t pAddr = AddressTranslation(PC, MIPS32::INSTRUCTION, MIPS32::LOAD);
    int32_t memword = LoadMemory(MIPS32::WORD, pAddr, PC, MIPS32::INSTRUCTION);

    return memword;
}

MIPS32::instr_t mips32::decode(uint32_t idata)
{
    MIPS32::instr_t instr;

    instr.opcode=(idata & 0xFC000000) >> 26;
    instr.funct_3=(idata & 0x03E00000) >> 21;
    instr.rs=(idata & 0x03E00000) >> 21;
    instr.rt=(idata & 0x001F0000) >> 16;
    instr.rd=(idata & 0x0000F800) >> 11;
    instr.immediate=(idata & 0x0000FFFF);
    instr.funct_1=(idata & 0x0000003F);
    instr.funct_2=(idata & 0x001F0000) >> 16;
    instr.offset=(idata & 0x0000FFFF);
    instr.base=(idata & 0x03E00000) >> 21;
    instr.instr_index=(idata & 0x03FFFFFF);
    instr.sa = (idata & 0x000007C0) >> 6;

    switch (instr.opcode) {

        case OP_SPECIAL:
            switch (instr.funct_1) {
                case S1F1_ADD:
                    instr.name = MIPS32::ADD;
                    break;
                case S1F1_TEQ:
                    instr.name = MIPS32::TEQ;
                    break;
                case S1F1_TNE:
                    instr.name = MIPS32::TNE;
                    break;
                case S1F1_SLT:
                    instr.name = MIPS32::SLT;
                    break;
                case S1F1_SLL:
                    instr.name = MIPS32::NOP;
                    break;
                case S1F1_JR:
                    instr.name = MIPS32::JR;
                    break;
                case S1F1_MOVN:    
                    instr.name = MIPS32::MOVN; 
                    break;
                case S1F1_MFLO:     
                    instr.name = MIPS32::MFLO;  
                    break;
//Antonio
                case S1F1_SLLV:
                    instr.name = MIPS32::SLLV;
                    break;
                case S1F1_MFHI:
                    instr.name = MIPS32::MFHI;
                    break;
                case S1F1_SUB:
                    instr.name = MIPS32::SUB;
                    break;
                case S1F1_TLT:
                    instr.name = MIPS32::TLT;
                    break;
                    //case S2F1_CLO:        instr.name = MIPS32::CLO;  break;
                    /****************** Cesar ************************/
                case S1F1_SRA:
                    instr.name = MIPS32::SRA;
                    break;
                case S1F1_ADDU:
                    instr.name = MIPS32::ADDU;
                    break;
                case S1F1_TGEU:
                    instr.name = MIPS32::TGEU;
                    break;
                    /**************************************************/
                case S1F1_SYSCALL:
                    instr.name = MIPS32::SYSCALL;
                    break;
                case S1F1_SUBU:
                    instr.name = MIPS32::SUBU;
                    break;
                case S1F1_DIV:    
                    instr.name = MIPS32::DIV; 
                    break; 
                default:
                    instr.name = MIPS32::IERR;
                    break;
            }
            break;

        case OP_REGIMM:
            switch (instr.funct_2) {
                    //case S2F1_CLO:       instr.name = MIPS32::CLO;  break;
                case S2F1_CLZ :
                    instr.name = MIPS32::CLZ;
                    break;
                case RF2_BLTZ:
                    instr.name = MIPS32::BLTZ;
                    break;
                case RF2_BGEZ:
                    instr.name = MIPS32::BGEZ;
                    break;
                default:
                    instr.name = MIPS32::IERR;
                    break;
            }
            break;

        case OP_J:
            instr.name = MIPS32::J;
            break;
        case OP_JAL:
            instr.name = MIPS32::JAL;
            break;
            /******************** OPCODES *************************/
        case OP_ADDIU:
            instr.name = MIPS32::ADDIU;
            break;
        case OP_SW:
            instr.name = MIPS32::SW;
            break;
        case OP_LW:
            instr.name = MIPS32::LW;
            break;
        case OP_BNE:
            instr.name = MIPS32::BNE;
            break;
        case OP_BNEL:
            instr.name = MIPS32::BNEL;
            break;
	    case OP_LH:
            instr.name = MIPS32::LH;
            break;
            /******************************************************/
        case OP_SLTIU:
            instr.name = MIPS32::SLTIU;
            break;
        case OP_BLEZL:
            instr.name = MIPS32::BLEZL;
            break;
        case OP_LDC1:
            instr.name = MIPS32::LDC1;
            break;
            /******************************************************/
        case OP_SLTI:
            instr.name = MIPS32::SLTI;
            break;
        case OP_ANDI:    
            instr.name = MIPS32::ANDI; 
            break; 
        case OP_LL:
            instr.name = MIPS32::LL;
            break;
        case OP_SB:
            instr.name = MIPS32::SB;
            break;
	    case OP_LBU :
	        instr.name = MIPS32::LBU;
			break;
	    case OP_LB :
	        instr.name = MIPS32::LB;
			break;
	    case OP_SH :
	        instr.name = MIPS32::SH;
			break;
	    case OP_LHU :
	        instr.name = MIPS32::LHU;
			break;
	    case OP_ORI :
	        instr.name = MIPS32::ORI;
			break;
	    break;
        default:
            instr.name = MIPS32::IERR;
            break;

    }
    return instr;
}

void mips32::execute(MIPS32::instr_t instr)
{

    uint8_t temp_byte;
    uint64_t temp64;
    uint32_t temp32;
    int32_t  stemp32,smemword;
    int32_t  target_offset;
    uint32_t vAddr, pAddr;
    int16_t  target_offset16;
    uint16_t utemp16_rs, utemp16_imm;
    uint8_t count;
    uint32_t dataword, memword;
    uint32_t instr_rs, instr_rt;
    uint8_t bytesel,byte;

    switch (instr.name) {

            // ***************************
            // CPU Arithmetic Instructions
            // ***************************

        case MIPS32::ADD: // Add Word // Correct :-)
            if (verbose) printf("Catched ADD  \t-> 0x%08x: ADD r%d, r%d, r%d\n", PC, instr.rd, instr.rs, instr.rt);
            temp64 = GPR[instr.rs] + GPR[instr.rt];
            if ((temp64 & 0x100000000) && (!(temp64 & 0x080000000)))
                SignalException(MIPS32::integerOverflow);
            else
                GPR[instr.rd] = temp64;
            next_PC = PC + 4;
            cntr.arithmetic++;
            break;

        case MIPS32::ADDU: //Add Unsigned Word // Correct :-)
            if (verbose) printf("Catched ADDU \t-> 0x%08x: ADDU r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.rd);
            temp32 = GPR[instr.rs] + GPR[instr.rt];
            GPR[instr.rd]=temp32;
            next_PC=PC+4;
            cntr.arithmetic++;
            //printf("ADDU BALE BERGA\n");
            break;

        case MIPS32::ADDI:
            printf("ADDI Not implemented yet :-) \n ");
            break;

        case MIPS32::ADDIU: // Correct :-)
            if (verbose) printf("Catched ADDIU \t-> 0x%08x: ADDIU r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.immediate);
            temp32 = GPR[instr.rs] + instr.immediate;
            GPR[instr.rt]=temp32;
            next_PC=PC+4;
            cntr.arithmetic++;
            break;

        case MIPS32::SUBU: //TODO: debug this implementation
            if(verbose) printf("Catched SUBU \t-> 0x%08x: SUBU r%d, r%d, r%d\n", PC, instr.rd, instr.rs, instr.rt);
            temp32 = GPR[instr.rs] - GPR[instr.rt];
            GPR[instr.rd] = temp32;
            next_PC = PC + 4;
            cntr.arithmetic++;
            break;
            
        case MIPS32::SLTIU: // Set on Less Than Immediate Unsigned // Correct :-)
            if (verbose) printf("Catched SLTIU \t-> 0x%08x: SLTIU r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.immediate);
            utemp16_rs = GPR[instr.rs];
            utemp16_imm = GPR[instr.immediate];
            GPR[instr.rt] = ( utemp16_rs < utemp16_imm ) ? 1 : 0; //rd?
            next_PC = PC + 4;
            cntr.arithmetic++;
            break;

        case MIPS32::SLTI: // Correct :-)
            int16_t immediate;
            uint16_t rs_0;
            if (verbose) printf("Catched SLTI \t-> 0x%08x: SLTI r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.immediate);
            immediate=instr.immediate;
            rs_0 = GPR[instr.rs];
            GPR[instr.rt] = ( rs_0 < immediate ) ? 1 : 0;
            next_PC = PC + 4;
            cntr.arithmetic++;
            break;

        case MIPS32::DIV: // Divide Word
            if (verbose) printf("Catched DIV \t-> 0x%08x: SUB r%d, r%d\n", PC, instr.rs, instr.rt);
            int32_t q, r;
            q = GPR[instr.rs] / GPR[instr.rt];
            LO = q;
            r = GPR[instr.rs] % GPR[instr.rt];
            HI = r;
            next_PC = PC + 4;
            cntr.arithmetic++;
            break;
            // ********************************
            // Branch and Jump Instructions
            // ********************************

        case MIPS32::J: // Jump // Correct :-)
            if (verbose) printf("Catched J \t-> 0x%08x: J 0x%08x\n", PC, instr.instr_index);
            next_PC = (PC & 0xF0000000) | (instr.instr_index << 2);
            cntr.jump++;
            break;

        case MIPS32::JR: // Jump Register // Correct :-)
            if (verbose) printf("Catched JR \t-> 0x%08x: JR r%d, r%d\n", PC, instr.rs);
            next_PC=GPR[instr.rs];
            printf("Jump to: %d\n", instr.rs);
            break;

        case MIPS32::JAL: // Jump and Link // Correct :-)
            if (verbose) printf("Catched JAL \t-> 0x%08x: JAL 0x%08x\n", PC, instr.instr_index);
            GPR[31] = PC + 8;
            next_PC = (PC & 0xF0000000) | (instr.instr_index << 2);
            cntr.jump++;
            break;

        case MIPS32::JALR: // Jump and Link Register // Correct :-)
            if (verbose) printf("Catched JALR \t-> 0x%08x: JALR r%d, r%d\n", PC, instr.rd, instr.rs);
            temp32 = GPR[instr.rs];
            GPR[instr.rd] = PC + 8;
            // no implement ASE
            //next_PC = temp32;
            cntr.jump++;
            break;

        case MIPS32::BNEL: // Branch on Not Equal Likely // TODO: Debug this
            if( verbose ) printf("Catched BNEL \t-> 0x%08x: BNEL r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            instr_rs=GPR[instr.rs];
            instr_rt=GPR[instr.rt];
            if(instr_rs != instr_rt) {
                next_PC=PC+(instr.offset << 2);
            } else {
                ;
            }
            break;

        case MIPS32::BNE: // Correct :-)
            if( verbose ) printf("Catched BNE \t-> 0x%08x: BNE r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            instr_rs=GPR[instr.rs];
            instr_rt=GPR[instr.rt];
            if(instr_rs != instr_rt) {
                next_PC=PC+(instr.offset << 2);
            } else {
                next_PC=PC+4;
            }
            break;

        case MIPS32::BLEZL:  // Branch on Less Than or Equal to Zero Likely // Correct :-)
            if (verbose) printf("Catched BLEZL \t-> 0x%08x: BLEZL r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            target_offset = instr.offset << 2;
            if (GPR[instr.rs] <= 0 ) {
                next_PC = PC + target_offset;
                cntr.jump++;
            } else ;
            next_PC=PC+4;       //NullifyCurrentInstruction(); WHATS THIS?
            break;

            // ************************************
            // Control Instructions
            // ************************************
        case MIPS32::NOP: // No operation // Correct :-)
            if( verbose ) printf("Catched NOP \t-> 0x%08x: NOP\n", PC);
            next_PC=PC+4;
            break;
            // ************************************************
            // Load, Store, and Memory Control Instructions
            // ************************************************
	    case MIPS32::SB: // Store Byte TODO: debug this
	        if (verbose) printf("Catched SB \t-> %08x: SB r%d, r%d, 0x%08x\n", PC, instr.rt, instr.base, instr.offset);
	        vAddr = instr.offset + GPR[instr.base];
	        pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
	        bytesel = pAddr & 0x00000003; 
	        bytesel = bytesel ^ 0x03;
		    if (verbose) printf("\tbytesel= %d \n", bytesel);
		    if (verbose) printf("\tGPR[%d]= (Dec: %d, Hex: 0x%08x)\n", instr.rt, GPR[instr.rt], GPR[instr.rt]);
	        dataword = GPR[instr.rt]  << (8 * bytesel); 
            if (verbose) printf("\tData Raw:%d, Dec:%d, Hex:0x%08x\n", dataword, dataword>>(8*bytesel), dataword);        	        
            StoreMemory(MIPS32::BYTE, dataword, pAddr, vAddr, MIPS32::DATA); 
	        next_PC = PC + 4;
	        cntr.memory++;
	    break;
	    case MIPS32::LB: // Load Byte Signed // TODO
	        if (verbose) printf("Catched LB \t-> 0x%08x: LB r%d, r%d, 0x%08x\n", PC, instr.base, instr.rt, instr.offset);
	        vAddr = instr.offset + GPR[instr.base];
	        pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
	        smemword = LoadMemory(MIPS32::BYTE, pAddr, vAddr, MIPS32::DATA);
		    byte = vAddr & 0x00000003;
	        //byte = byte ^ 0x03;
            if (verbose) printf("\tbyte: %d \n", byte);
		    stemp32 = smemword >> (8 * byte);	    
            GPR[instr.rt] = stemp32;
	        if (verbose) printf("\tContents Raw:%d, Dec:%d, Hex:0x%08x\n",smemword, smemword >> (8 * byte), smemword);
	        next_PC = PC + 4;
             cntr.memory++;
	    break;
	    case MIPS32::LBU: // Load Byte Unsigned// TODO
	        if (verbose) printf("Catched LBU \t-> 0x%08x: LBU r%d, r%d, 0x%08x\n", PC, instr.base, instr.rt, instr.offset);
	        vAddr = instr.offset + GPR[instr.base];
	        pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
	        memword = LoadMemory(MIPS32::BYTE, pAddr, vAddr, MIPS32::DATA);
		    byte = vAddr & 0x00000003;
	        byte = byte ^ 0x03;
            if (verbose) printf("\tbyte: %d \n", byte);
		    temp32 = memword >> (8 * byte);	    
            temp32 = temp32 & 0x000000FF;
            GPR[instr.rt] = temp32;
	        if (verbose) printf("\tContents Raw:%d, Dec:%d, Hex:0x%08x\n",memword, memword >> (8 * byte), memword);
	        next_PC = PC + 4;
            cntr.memory++;
	    break;
	    case MIPS32::SH: // Store Halfword TODO: debug this
	        if (verbose) printf("Catched SH \t-> %08x: SH r%d, r%d, 0x%08x\n", PC, instr.rt, instr.base, instr.offset);
	        vAddr = instr.offset + GPR[instr.base];
			if (vAddr & 0x01) SignalException(MIPS32::AddressError);
	        pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
	        bytesel = pAddr & 0x00000003; 
	        //bytesel = bytesel ^ 0x03;
		    if (verbose) printf("\tbytesel= %d \n", bytesel);
		    if (verbose) printf("\tGPR[%d]= (Dec: %d, Hex: 0x%08x)\n", instr.rt, GPR[instr.rt], GPR[instr.rt]);
	        dataword = GPR[instr.rt]  << (8 * bytesel); 
            if (verbose) printf("\tData Raw:%d, Dec:%d, Hex:0x%08x\n", dataword, dataword>>(8*bytesel), dataword);        	        
            StoreMemory(MIPS32::HALFWORD, dataword, pAddr, vAddr, MIPS32::DATA); 
	        next_PC = PC + 4;
	        cntr.memory++;
		break;

	    case MIPS32::LHU: // Load Byte Unsigned// TODO
	        if (verbose) printf("Catched LHU \t-> 0x%08x: LHU r%d, r%d, 0x%08x\n", PC, instr.base, instr.rt, instr.offset);
	        vAddr = instr.offset + GPR[instr.base];
			if (vAddr & 0x01) SignalException(MIPS32::AddressError);	        	        
			pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
			memword = LoadMemory(MIPS32::HALFWORD, pAddr, vAddr, MIPS32::DATA);
		    byte = vAddr & 0x00000003;
	        //byte = byte ^ 0x03;
            if (verbose) printf("\tbyte: %d \n", byte);
		    temp32 = memword >> (8 * byte);	    
            temp32 = temp32 & 0x000000FF;
            GPR[instr.rt] = temp32;
	        if (verbose) printf("\tContents Raw:%d, Dec:%d, Hex:0x%08x\n",memword, memword >> (8 * byte), memword);
	        next_PC = PC + 4;
            cntr.memory++;
	    break;

        case MIPS32::ORI:  //Load Doubleword to Floating Point // TODO: what NullifyCurrentInstruction() do?
            if (verbose) printf("Catched ORI \t-> 0x%08x: ORI r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.immediate);
			stemp32 = instr.immediate;			
			GPR[instr.rt] = GPR[instr.rs] | stemp32;
			//cout << "VALIO VERGA" << endl;            
			next_PC = PC + 4;
             
            break;

        case MIPS32::LDC1:  //Load Doubleword to Floating Point // TODO: what NullifyCurrentInstruction() do?
            if (verbose) printf("Catched LDC1 \t-> 0x%08x: LDC1 r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            target_offset16 = instr.offset;
            target_offset16 = target_offset16 << 2;
            if (GPR[instr.rs] <= 0 ) {
                next_PC = PC + target_offset16;
                cntr.jump++;
            } else ; 
            break;
	    
	    case MIPS32::LH: //Load Halfword //TODO: debug this instruction
                if (verbose) printf("Catched LH \t-> 0x%08x: LH r%d, 0x%08x\n", PC, instr.rt, instr.offset);
                vAddr = instr.offset + GPR[instr.base];
                if ((vAddr & 0x00000001) != 0)
                SignalException(MIPS32::AddressError);
                pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::LOAD);
                memword = LoadMemory(MIPS32::HALFWORD, pAddr, vAddr, MIPS32::DATA);
                temp_byte = vAddr & 0x00000003;
                GPR[instr.rt] = memword << (temp_byte * 8);
                next_PC = PC + 4;
                cntr.control++;
            break;
	    case MIPS32::LWL: // TODO: debug this
            if (verbose) printf("Catched LWL \t-> 0x%08x: LH r%d, 0x%08x\n", PC, instr.rt, instr.offset);
            vAddr = GPR[instr.offset] + GPR[instr.base];
            pAddr = AddressTranslation(vAddr, MIPS32::DATA, MIPS32::LOAD);
	    next_PC=PC+4;
            break;

        case MIPS32::CLZ: // Count Leading Zeros in Word // TODO: Debug this implementation
            if (verbose) printf("Catched CLZ \t-> 0x%08x: CLZ r%d, r%d, r%d\n", PC, instr.rs, instr.rt, instr.rd);
            temp32 = GPR[instr.rs];
            count = 32;
            for (int i=0; i<=31; i++ ) {
                temp32 = GPR[instr.rs];
                temp32 = (temp32 << i ) && 0x80000000;
                if (temp32 != 0)
                    count--;
            }
            GPR[instr.rd] = count;
            next_PC = PC + 4;
            cntr.shift++;
            break;

        case MIPS32::SW: // Correct :-)
            if (verbose) printf("Catched SW \t-> 0x%08x: SW r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            vAddr=instr.offset + GPR[instr.base];
            if( (vAddr & 0x00000003) != 0 )
                SignalException(MIPS32::AddressError);
            pAddr=AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
            dataword=GPR[instr.rt];
            if(verbose) printf("\tData is %d, 0x%08x\n", dataword, dataword);
            StoreMemory(MIPS32::WORD, dataword, pAddr, vAddr, MIPS32::DATA);
            next_PC=PC+4;

            break;

        case MIPS32::LW: // Correct :-) 
            if (verbose) printf("Catched LW\t-> 0x%08x: LW r%d, r%d, 0x%08x\n", PC, instr.rs, instr.rt, instr.offset);
            vAddr=instr.offset + GPR[instr.base];
            if( (vAddr & 0x00000003) != 0 )
                SignalException(MIPS32::AddressError);
            pAddr=AddressTranslation(vAddr, MIPS32::DATA, MIPS32::STORE);
            memword=LoadMemory(MIPS32::WORD, pAddr, vAddr, MIPS32::DATA);
            GPR[instr.rt]=memword;
            next_PC=PC+4;
            break;

        case MIPS32::LL: //Debug this
            temp32 = instr.offset + GPR[instr.base];
            vAddr = temp32;
            if( (vAddr & 0x00000003) != 0 ){  
                SignalException(MIPS32::AddressError); 
            }
            pAddr=AddressTranslation(vAddr, MIPS32::DATA, MIPS32::LOAD);
            memword = LoadMemory(MIPS32::WORD,pAddr,vAddr,MIPS32::DATA);
            GPR[instr.rt] = memword;
            LLbit = 1;
            next_PC=PC+4;
        break;
            // ************************
            // Logical Instructions
            // ************************
        case MIPS32::ANDI: // And Immediate
            if (verbose) printf("Catched ANDI \t-> 0x%08x: ANDI r%d, r%d, r%d \n", PC, instr.rs, instr.rt, instr.immediate);
                temp32 = instr.immediate & 0x0000FFFF;      
            GPR[instr.rt] = GPR[instr.rs] & temp32;
            next_PC = PC + 4;
            cntr.logical++;
        break;
            // *********************
            // Move Instructions
            // *********************
        
        case MIPS32::MOVN: // Move Conditional on Not Zero
             if (verbose) printf("Catched MOVN \t-> 0x%08x: MOVN r%d, r%d, r%d \n", PC, instr.rs, instr.rt ,instr.rd);
             if(GPR[instr.rt] != 0)
                GPR[instr.rd] = GPR[instr.rs];
             next_PC = PC + 4;
            cntr.move++;
            break;
 
    //}
            // ************************
            // Shift Instructions
            // ************************

            // *****************
            // Trap Instructions
            // *****************
        case MIPS32::SYSCALL: // System Call // Correct :-)
            if (verbose) printf("Catched SYSCALL -> 0x%08x: SYSCALL\n", PC);
            SignalException(MIPS32::SystemCall);
            next_PC = PC + 4;
            cntr.trap++;
            break;

        case MIPS32::TEQ: //Trap if equal //Correct :-)
            if(verbose) printf("Catched TEQ \t-> 0x%08x: TEQ r%d, r%d, \n", PC, instr.rs, instr.rt);
            if(GPR[instr.rs] == GPR[instr.rt])
                SignalException(MIPS32::SystemCall); //TODO: Debug if SYSCALL or add TRAP exception
            else
                next_PC=PC+4;
            cntr.trap++;
            break;

            // ***********************
            // Privileged Instructions
            // ***********************

        case MIPS32::IERR:
            SignalException(MIPS32::InvalidInstruction);
            break;
    }
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
