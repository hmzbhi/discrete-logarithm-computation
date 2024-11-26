#include "pollards_kangaroos.h"

static const num128 g = {.t = {4398046511104ULL, 0}};

num128 gexp(uint64_t x){
    num128 base = g;
    num128 res = {.t = {1, 0}};

    while (1){
        if (x & 1){
            res = mul11585(res, base);
        }
        x >>= 1;
        if (x == 0){
            break;
        }
        base = mul11585(base, base);
    }
    return res;
}