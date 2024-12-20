#include "../src/pollards_kangaroos.h"

void test(){
    num128 target = {.t = {0xB6263BF2908A7B09ULL,0x71AC72AF7B138ULL}};
    num128 exp = dlog64(target);

    num128 res = gexp(exp.t[0]);

    if (!memcmp(&res, &target, sizeof(num128))) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
    printf("\n");
}

int main(){
    test();
    return 0;
}