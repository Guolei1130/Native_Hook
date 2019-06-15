//
// Created by vipkid on 2019/6/6.
//

#ifndef ELF_HOOK_ELF_HOOK_H
#define ELF_HOOK_ELF_HOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>

#include "elf_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    const char* name;
    Elf_Addr base;
    Elf_Addr bias;
    uint32_t privilege;

    Elf_Ehdr* ehdr;
    Elf_Phdr* phdr;
    Elf_Shdr* shdr;

    Elf_Dyn* dyn;
    size_t dyn_count;

    Elf_Sym* sym;
    size_t sym_count;

    const char* symstr;

    Elf_Addr plt_rel;
    size_t plt_rel_count;

    Elf_Addr rel;
    size_t rel_count;

    size_t nbucket;
    unsigned *bucket;
    size_t nchain;
    unsigned *chain;

    int use_rela;
} loaded_soinfo;

extern loaded_soinfo *elfhook_open(const char *so_path);

extern int elfhook_replace(const loaded_soinfo *soinfo, const char *func_name, void *new_func,
                           void **original_func);

extern void elfhook_close(loaded_soinfo *soinfo);

#ifdef __cplusplus
}
#endif

#endif //ELF_HOOK_ELF_HOOK_H
