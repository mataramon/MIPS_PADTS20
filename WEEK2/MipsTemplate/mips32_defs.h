#ifndef _MIPS32_DEFS_H_
#define _MIPS32_DEFS_H_

#include <stdint.h>

namespace MIPS32 {

	// Opcode values
#define OP_SPECIAL  0x00
#define OP_REGIMM   0x01
#define OP_J        0x02
#define OP_JAL      0x03
#define OP_BEQ      0x04
#define OP_BNE      0x05
#define OP_BLEZ     0x06
#define OP_BGTZ     0x07
#define OP_ADDI     0x08
#define OP_ADDIU    0x09
#define OP_SLTI     0x0A
#define OP_SLTIU    0x0B
#define OP_ANDI     0x0C
#define OP_ORI      0x0D
#define OP_XORI     0x0E
#define OP_LUI      0x0F
#define OP_COP0     0x10
#define OP_COP1     0x11
#define OP_COP2     0x12
#define OP_BEQL     0x14
#define OP_BNEL     0x15
#define OP_BLEZL    0x16
#define OP_BGTZL    0x17
#define OP_SPECIAL2 0x1C
#define OP_CACHE    0x1F
#define OP_LB       0x20
#define OP_LH       0x21
#define OP_LWL      0x22
#define OP_LW       0x23
#define OP_LBU      0x24
#define OP_LHU      0x25
#define OP_LWR      0x26
#define OP_SB       0x28
#define OP_SH       0x29
#define OP_SWL      0x2A
#define OP_SW       0x2B
#define OP_SWR      0x2E
#define OP_LL       0x30
#define OP_LWC1     0x31
#define OP_LWC2     0x32
#define OP_PREF     0x33
#define OP_LDC1     0x35
#define OP_LDC2     0x36
#define OP_SC       0x38
#define OP_SWC1     0x39
#define OP_SWC2     0x3A
#define OP_SDC1     0x3D
#define OP_SDC2     0x3E

	// Special1 function values
#define S1F1_SLL     0x00
#define S1F1_MOVCI   0x01
#define S1F1_SRL     0x02
#define S1F1_SRA     0x03
#define S1F1_SLLV    0x04
#define S1F1_SRLV    0x06
#define S1F1_SRAV    0x07
#define S1F1_JR      0x08
#define S1F1_JALR    0x09
#define S1F1_MOVZ    0x0A
#define S1F1_MOVN    0x0B
#define S1F1_SYSCALL 0x0C
#define S1F1_BREAK   0x0D
#define S1F1_SYNC    0x0F
#define S1F1_MFHI    0x10
#define S1F1_MTHI    0x11
#define S1F1_MFLO    0x12
#define S1F1_MTLO    0x13
#define S1F1_MULT    0x18
#define S1F1_MULTU   0x19
#define S1F1_DIV     0x1A
#define S1F1_DIVU    0x1B
#define S1F1_ADD     0x20
#define S1F1_ADDU    0x21
#define S1F1_SUB     0x22
#define S1F1_SUBU    0x23
#define S1F1_AND     0x24
#define S1F1_OR      0x25
#define S1F1_XOR     0x26
#define S1F1_NOR     0x27
#define S1F1_SLT     0x2A
#define S1F1_SLTU    0x2B
#define S1F1_TGE     0x30
#define S1F1_TGEU    0x31
#define S1F1_TLT     0x32
#define S1F1_TLTU    0x33
#define S1F1_TEQ     0x34
#define S1F1_TNE     0x36

	// Special2 function values
#define S2F1_MADD  0x00
#define S2F1_MADDU 0x01
#define S2F1_MUL   0x02
#define S2F1_MSUB  0x04
#define S2F1_MSUBU 0x05
#define S2F1_CLZ   0x20
#define S2F1_CLO   0x21
#define S2F1_SDBBP 0x3F

