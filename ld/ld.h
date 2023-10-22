/*
    This file is part of duckOS.
    
    duckOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    duckOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with duckOS.  If not, see <https://www.gnu.org/licenses/>.
    
    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <kernel/api/page_size.h>
#include <string>

#define ELF_MAGIC 0x464C457F //0x7F followed by 'ELF'

#define ELF32 1
#define ELF64 2

#define ELF_LITTLE_ENDIAN 1
#define ELF_BIG_ENDIAN 2

#define ELF_TYPE_RELOCATABLE 1
#define ELF_TYPE_EXECUTABLE 2
#define ELF_TYPE_SHARED 3
#define ELF_TYPE_CORE 4

#define ELF_NO_ARCH 0
#define ELF_X86 3

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6

#define PF_X 1u
#define PF_W 2u
#define PF_R 4u

#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH 	15
#define DT_SYMBOLIC	16
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_INIT_ARRAY	25
#define DT_INIT_ARRAYSZ	27
#define DT_ENCODING	32
#define OLD_DT_LOOS		0x60000000
#define DT_LOOS			0x6000000d
#define DT_HIOS			0x6ffff000
#define DT_VALRNGLO		0x6ffffd00
#define DT_VALRNGHI		0x6ffffdff
#define DT_ADDRRNGLO	0x6ffffe00
#define DT_ADDRRNGHI	0x6ffffeff
#define DT_VERSYM		0x6ffffff0
#define DT_RELACOUNT	0x6ffffff9
#define DT_RELCOUNT		0x6ffffffa
#define DT_FLAGS_1		0x6ffffffb
#define DT_VERDEF		0x6ffffffc
#define	DT_VERDEFNUM	0x6ffffffd
#define DT_VERNEED		0x6ffffffe
#define	DT_VERNEEDNUM	0x6fffffff
#define OLD_DT_HIOS     0x6fffffff
#define DT_LOPROC		0x70000000
#define DT_HIPROC		0x7fffffff

#define SHT_NULL		0
#define SHT_PROGBITS	1
#define SHT_SYMTAB		2
#define SHT_STRTAB		3
#define SHT_RELA		4
#define SHT_HASH		5
#define SHT_DYNAMIC		6
#define SHT_NOTE		7
#define SHT_NOBITS		8
#define SHT_REL			9
#define SHT_SHLIB		10
#define SHT_DYNSYM		11
#define SHT_NUM			12
#define SHT_LOPROC		0x70000000
#define SHT_HIPROC		0x7fffffff
#define SHT_LOUSER		0x80000000
#define SHT_HIUSER		0xffffffff

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

#define R_386_NONE		0
#define R_386_32		1
#define R_386_PC32		2
#define R_386_GOT32		3
#define R_386_PLT32		4
#define R_386_COPY		5
#define R_386_GLOB_DAT	6
#define R_386_JMP_SLOT	7
#define R_386_RELATIVE	8
#define R_386_TLS_TPOFF	14

#define ELF32_R_SYM(x) ((x) >> 8u)
#define ELF32_R_TYPE(x) ((x) & 0xffu)

typedef struct {
	unsigned char	e_ident[16];
	uint16_t		e_type;
	uint16_t		e_machine;
	uint32_t		e_version;
	uint32_t		e_entry;  /* Entry point */
	uint32_t		e_phoff;
	uint32_t		e_shoff;
	uint32_t		e_flags;
	uint16_t		e_ehsize;
	uint16_t		e_phentsize;
	uint16_t		e_phnum;
	uint16_t		e_shentsize;
	uint16_t		e_shnum;
	uint16_t		e_shstrndx;
} elf32_ehdr;

typedef struct {
	uint32_t p_type;
	uint32_t p_offset;
	uint32_t p_vaddr;
	uint32_t p_paddr;
	uint32_t p_filesz;
	uint32_t p_memsz;
	uint32_t p_flags;
	uint32_t p_align;
} elf32_pheader;

typedef struct  {
	int32_t d_tag;
	uint32_t d_val;
} elf32_dynamic;

typedef struct {
	uint32_t	st_name;
	uint32_t	st_value;
	uint32_t	st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	uint16_t	st_shndx;
} elf32_sym;

typedef struct {
	uint32_t	r_offset;
	uint32_t	r_info;
} elf32_rel;

typedef struct {
	uint32_t	r_offset;
	uint32_t	r_info;
	int32_t 	r_addend;
} elf32_rela;

typedef struct {
	uint32_t	sh_name;
	uint32_t	sh_type;
	uint32_t	sh_flags;
	uint32_t	sh_addr;
	uint32_t	sh_offset;
	uint32_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint32_t	sh_addralign;
	uint32_t	sh_entsize;
} elf32_sheader;

typedef int (*main_t)(int argc, char* argv[], char* envp[]);

class Object {
public:
	Object() = default;
	~Object() = default;

	static Object* open_library(char* library_name);

	int load(char* name_cstr, bool is_main_executable);
	int calculate_memsz();
	int read_headers();
	int load_dynamic_table();
	void read_dynamic_table();
	int load_sections();
	void mprotect_sections();
	int read_copy_relocations();
	int read_symbols();
	int relocate();

	std::string name;
	int fd = 0;
	elf32_ehdr* header = nullptr;
	size_t memsz = 0;
	size_t memloc = 0;
	size_t calculated_base = 0;
	bool loaded = false;

	char* string_table = nullptr;
	size_t string_table_size = 0;
	elf32_sym* symbol_table = nullptr;
	size_t symbol_table_size = 0;
	uint32_t* hash = nullptr;
	void (**init_array)() = nullptr;
	size_t init_array_size = 0;
	void (*init_func)() = nullptr;
	main_t entry;

	std::vector<char*> required_libraries;
	uint8_t* mapped_file = nullptr;
	size_t mapped_size = 0;
	std::vector<elf32_pheader> pheaders;
	std::vector<elf32_sheader> sheaders;
	std::vector<elf32_dynamic> dynamic_table;
};

std::string find_library(char* library_name);

