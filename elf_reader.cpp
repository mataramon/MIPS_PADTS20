#include "elf_reader.h"

void elf_reader::print_elf(const char* dmp_file)
{
	ptr_dfile = fopen(dmp_file, "w");

	// ****************
	// Print ELF Header
	// ****************

	fprintf(ptr_dfile, "ELF Header:\n");
	fprintf(ptr_dfile, "  Magic:\t\t\t\t\t%02x %02x %02x %02x\n", Elf32_hdr.e_ident.ei_mag0, Elf32_hdr.e_ident.ei_mag1, Elf32_hdr.e_ident.ei_mag2, Elf32_hdr.e_ident.ei_mag3);
	fprintf(ptr_dfile, "  Class:\t\t\t\t\t");
	switch (Elf32_hdr.e_ident.ei_class) {
	case ELFCLASSNONE: fprintf(ptr_dfile, "ELF None"); break;
	case ELFCLASS32: fprintf(ptr_dfile, "ELF32"); break;
	case ELFCLASS64: fprintf(ptr_dfile, "ELF64"); break;
	}
	fprintf(ptr_dfile, "\n  Data:\t\t\t\t\t\t");
	switch (Elf32_hdr.e_ident.ei_data) {
	case ELFDATANONE: fprintf(ptr_dfile, "Data None"); break;
	case ELFDATA2LSB: fprintf(ptr_dfile, "2's complement, little endian"); break;
	case ELFDATA2MSB: fprintf(ptr_dfile, "2's complement, big endian"); break;
	}
	fprintf(ptr_dfile, "\n  Version:\t\t\t\t\t");
	switch (Elf32_hdr.e_ident.ei_version) {
	case EV_NONE: fprintf(ptr_dfile, "0 (Invalid)"); break;
	case EV_CURRENT: fprintf(ptr_dfile, "1 (Current)"); break;
	}
	fprintf(ptr_dfile, "\n  ABI Version:\t\t\t\t%d", Elf32_hdr.e_ident.ei_abiversion);
	fprintf(ptr_dfile, "\n  Type:\t\t\t\t\t\t");
	switch (Elf32_hdr.e_type) {
	case ET_NONE: fprintf(ptr_dfile, "NONE"); break;
	case ET_REL: fprintf(ptr_dfile, "REL (Relocatable)"); break;
	case ET_EXEC: fprintf(ptr_dfile, "EXEC (Executable)"); break;
	case ET_DYN: fprintf(ptr_dfile, "DYN (Shared Object)"); break;
	case ET_CORE: fprintf(ptr_dfile, "CORE (Core)"); break;
	case ET_LOPROC: fprintf(ptr_dfile, "LOPROC (Processor Specific)"); break;
	case ET_HIPROC: fprintf(ptr_dfile, "HIPROC (Processor Specific)"); break;
	}
	fprintf(ptr_dfile, "\n  Machine:\t\t\t\t\t");
	switch (Elf32_hdr.e_machine) {
	case EM_NONE: fprintf(ptr_dfile, "No machine"); break;
	case EM_M32: fprintf(ptr_dfile, "AT&T WE 32100"); break;
	case EM_SPARC: fprintf(ptr_dfile, "SPARC"); break;
	case EM_386: fprintf(ptr_dfile, "Intel 80386"); break;
	case EM_68K: fprintf(ptr_dfile, "Motorola 68000"); break;
	case EM_88K: fprintf(ptr_dfile, "Motorola 88000"); break;
	case EM_860: fprintf(ptr_dfile, "Intel 80860"); break;
	case EM_MIPS: fprintf(ptr_dfile, "MIPS RS3000"); break;
	}
	fprintf(ptr_dfile, "\n  Version:\t\t\t\t\t0x%02x", Elf32_hdr.e_version);
	fprintf(ptr_dfile, "\n  Entry point address:\t\t\t0x%08x", Elf32_hdr.e_entry);
	fprintf(ptr_dfile, "\n  Start of program headers:\t\t%d (bytes into file)", Elf32_hdr.e_phoff);
	fprintf(ptr_dfile, "\n  Start of section headers:\t\t%d (bytes into file)", Elf32_hdr.e_shoff);
	fprintf(ptr_dfile, "\n  Size of this header:\t\t\t%d (bytes)", Elf32_hdr.e_ehsize);
	fprintf(ptr_dfile, "\n  Size of program headers:\t\t%d (bytes)", Elf32_hdr.e_phentsize);
	fprintf(ptr_dfile, "\n  Number program headers:\t\t%d", Elf32_hdr.e_phnum);
	fprintf(ptr_dfile, "\n  Size of section headers:\t\t%d (bytes)", Elf32_hdr.e_shentsize);
	fprintf(ptr_dfile, "\n  Number of section headers:\t%d", Elf32_hdr.e_shnum);
	fprintf(ptr_dfile, "\n  Section header string table index:\t%d", Elf32_hdr.e_shstrndx);

	// *********************
	// Print Section Headers
	// *********************

	fprintf(ptr_dfile, "\n\nSection Headers:\n");
	fprintf(ptr_dfile, "[Nr] Name\t\tType\t\tAddr     Off    Size\tES Flg Lk Inf Al");
	for (int i = 0; i < Elf32_hdr.e_shnum; i++) {
		char* hname = &headers_name[Elf32_Shd[i].sh_name];
		fprintf(ptr_dfile, "\n[%2d] %s\t", i, hname);
		switch (Elf32_Shd[i].sh_type) {
		case SHT_NULL: fprintf(ptr_dfile, "\t\tNULL\t\t"); break;
		case SHT_PROGBITS: fprintf(ptr_dfile, "PROGBITS\t"); break;
		case SHT_SYMTAB: fprintf(ptr_dfile, "SYMTAB\t\t"); break;
		case SHT_STRTAB: fprintf(ptr_dfile, "STRTAB\t\t"); break;
		case SHT_RELA: fprintf(ptr_dfile, "RELA\t"); break;
		case SHT_HASH: fprintf(ptr_dfile, "HASH\t"); break;
		case SHT_DYNAMIC: fprintf(ptr_dfile, "DYNAMIC\t"); break;
		case SHT_NOTE: fprintf(ptr_dfile, "NOTE\t"); break;
		case SHT_NOBITS: fprintf(ptr_dfile, "\tNOBITS\t\t"); break;
		case SHT_REL: fprintf(ptr_dfile, "REL\t"); break;
		case SHT_SHLIB: fprintf(ptr_dfile, "SHLIB\t"); break;
		case SHT_DYNSYM: fprintf(ptr_dfile, "DYNSYM\t"); break;
		case SHT_LOPROC: fprintf(ptr_dfile, "LOPROC\t"); break;
		case SHT_HIPROC: fprintf(ptr_dfile, "HIPROC\t"); break;
		case SHT_LOUSER: fprintf(ptr_dfile, "LOUSER\t"); break;
		case SHT_HIUSER: fprintf(ptr_dfile, "HIUSER\t"); break;
		default: fprintf(ptr_dfile, "NODEF\t\t"); break;
		}
		fprintf(ptr_dfile, "%08x %06x %06x  %02x  ", Elf32_Shd[i].sh_addr, Elf32_Shd[i].sh_offset, Elf32_Shd[i].sh_size, Elf32_Shd[i].sh_entsize);
		if (Elf32_Shd[i].sh_flags&SHF_WRITE) fprintf(ptr_dfile, "W");
		if (Elf32_Shd[i].sh_flags&SHF_ALLOC) fprintf(ptr_dfile, "A");
		if (Elf32_Shd[i].sh_flags&SHF_EXECINSTR) fprintf(ptr_dfile, "X");
		if (Elf32_Shd[i].sh_flags&SHF_MASKPROC) fprintf(ptr_dfile, "p");
		fprintf(ptr_dfile, "\t%d %d   %d", Elf32_Shd[i].sh_link, Elf32_Shd[i].sh_info, Elf32_Shd[i].sh_addralign);
	}

	// *********************
	// Print Program Headers
	// *********************

	fprintf(ptr_dfile, "\n\nProgram Headers:\n");
	fprintf(ptr_dfile, "  Type\t\tOffset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg\tAlign");
	for (int i = 0; i < Elf32_hdr.e_phnum; i++) {
		fprintf(ptr_dfile, "\n  ");
		switch (Elf32_Phdr[i].p_type) {
		case PT_NULL: fprintf(ptr_dfile, "NULL\t\t"); break;
		case PT_LOAD: fprintf(ptr_dfile, "LOAD\t\t"); break;
		case PT_DYNAMIC: fprintf(ptr_dfile, "DYNAMIC\t\t"); break;
		case PT_INTERP: fprintf(ptr_dfile, "INTERP\t\t"); break;
		case PT_NOTE: fprintf(ptr_dfile, "NOTE\t"); break;
		case PT_SHLIB: fprintf(ptr_dfile, "SHLIB\t"); break;
		case PT_PHDR: fprintf(ptr_dfile, "PHDR\t"); break;
		case PT_LOPROC: fprintf(ptr_dfile, "LOPROC\t"); break;
		case PT_HIPROC: fprintf(ptr_dfile, "HUPROC\t\t"); break;
		default: fprintf(ptr_dfile, "NODEF\t\t"); break;
		}
		fprintf(ptr_dfile, "0x%06x 0x%08x 0x%08x 0x%05x 0x%05x ", Elf32_Phdr[i].p_offset, Elf32_Phdr[i].p_vaddr, Elf32_Phdr[i].p_paddr, Elf32_Phdr[i].p_filesz, Elf32_Phdr[i].p_memsz);
		if (Elf32_Phdr[i].p_flags&PF_R) fprintf(ptr_dfile, "R");
		if (Elf32_Phdr[i].p_flags&PF_W) fprintf(ptr_dfile, "W");
		if (Elf32_Phdr[i].p_flags&PF_X) fprintf(ptr_dfile, "E");
		fprintf(ptr_dfile, "\t0x%x", Elf32_Phdr[i].p_align);
	}

	// ******************
	// Print Symbol Table
	// ******************

	fprintf(ptr_dfile, "\n\nSymbol table '.symtab' conatins %d entries:\n", sym_entries);
	fprintf(ptr_dfile, "  Num:\tValue\t\tSize\tType\tBind\t\tVis\tNdx Name");
	for (int i = 0; i < sym_entries; i++) {
		char st_type = Elf32_Sym[i].st_info & 0xF;
		char st_bind = Elf32_Sym[i].st_info >> 4;
		char* sname = &syms_name[Elf32_Sym[i].st_name];
		fprintf(ptr_dfile, "\n  %d:\t%08x\t%d\t\t", i, Elf32_Sym[i].st_value, Elf32_Sym[i].st_size);
		switch (st_type) {
		case STT_NOTYPE: fprintf(ptr_dfile, "NOTYPE\t"); break;
		case STT_OBJECT: fprintf(ptr_dfile, "OBJECT\t"); break;
		case STT_FUNC: fprintf(ptr_dfile, "FUNC\t"); break;
		case STT_SECTION: fprintf(ptr_dfile, "SECTION\t"); break;
		case STT_FILE: fprintf(ptr_dfile, "FILE\t"); break;
		case STT_LOPROC: fprintf(ptr_dfile, "LOPROC\t"); break;
		case STT_HIPROC: fprintf(ptr_dfile, "HIPROC\t"); break;
		default: fprintf(ptr_dfile, "NODEF\t"); break;
		}
		switch (st_bind) {
		case STB_LOCAL: fprintf(ptr_dfile, "LOCAL\t"); break;
		case STB_GLOBAL: fprintf(ptr_dfile, "GLOBAL\t"); break;
		case STB_WEAK: fprintf(ptr_dfile, "WEAK\t"); break;
		case STB_LOPROC: fprintf(ptr_dfile, "LOPROC\t"); break;
		case STB_HIPROC: fprintf(ptr_dfile, "HIPROC\t"); break;
		default: fprintf(ptr_dfile, "NODEF\t"); break;
		}
		fprintf(ptr_dfile, "\t%02x\t%04x %s", Elf32_Sym[i].st_other, Elf32_Sym[i].st_shndx, sname);
	}

	fclose(ptr_dfile);
}