	// REGIMM function2 values
#define RF2_BLTZ    0x00
#define RF2_BGEZ    0x01
#define RF2_BLTZL   0x02
#define RF2_BGEZL   0x03
#define RF2_TGEI    0x08
#define RF2_TGEIU   0x09
#define RF2_TLTI    0x0A
#define RF2_TLTIU   0x0B
#define RF2_TEQI    0x0C
#define RF2_TNEI    0x0E
#define RF2_BLTZAL  0x10
#define RF2_BGEZAL  0x11
#define RF2_BLTZALL 0x12
#define RF2_BGEZALL 0x13

	// COP0 function1 values
#define C0F1_TLBR  0x01
#define C0F1_TLBWI 0x02
#define C0F1_TLBWR 0x06
#define C0F1_TLBP  0x08
#define C0F1_ERET  0x18
#define C0F1_DERET 0x1F
#define C0F1_WAIT  0x20

	// COP1 function1 values
#define C1F1_ADD    0x00
#define C1F1_SUB    0x01
#define C1F1_MUL    0x02
#define C1F1_DIV    0x03
#define C1F1_SQRT   0x04
#define C1F1_ABS    0x05
#define C1F1_MOV    0x06
#define C1F1_NEG    0x07
#define C1F1_ROUNDW 0x0C
#define C1F1_TRUNCW 0x0D
#define C1F1_CEILW  0x0E
#define C1F1_FLOORW 0x0F
#define C1F1_MOVCF  0x11
#define C1F1_MOVZ   0x12
#define C1F1_MOVN   0x13
#define C1F1_CVTS   0x20
#define C1F1_CVTD   0x21
#define C1F1_CVTW   0x24

	// COP0 function3 values
#define C0F3_MF 0x00
#define C0F3_MT 0x04

	// COP1 function3 values
#define C1F3_MF 0x00
#define C1F3_CF 0x02
#define C1F3_MT 0x04
#define C1F3_CT 0x06
#define C1F3_BC 0x08

	// COP2 function3 values
#define C2F3_MF 0x00
#define C2F3_CF 0x02
#define C2F3_MT 0x04
#define C2F3_CT 0x06
#define C2F3_BC 0x08

	// Floating Comparison condition values
#define CN_F    0x0
#define CN_UN   0x1
#define CN_EQ   0x2
#define CN_UEQ  0x3
#define CN_OLT  0x4
#define CN_ULT  0x5
#define CN_OLE  0x6
#define CN_ULE  0x7
#define CN_SF   0x8
#define CN_NGLE 0x9
#define CN_SEQ  0xA
#define CN_NGL  0xB
#define CN_LT   0xC
#define CN_NGE  0xD
#define CN_LE   0xE
#define CN_NGT  0xF

	// Cache name values
#define CHN_I 0x0 // Primary Instruction
#define CHN_D 0x1 // Primary Data or Unified primary
#define CHN_T 0x2 // Tertiary
#define CHN_S 0x3 // Secondary

	// Cache operation values
#define CHO_INV 0x0 // Index Invalidate
#define CHO_LTG 0x1 // Load Tag
#define CHO_STG 0x2 // Store Tag
#define CHO_IDP 0x3 // Implementation Dependent
#define CHO_HIN 0x4 // Hit Invalidate
#define CHO_HWI 0x5 // Hit WriteBack Invalidate
#define CHO_HWB 0x6 // Hit WriteBack
#define CHO_FAL 0x7 // Fetch and lock

