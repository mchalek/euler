#ifndef _KMBITS_H
#define _KMBITS_H

#include <assert.h>
#include<stdint.h>

// I think the builtin cpu checking is in gcc-4.8 only
#define __BUILTIN_CPU_FEATURES__ ((__GNUC__ > 3) && (__GNUC__MINOR__ > 7))

__attribute__ ((constructor))
void __cpuid__(void) 
{
#if __BUILTIN_CPU_FEATURES__
    __builtin_cpu_init();
#endif
}

static inline int _leadz(uint64_t x)
{
    return __builtin_clzl(x);
}

static inline int _trailz(uint64_t x)
{
    return __builtin_ctzl(x);
}

static inline int _popcnt(uint64_t x)
{
// __builtin_popcountl() sucks on machines lacking instruction
#if __BUILTIN_CPU_FEATURES__
    if(__builtin_cpu_supports("popcnt")) {
        return __builtin_popcountl(x);
    } else {
#endif
        x = (x & 0x5555555555555555UL) + ((x >> 1) & 0x5555555555555555UL);
        x = (x & 0x3333333333333333UL) + ((x >> 2) & 0x3333333333333333UL);
        x = (x & 0x0F0F0F0F0F0F0F0FUL) + ((x >> 4) & 0x0F0F0F0F0F0F0F0FUL);
        return (x * 0x0101010101010101UL) >> 56;
#if __BUILTIN_CPU_FEATURES__
    }
#endif
}


#endif