void elf_reader::read_elf(const char* elf_file)
{
	ptr_file = fopen(elf_file, "rb");

	// Read Header Table
	fread(&Elf32_hdr, sizeof(Elf32_hdr), 1, ptr_file);
	format_elf32_hdr();

	// Point to Program Headers
	fseek(ptr_file, Elf32_hdr.e_phoff, SEEK_SET);

	// Read Program Headers table
	Elf32_Phdr = new Elf32_Phdr_t[Elf32_hdr.e_phnum];
	fread(Elf32_Phdr, (sizeof(*Elf32_Phdr)*Elf32_hdr.e_phnum), 1, ptr_file);
	format_elf32_phdr();

	// Generate Memory
	entry_ptr = Elf32_hdr.e_entry;
	base_addr = Elf32_hdr.e_entry;//Elf32_Phdr[loadable_segment].p_paddr;
	mem_size = 0x20000;
	mem = new uint8_t[mem_size];

	// Point to section Headers
	fseek(ptr_file, Elf32_hdr.e_shoff, SEEK_SET);

	// Read Section Header table
	Elf32_Shd = new Elf32_Shd_t[Elf32_hdr.e_shnum];
	fread(Elf32_Shd, (sizeof(*Elf32_Shd)*Elf32_hdr.e_shnum), 1, ptr_file);
	format_elf32_shd();

	// Point to String Table Headers
	fseek(ptr_file, Elf32_Shd[Elf32_hdr.e_shstrndx].sh_offset, SEEK_SET);

	// Read Headers Name
	headers_name = new char[Elf32_Shd[Elf32_hdr.e_shstrndx].sh_size];
	fread(headers_name, Elf32_Shd[Elf32_hdr.e_shstrndx].sh_size, 1, ptr_file);

	// Point to Symbol Table Section
	fseek(ptr_file, Elf32_Shd[sym_t_indx].sh_offset, SEEK_SET);

	// Read Symbols table
	sym_entries = Elf32_Shd[sym_t_indx].sh_size / Elf32_Shd[sym_t_indx].sh_entsize;
	Elf32_Sym = new Elf32_Sym_t[sym_entries];
	fread(Elf32_Sym, Elf32_Shd[sym_t_indx].sh_size, 1, ptr_file);
	format_elf32_sym();

	// Point to Symbol Names Section
	fseek(ptr_file, Elf32_Shd[Elf32_Shd[sym_t_indx].sh_link].sh_offset, SEEK_SET);

	// Read Symbol Names 
	syms_name = new char[Elf32_Shd[Elf32_Shd[sym_t_indx].sh_link].sh_size];
	fread(syms_name, Elf32_Shd[Elf32_Shd[sym_t_indx].sh_link].sh_size, 1, ptr_file);

	// Set Main & Start Pointer
	main_ptr = find_symbol("main");
	start_ptr = find_symbol("_start");

	fclose(ptr_file);
}