	typedef enum instr_name_e {

		// CPU Arithmetic Instructions
		ADD, // Add Word
		ADDI, // Add Immediate Word
		ADDIU, // Add Immediate Unsigned Word
		ADDU, // Add Unsigned Word
		CLO, // Count Leading Ones in Word
		CLZ, // Count Leading Zeros in Word
		DIV, // Divide Word
		DIVU, // Divide Unsigned Word
		MADD, // Multiply and Add Word to Hi, Lo
		MADDU, // Multiply and Add Unsigned Word to Hi, Lo
		MSUB, // Multiply and Subtract Word to Hi, Lo
		MSUBU, // Multiply and Subtract Unsigned Word to Hi, Lo
		MUL, // Multiply Word to GPR
		MULT, // Multiply Word
		MULTU, // Multiply Unsigned Word
		SLT, // Set on Less Than
		SLTI, // Set on Less Than Immediate
		SLTIU, // Set on Less Than Immediate Unsigned
		SLTU, // Set on Less Than Unsigned
		SUB, // Subtract Word
		SUBU, // Subtract Unsigned Word

		// CPU Branch and Jump Instructions
		B, // Unconditional Branch
		BAL, // Branch and Link
		BEQ, // Branch on Equal
		BGEZ, // Branch on Greater Than or Equal to Zero
		BGEZAL, // Branch on Greater Than or Equal to Zero and Link
		BGTZ, // Branch on Greater Than Zero
		BLEZ, // Branch on Less Than or Equal to Zero
		BLTZ, // Branch on Less Than Zero
		BLTZAL, // Branch on Less Than Zero and Link
		BNE, // Branch on Not Equal
		J, // Jump
		JAL, // Jump and Link
		JALR, // Jump and Link Register
		JR, // Jump Register

		// CPU Instruction Control Instructions
		NOP, // No Operation
		SSNOP, // Superscalar No Operation

		// CPU Load, Store, and Memory Control Instructions
		LB, // Load Byte
		LBU, // Load Byte Unsigned
		LH, // Load Halfword
		LHU, // Load Halfword Unsigned
		LL, // Load Linked Word
		LW, // Load Word
		LWL, // Load Word Left
		LWR, // Load Word Right
		PREF, // Prefetch
		SB, // Store Byte
		SC, // Store Conditional Word
		SD, // Store Doubleword
		SH, // Store Halfword
		SW, // Store Word
		SWL, // Store Word Left
		SWR, // Store Word Right
		SYNC, // Synchronize Shared Memory
		// CPU Logical Instructions
		AND, // And
		ANDI, // And Immediate
		LUI, // Load Upper Immediate
		NOR, // Not Or
		OR, // Or
		ORI, // Or Immediate
		XOR, // Exclusive Or
		XORI, // Exclusive Or Immediate

		// CPU Move Instructions
		MFHI, // Move From HI Register
		MFLO, // Move From LO Register
		MOVF, // Move Conditional on Floating Point False
		MOVN, // Move Conditional on Not Zero
		MOVT, // Move Conditional on Floating Point True
		MOVZ, // Move Conditional on Zero
		MTHI, // Move To HI Register
		MTLO, // Move To LO Register

		// CPU Shift Instructions
		SLL, // Shift Word Left Logical
		SLLV, // Shift Word Left Logical Variable
		SRA, // Shift Word Right Arithmetic
		SRAV, // Shift Word Right Arithmetic Variable
		SRL, // Shift Word Right Logical
		SRLV, // Shift Word Right Logical Variable

		// CPU Trap Instructions
		BREAK, // Breakpoint
		SYSCALL, // System Call
		TEQ, // Trap if Equal
		TEQI, // Trap if Equal Immediate
		TGE, // Trap if Greater or Equal
		TGEI, // Trap if Greater of Equal Immediate
		TGEIU, // Trap if Greater or Equal Immediate Unsigned
		TGEU, // Trap if Greater or Equal Unsigned
		TLT, // Trap if Less Than
		TLTI, // Trap if Less Than Immediate
		TLTIU, // Trap if Less Than Immediate Unsigned
		TLTU, // Trap if Less Than Unsigned
		TNE, // Trap if Not Equal
		TNEI, // Trap if Not Equal Immediate

		// Obsoletea CPU Branch Instructions
		// a.Software is strongly encouraged to avoid use of the Branch Likely instructions, as they will be removed from
		// a future revision of the MIPS32 architecture.
		BEQL, // Branch on Equal Likely
		BGEZALL, // Branch on Greater Than or Equal to Zero and Link Likely
		BGEZL, // Branch on Greater Than or Equal to Zero Likely
		BGTZL, // Branch on Greater Than Zero Likely
		BLEZL, // Branch on Less Than or Equal to Zero Likely
		BLTZALL, // Branch on Less Than Zero and Link Likely
		BLTZL, // Branch on Less Than Zero Likely
		BNEL, // Branch on Not Equal Likely

		// FPU Arithmetic Instructions
		ABS_fmt, // Floating Point Absolute Value
		ADD_fmt, // Floating Point Add
		DIV_fmt, // Floating Point Divide
		MADD_fmt, // Floating Point Multiply Add
		MSUB_fmt, // Floating Point Multiply Subtract
		MUL_fmt, // Floating Point Multiply
		NEG_fmt, // Floating Point Negate
		NMADD_fmt, // Floating Point Negative Multiply Add
		NMSUB_fmt, // Floating Point Negative Multiply Subtract
		RECIP_fmt, // Reciprocal Approximation
		RSQRT_fmt, // Reciprocal Square Root Approximation
		SQRT, // Floating Point Square Root
		SUB_fmt, // Floating Point Subtract

		// FPU Branch Instructions
		BC1F, // Branch on FP False
		BC1T, // Branch on FP True

		// FPU Compare Instructions
		C_cond_fmt, // Floating Point Compare

		// FPU Convert Instructions
		CEIL_W_fmt, // Floating Point Ceiling Convert to Word Fixed Point
		CVT_D_fmt, // Floating Point Convert to Double Floating Point
		CVT_S_fmt, // Floating Point Convert to Single Floating Point
		CVT_W_fmt, // Floating Point Convert to Word Fixed Point
		FLOOR_W_fmt, // Floating Point Floor Convert to Word Fixed Point
		ROUND_W_fmt, // Floating Point Round to Word Fixed Point
		TRUNC_W_fmt, // Floating Point Truncate to Word Fixed Point

		// Load, Store, and Memory Control Instructions
		LDC1, // Load Doubleword to Floating Point
		LWC1, // Load Word to Floating Point
		SDC1, // Store Doubleword from Floating Point
		SWC1, // Store Word from Floating Point

		// FPU Move Instructions
		CFC1, // Move Control Word from Floating Point
		CTC1, // Move Control Word to Floating Point
		MFC1, // Move Word from Floating Point
		MOV_fmt, // Floating Point Move
		MOVF_fmt, // Floating Point Move Conditional on Floating Point False
		MOVN_fmt, // Floating Point Move Conditional on Not Zero
		MOVT_fmt, // Floating Point Move Conditional on Floating Point True
		MOVZ_fmt, // Floating Point Move Conditional on Zero
		MTC1, // Move Word to Floating Point

		// Obsoletea FPU Branch Instructions
		// a.Software is strongly encouraged to avoid use of the Branch Likely instructions, as they will be removed from
		// a future revision of the MIPS32 architecture.
		BC1FL, // Branch on FP False Likely
		BC1TL, // Branch on FP True Likely

		// Coprocessor Branch Instructions
		BC2F, // Branch on COP2 False
		BC2T, // Branch on COP2 True

		// Coprocessor Execute Instructions
		COP2, // Coprocessor Operation to Coprocessor 2

		// Coprocessor Load and Store Instructions
		LDC2, // Load Doubleword to Coprocessor 2
		LWC2, // Load Word to Coprocessor 2
		SDC2, // Store Doubleword from Coprocessor 2
		SWC2, // Store Word from Coprocessor 2

		// Coprocessor Move Instructions
		CFC2, // Move Control Word from Coprocessor 2
		CTC2, // Move Control Word to Coprocessor 2
		MFC2, // Move Word from Coprocessor 2
		MTC2, // Move Word to Coprocessor 2

		// Obsoletea Coprocessor Branch Instructions
		// a.Software is strongly encouraged to avoid use of the Branch Likely instructions, as they will be removed from
		// a future revision of the MIPS32 architecture.
		BC2FL, // Branch on COP2 False Likely
		BC2TL, // Branch on COP2 True Likely

		// Privileged Instructions
		CACHE, // Perform Cache Operation
		ERET, // Exception Return
		MFC0, // Move from Coprocessor 0
		MTC0, // Move to Coprocessor 0
		TLBP, // Probe TLB for Matching Entry
		TLBR, // Read Indexed TLB Entry
		TLBWI, // Write Indexed TLB Entry
		TLBWR, // Write Random TLB Entry
		WAIT, // Enter Standby Mode

		// EJTAG Instructions
		DERET, // Debug Exception Return
		SDBBP, // Software Debug Breakpoint

		IERR // Intruction Error, Instrucion not recognized

	} instr_name_t;

