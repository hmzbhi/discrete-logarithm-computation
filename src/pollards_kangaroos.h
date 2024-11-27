#include "mul11585.h"
#include "../tools/tools.h"

struct parameterisation {
    uint64_t k;
    uint64_t log_mu;
    uint64_t log_d_inv;
    num128 kangaroo_init_exp;
};

uint64_t gen_rdm(void);

num128 gexp(uint64_t x);

num128 dlog64(num128 target);