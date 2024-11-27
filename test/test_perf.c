#include "../src/pollards_kangaroos.h"

#define NB_TESTS 10

void test(){
    for (int i = 0; i < NB_TESTS; i++){
        uint64_t exp = gen_rdm();
        num128 target = gexp(exp);

        printf("- Test %d\n", i);
        printf("target = ");
        print_num128(target);
        printf(", exp = %lu\n", exp);

        uint64_t start = clock();
        num128 res = dlog64(target);
        uint64_t end = clock();

        num128 obt = gexp(res.t[0]);

        if (!memcmp(&target, &obt, sizeof(num128))) {
            printf("PASSED\n");
            printf("ticks: %lu\n", end - start);

        } else {
            printf("FAILED\n");
        }
        printf("\n");
    }
}

int main(){
    test();
    return 0;
}