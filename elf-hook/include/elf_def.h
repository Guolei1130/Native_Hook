//
// Created by vipkid on 2019/6/6.
//

#ifndef ELF_HOOK_ELF_DEF_H
#define ELF_HOOK_ELF_DEF_H

#include <linux/elf.h>

#ifdef __LP64__

typedef Elf64_Ehdr Elf_Ehdr;
typedef Elf64_Phdr Elf_Phdr;
typedef Elf64_Shdr Elf_Shdr;
typedef Elf64_Dyn Elf_Dyn;
typedef Elf64_Sym Elf_Sym;
typedef Elf64_Word Elf_Word;
typedef Elf64_Addr Elf_Addr;
typedef Elf64_Rel Elf_Rel;
typedef Elf64_Rela Elf_Rela;

#define ELF_R_SYM(x) ELF64_R_SYM(x)
#define ELF_R_TYPE(x) ELF64_R_TYPE(x)

#else

typedef Elf32_Ehdr Elf_Ehdr;
typedef Elf32_Phdr Elf_Phdr;
typedef Elf32_Shdr Elf_Shdr;
typedef Elf32_Dyn Elf_Dyn;
typedef Elf32_Sym Elf_Sym;
typedef Elf32_Word Elf_Word;
typedef Elf32_Addr Elf_Addr;
typedef Elf32_Rel Elf_Rel;
typedef Elf32_Rela Elf_Rela;

#define ELF_R_SYM(x) ELF32_R_SYM(x)
#define ELF_R_TYPE(x) ELF32_R_TYPE(x)

#endif

#define DT_GNU_HASH 0x6ffffef5

#endif //ELF_HOOK_ELF_DEF_H
