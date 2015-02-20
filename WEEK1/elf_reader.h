#ifndef _ELF_READER_H_
#define _ELF_READER_H_

#include "elf_reader_defs.h"
#include <iostream>

class elf_reader {
private:
	FILE* ptr_file;
	FILE* ptr_dfile;
	Elf32_hdr_t Elf32_hdr;
	Elf32_Shd_t* Elf32_Shd;
	Elf32_Phdr_t* Elf32_Phdr;
	Elf32_Sym_t* Elf32_Sym;
	char* headers_name;
	char* syms_name;
	char sym_t_indx;
	int sym_entries;
	char loadable_segment;

	void format_elf32_hdr(void);
	void format_elf32_shd(void);
	void format_elf32_phdr(void);
	void format_elf32_sym(void);
	void change_endianess(uint8_t* data, uint8_t n_bytes);

public:
	uint32_t main_ptr;
	uint32_t start_ptr;
	uint32_t entry_ptr;
	uint32_t base_addr;
	uint8_t* mem;
	uint32_t mem_size;

	/*void*/int read_elf(const char* elf_file);
	/*void*/ int print_elf(const char* dmp_file);
	uint32_t find_symbol(const char* sym_name);
};

#endif //_ELF_READER_H_ //
