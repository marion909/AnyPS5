#ifndef PRX_LIBC_INCLUDE_SPECIFICS_LINUX_ELFTYPES_HPP
#define PRX_LIBC_INCLUDE_SPECIFICS_LINUX_ELFTYPES_HPP

#include <cstdint>
#include <cstddef>

struct Elf64_Phdr {
    std::uint32_t p_type;
    std::uint32_t p_flags;
    std::uint64_t p_offset;
    std::uint64_t p_vaddr;
    std::uint64_t p_paddr;
    std::uint64_t p_filesz;
    std::uint64_t p_memsz;
    std::uint64_t p_align;
};

#ifdef __APPLE__
using Elf64_Addr = std::uint64_t;
using Elf64_Off = std::uint64_t;
using Elf64_Half = std::uint16_t;
using Elf64_Word = std::uint32_t;
using Elf64_Sword = std::int32_t;
using Elf64_Xword = std::uint64_t;
using Elf64_Sxword = std::int64_t;

struct Elf64_Dyn {
    Elf64_Sxword d_tag;
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
};

#endif

struct dl_phdr_info {
    std::uintptr_t dlpi_addr;
    const char* dlpi_name;
    const Elf64_Phdr* dlpi_phdr;
    std::uint16_t dlpi_phnum;
#ifdef __APPLE__
    unsigned long long dlpi_adds;
    unsigned long long dlpi_subs;
    std::size_t dlpi_tls_modid;
    void* dlpi_tls_data;
#endif
};

#ifdef __APPLE__
#ifndef ElfW
#define ElfW(type) Elf64_##type
#endif
static constexpr std::uint32_t PT_NULL = 0;
static constexpr std::uint32_t PT_DYNAMIC = 2;
static constexpr std::uint32_t PT_INTERP = 3;
static constexpr std::uint32_t PT_NOTE = 4;
static constexpr std::uint32_t PT_TLS = 7;
static constexpr std::uint32_t PF_R = 4;
#endif

static constexpr std::uint32_t PT_LOAD = 1;
static constexpr std::uint32_t PT_GNU_EH_FRAME = 0x6474e550;
static constexpr std::uint32_t PF_X = 1;
static constexpr std::uint32_t PF_W = 2;

#ifdef __APPLE__
extern "C" int dl_iterate_phdr(int (*callback)(dl_phdr_info*, std::size_t, void*), void* data) __asm__("_dl_iterate_phdr_nid_no_patch");
#else
extern "C" int dl_iterate_phdr(int (*callback)(dl_phdr_info*, std::size_t, void*), void* data);
#endif

#endif
