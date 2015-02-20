#ifndef _MIPS32_H_
#define _MIPS32_H_

#include <iostream>
#include "mips32_defs.h"
//#include <unistd.h>
#include <windows.h>
#include <stdio.h>

using namespace std;

// MIPS 32 Processor Model
class mips32 {
public:
	MIPS32::mips_counter_t cntr;

	// Constructor
	mips32(bool vb);

	// Reset
	void reset(uint32_t init_PC);

	// Run
	void run(void);

	// Status
	bool get_status(uint8_t param);

	// Processor Stages
	uint32_t fetch(void); // Fetch
	MIPS32::instr_t decode(uint32_t idata); // Decode
	void execute(MIPS32::instr_t instr); // Execute
	void pic(uint8_t n); // PIC

	// Load Memory
	virtual int32_t LoadMemory(MIPS32::word_size_t word_size, uint32_t paddr, uint32_t vaddr, MIPS32::mem_type_t mem_type)=0;

	// Store Memory
	virtual void StoreMemory(MIPS32::word_size_t word_size, int32_t data, uint32_t paddr, uint32_t vaddr, MIPS32::mem_type_t mem_type)=0;

private:
	// CPU Registres
	int32_t GPR[32]; // General Purpose Registers
	int32_t HI, LO;  // Special Purpose Registers
	uint32_t PC;      // Program Counter

	// FPU Registers
	uint32_t FPR[32]; // Floating Point Registers
	uint32_t FCR0;    // FPU Control Register
	uint32_t FCR25;   // FPU Control Register
	uint32_t FCR26;   // FPU Control Register
	uint32_t FCR28;   // FPU Control Register
	uint32_t FCSR;    // FPU Control Register

	// CoProcessor0 Registers
	MIPS32::CPR_t CP0R;
	uint32_t* CP0RP;

	uint32_t next_PC;
	uint32_t irq_handler;
	uint32_t entry_addr;
	bool LLbit;
	bool irq_evt;
	bool sleep;
	bool done;

	bool verbose;

	// Exceptions
	void SignalException(MIPS32::exception_t exception);

	// Address Translation
	uint32_t AddressTranslation(uint32_t addr, MIPS32::mem_type_t mem_type, MIPS32::at_type_t at_type);
};

#endif // _MIPS32_H_ //

