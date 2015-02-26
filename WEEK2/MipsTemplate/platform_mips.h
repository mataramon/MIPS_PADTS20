#ifndef _PLATFORM_MIPS_H_
#define _PLATFORM_MIPS_H_

#include "mips32.h"
#include "elf_reader.h"

class platform_mips : public mips32
{
public:
	platform_mips(const char* elf_file, const char* dmp_file, bool verbose);

	// Print Statistics
	void print_stats(const char* stats_file);

	// Enable Pipeline
	void run_mips(void);

	elf_reader ereader;

private:
	// Load Memory
	virtual int32_t LoadMemory(MIPS32::word_size_t word_size, uint32_t paddr, uint32_t vaddr, MIPS32::mem_type_t mem_type);

	// Store Memory
	virtual void StoreMemory(MIPS32::word_size_t word_size, int32_t data, uint32_t paddr, uint32_t vaddr, MIPS32::mem_type_t mem_type);


	uint8_t* memory;
	bool vb;
};

#endif /* _PLATFORM_MIPS_H_ */