	typedef struct instr_s {
		instr_name_t name; // Instruction name
		uint8_t opcode; // Instruction opcode
		uint8_t funct_1; // Instruction function 1
		uint8_t funct_2; // Instruction function 2
		uint8_t funct_3; // Instruction function 3
		int16_t immediate; // Immaediate data
		int16_t offset; // Immaediate data
		uint32_t code; // Code for breakpoint exception
		uint32_t instr_index; // Instruction Index (JUMP)
		uint8_t sel; // Selector
		// Instruction fields
		uint8_t sa;
		uint8_t rs;
		uint8_t rt;
		uint8_t rd;
		uint8_t hint;
		uint8_t stype;
		// Floating point fields
		uint8_t fmt;
		uint8_t ft;
		uint8_t fs;
		uint8_t fd;
		// Branch fields
		uint8_t	cc_2;
		bool nd;
		bool tf;
		// Flaoting Point Branch fields
		uint8_t	cc_1;
		bool A;
		uint8_t FC;
		uint8_t cond;
		// Cache fields
		uint8_t base;
		uint8_t cache_nm;
		uint8_t cache_op;
		// Coprocessor fields
		bool CO;
		uint32_t cofun;
	} instr_t;

	typedef enum exception_e {
		integerOverflow,
		TLBRefill,
		TLBInvalid,
		AddressError,
		SystemCall,
		InvalidInstruction
	} exception_t;