void elf_reader::format_elf32_sym(void)
{
	if (Elf32_hdr.e_ident.ei_data == ELFDATA2MSB) {
		for (int i = 0; i < sym_entries; i++) {
			change_endianess((uint8_t*)(&Elf32_Sym[i].st_name), 4);
			change_endianess((uint8_t*)(&Elf32_Sym[i].st_value), 4);
			change_endianess((uint8_t*)(&Elf32_Sym[i].st_size), 4);
			change_endianess((uint8_t*)(&Elf32_Sym[i].st_shndx), 2);
		}
	}
}

void elf_reader::format_elf32_phdr(void)
{
	if (Elf32_hdr.e_ident.ei_data == ELFDATA2MSB) {
		for (int i = 0; i < Elf32_hdr.e_phnum; i++) {
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_type), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_offset), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_vaddr), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_paddr), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_filesz), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_memsz), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_flags), 4);
			change_endianess((uint8_t*)(&Elf32_Phdr[i].p_align), 4);

			if (Elf32_Phdr[i].p_type == PT_LOAD) {
				loadable_segment = i;
			}
		}
	}
}

void elf_reader::format_elf32_shd(void)
{
	if (Elf32_hdr.e_ident.ei_data == ELFDATA2MSB) {
		for (int i = 0; i < Elf32_hdr.e_shnum; i++) {
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_name), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_type), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_flags), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_addr), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_offset), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_size), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_link), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_info), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_addralign), 4);
			change_endianess((uint8_t*)(&Elf32_Shd[i].sh_entsize), 4);
			if (Elf32_Shd[i].sh_type == SHT_SYMTAB)
				sym_t_indx = i;
			if (Elf32_Shd[i].sh_flags&SHF_ALLOC) {
				fseek(ptr_file, Elf32_Shd[i].sh_offset, SEEK_SET);
				fread(&mem[Elf32_Shd[i].sh_addr], Elf32_Shd[i].sh_size, 1, ptr_file);
			}
		}
	}
}

