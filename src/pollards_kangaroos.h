#include "mul11585.h"
#include "../tools/tools.h"

/**
 * @brief Represents the parameters for the Pollard's kangaroo algorithm.
 */
struct parameterisation {
    uint64_t k;
    uint64_t log_mu;
    uint64_t log_d_inv;
    num128 kangaroo_init_exp;
};

/**
 * @brief Generates a 64-bit random number using the xoshiro256+ random number generator.
 *
 * @return A 64-bit random unsigned integer.
 */

uint64_t gen_rdm(void);

/**
 * @brief Computes \( g^x \) using repeated squaring and modular multiplication.
 *
 * @param x The exponent for which \( g^x \) is to be calculated.
 * @return A num128 structure representing \( g^x \).
 */

num128 gexp(uint64_t x);

/**
 * @brief Solves the discrete logarithm problem \( g^x = \text{target} \) using Pollard's kangaroo method.
 *
 * @param target The target value for which the discrete logarithm is to be computed.
 * @return A num128 number representing the exponent \( x \) such that \( g^x = \text{target} \).
 */

num128 dlog64(num128 target);