	typedef enum mem_type_e {
		DATA,
		INSTRUCTION
	} mem_type_t;

	typedef enum at_type_e {
		LOAD,
		STORE
	} at_type_t;

	typedef enum word_size_e {
		BYTE,
		HALFWORD,
		WORD
	} word_size_t;

	typedef struct CPR_s {
		uint32_t Index;
		uint32_t Random;
		uint32_t EntryLo0;
		uint32_t EntryLo1;
		uint32_t Context;
		uint32_t PageMask;
		uint32_t Wired;
		uint32_t Reserved0;
		uint32_t BadVAddr;
		uint32_t Count;
		uint32_t EntryHi;
		uint32_t Compare;
		uint32_t Status;
		uint32_t Cause;
		uint32_t EPC;
		uint32_t PRId;
		uint32_t Config;
		uint32_t LLAddr;
		uint32_t WatchLo;
		uint32_t WatchHi;
		uint32_t XContext;
		uint32_t Reserved1;
		uint32_t Reserved2;
		uint32_t Debug;
		uint32_t DEPC;
		uint32_t PerfCnt;
		uint32_t ErrCtl;
		uint32_t CacheErr;
		uint32_t TagLo_DataLo;
		uint32_t TagHi_DataHi;
		uint32_t ErrorEPC;
		uint32_t DESAVE;
	} CPR_t;

	typedef struct mips_counter_s {
		uint32_t privileged;
		uint32_t trap;
		uint32_t shift;
		uint32_t move;
		uint32_t logical;
		uint32_t memory;
		uint32_t control;
		uint32_t jump;
		uint32_t arithmetic;
	} mips_counter_t;

}

#endif // _MIPS32_DEFS_H_ //