void elf_reader::format_elf32_hdr(void)
{
	if (Elf32_hdr.e_ident.ei_data == ELFDATA2MSB) {
		change_endianess((uint8_t*)(&Elf32_hdr.e_type), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_machine), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_version), 4);
		change_endianess((uint8_t*)(&Elf32_hdr.e_entry), 4);
		change_endianess((uint8_t*)(&Elf32_hdr.e_phoff), 4);
		change_endianess((uint8_t*)(&Elf32_hdr.e_shoff), 4);
		change_endianess((uint8_t*)(&Elf32_hdr.e_flags), 4);
		change_endianess((uint8_t*)(&Elf32_hdr.e_ehsize), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_phentsize), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_phnum), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_shentsize), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_shnum), 2);
		change_endianess((uint8_t*)(&Elf32_hdr.e_shstrndx), 2);
	}
}

void elf_reader::change_endianess(uint8_t* data, uint8_t n_bytes)
{
	for (int i = 0; i < (n_bytes / 2); i++) {
		uint8_t tmp = data[i];
		data[i] = data[n_bytes - i - 1];
		data[n_bytes - i - 1] = tmp;
	}
}

uint32_t elf_reader::find_symbol(const char* sym_name)
{
	int i = 0;
	bool sym_found = false;

	while ((i < sym_entries) && (sym_found == false)) {
		char* sname = &syms_name[Elf32_Sym[i].st_name];
		if (!strcmp(sname, sym_name))
			sym_found = true;
		else
			i++;
	}

	return Elf32_Sym[i].st_value;
}
