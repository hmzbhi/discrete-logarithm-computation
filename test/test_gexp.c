#include "../src/pollards_kangaroos.h"

void test(){
    printf("Testing gexp...\n");
    printf("- Test n°1:\n");

    num128 res1 = gexp(257);
    num128 expected1 = {.t = {0x0840EE23EECF13E4ULL, 0x42F953471EDC0ULL}};
    if (res1.t[0] == expected1.t[0] && res1.t[1] == expected1.t[1]){
        printf("PASSED\n");
        printf("Got: ");
        print_num128(res1);
        printf(", Expected: ");
        print_num128(expected1);
        printf("\n");
    } else {
        printf("FAILED\n");
        printf("Expected: ");
        print_num128(expected1);
        printf("\n");
        printf("Got: ");
        print_num128(res1);
        printf("\n");
    }

    printf("- Test n°2:\n");
    num128 res2 = gexp(112123123412345);
    num128 expected2 = {.t = {0xD8BC716B91D838CCULL, 0x21F33CAEB45F4ULL}};
    if (res2.t[0] == expected2.t[0] && res2.t[1] == expected2.t[1]){
        printf("PASSED\n");
        printf("Got: ");
        print_num128(res2);
        printf(", Expected: ");
        print_num128(expected2);
        printf("\n");
    } else {
        printf("FAILED\n");
        printf("Expected: ");
        print_num128(expected2);
        printf("\n");
        printf("Got: ");
        print_num128(res2);
        printf("\n");
    }

    printf("- Test n°3:\n");
    num128 res3 = gexp(18014398509482143);
    num128 expected3 = {.t = {0x25357DAACBF4868FULL, 0x7A2A1DEC09D03ULL}};
    if (res3.t[0] == expected3.t[0] && res3.t[1] == expected3.t[1]){
        printf("PASSED\n");
        printf("Got: ");
        print_num128(res3);
        printf(", Expected: ");
        print_num128(expected3);
        printf("\n");
    } else {
        printf("FAILED\n");
        printf("Expected: ");
        print_num128(expected3);
        printf("\n");
        printf("Got: ");
        print_num128(res3);
        printf("\n");
    }
    printf("\n");
}

int main(){
    test();
    return 0;
}