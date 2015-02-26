#ifndef _ELF_READER_DEFS_H_
#define _ELF_READER_DEFS_H_

#include <stdint.h>
#include <string.h> 
#include <stdio.h>

// File Class
#define ELFCLASSNONE 0
#define ELFCLASS32   1
#define ELFCLASS64   2

// Data Enconding
#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

// Object file type
#define ET_NONE   0 // No file type
#define ET_REL    1 // Relocatable file
#define ET_EXEC   2 // Executable file
#define ET_DYN    3 // Shared object file
#define ET_CORE   4 // Core file
#define ET_LOPROC 0xff00 // Processor - specific
#define ET_HIPROC 0xffff // Processor - specific

// Architecture
#define EM_NONE  0 // No machine
#define EM_M32   1 // AT&T WE 32100
#define EM_SPARC 2 // SPARC
#define EM_386   3 // Intel 80386
#define EM_68K   4 // Motorola 68000
#define EM_88K   5 // Motorola 88000
#define EM_860   7 // Intel 80860
#define EM_MIPS  8 // MIPS RS3000

// Version
#define EV_NONE    0 // Invalid version
#define EV_CURRENT 1 // Current version

// Section Header Type
#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_HASH     5
#define SHT_DYNAMIC  6
#define SHT_NOTE     7
#define SHT_NOBITS   8
#define SHT_REL      9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff

// Attribute Flags
#define SHF_WRITE     0x1
#define SHF_ALLOC     0x2
#define SHF_EXECINSTR 0x4
#define SHF_MASKPROC  0xf0000000

// Program Header Type
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff

// Program Header Flags
#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4

// Symbol info suntions
#define ELF32_ST_BIND(i) ((i) > > 4)
#define ELF32_ST_TYPE(i) ((i)& 0 x f)
#define ELF32_ST_INFO(b, t) (((b) < < 4) + ((t)& 0 x f))

// Symbol Binding
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2
#define STB_LOPROC 13
#define STB_HIPROC 15

// SYmbol Types
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_LOPROC  13
#define STT_HIPROC  15

typedef struct {
	uint8_t ei_mag0;
	uint8_t ei_mag1;
	uint8_t ei_mag2;
	uint8_t ei_mag3;
	uint8_t ei_class;
	uint8_t ei_data;
	uint8_t ei_version;
	uint8_t ei_osabi;
	uint8_t ei_abiversion;
	uint8_t ei_pad[7];
} e_ident_t;

typedef struct {
	e_ident_t e_ident;
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint32_t e_entry;
	uint32_t e_phoff;
	uint32_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} Elf32_hdr_t;

typedef struct {
	uint32_t sh_name;
	uint32_t sh_type;
	uint32_t sh_flags;
	uint32_t sh_addr;
	uint32_t sh_offset;
	uint32_t sh_size;
	uint32_t sh_link;
	uint32_t sh_info;
	uint32_t sh_addralign;
	uint32_t sh_entsize;
} Elf32_Shd_t;

typedef struct {
	uint32_t p_type;
	uint32_t p_offset;
	uint32_t p_vaddr;
	uint32_t p_paddr;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t p_flags;
	uint32_t p_align;
} Elf32_Phdr_t;

typedef struct {
	uint32_t st_name;
	uint32_t st_value;
	uint32_t st_size;
	uint8_t st_info;
	uint8_t st_other;
	uint16_t st_shndx;
} Elf32_Sym_t;

#endif // _ELF_READER_DEFS_H_ //
