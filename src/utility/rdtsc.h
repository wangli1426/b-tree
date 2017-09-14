//
// Created by robert on 14/9/17.
//

#ifndef B_TREE_RDTSC_H
#define B_TREE_RDTSC_H

static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
#endif //B_TREE_RDTSC_H
