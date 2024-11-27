#include "pollards_kangaroos.h"
#include "xoshiro.h"

#define G_LOW 0b0011000011000011000011000011000011000011000011000011000011000001UL

static const num128 g = {.t = {4398046511104ULL, 0}};

static const num128 g_size = {.t = {G_LOW, G_LOW}};

struct parameterisation parameters = {
    .k = 32,
    .log_mu = 31,
    .log_d_inv = 26,
    .kangaroo_init_exp = {.t = {((uint64_t)1 << 63), 0}}
};

num128 gexp(uint64_t x)
{
    num128 base = g;
    num128 res = {.t = {1, 0}};

    while (1)
    {
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

void incr_exp(num128 *exp, uint64_t incr)
{
    if (exp->t[0] > (~incr)){
        exp->t[1]++;
    }

    exp->t[0] += incr;

    if (exp->t[1] < g_size.t[1]){
        return;
    }

    if (exp->s >= g_size.s){
        exp->s -= g_size.s;
    }
}

uint64_t gen_rdm(void){
	return xoshiro256plus_random();
}

num128 dlog64(num128 target)
{   
    // Create masks for jump selection and distinguishing elements
    uint64_t k_mask = parameters.k - 1;
    num128 *Jmap = calloc(parameters.k, sizeof(num128));
    if (!Jmap)
    {
        fprintf(stderr, "Failed to allocate memory for Jmap\n");
        exit(1);
    }

    uint64_t *Jmap_exp = calloc(parameters.k, sizeof(uint64_t));
    if (!Jmap_exp)
    {
        fprintf(stderr, "Failed to allocate memory for Jmap_exp\n");
        exit(1);
    }

    uint64_t d_mask = ((uint64_t)1 << parameters.log_d_inv) - 1;
    
    for (unsigned i = 0; i < parameters.k; i++)
    {   
        // Randomly generate an exponent
        uint64_t exponent = xoshiro256plus_random() & (((uint64_t)1 << (parameters.log_mu + 1)) - 1);
        Jmap_exp[i] = exponent;
        Jmap[i] = gexp(exponent); // Precompute g^exponent for efficiency
    }

    // Initialize a hash table to store traps
    struct Hashmap *traps = init_hash(1 << 4);

    // Set up the tame kangaroo starting position
    num128 b;
    memcpy(&b, &(parameters.kangaroo_init_exp), sizeof(num128));

    num128 tame_kangaroo = gexp(b.t[0]);
    num128 c = {.t = {0, 0}}; // Exponent for the wild kangaroo
    
    // Initialize the wild kangaroo at the target position
    num128 wild_kangaroo;
    memcpy(&wild_kangaroo, &target, sizeof(num128));

    uint64_t wk_jump; // Jump index for the wild kangaroo
    uint64_t tk_jump; // Jump index for the tame kangaroo

    struct HashNode *trap;

    // Iteration counters for performance measurement
    uint64_t iter_count = 0;
    uint64_t wk_trap_count = 0;
    uint64_t tk_trap_count = 0;

    num128 res; // Result to store the computed exponent

    // Iterate until the wild kangaroo and tame kangaroo meet
    while (1)
    {
        wk_jump = wild_kangaroo.t[0] & k_mask;
        incr_exp(&c, Jmap_exp[wk_jump]);

        wild_kangaroo = mul11585(wild_kangaroo, Jmap[wk_jump]);

        // Check if the wild kangaroo is on a distinguished element
        if ((wild_kangaroo.t[0] & d_mask) == 0)
        {
            trap = add_hash(traps, wild_kangaroo, c); // Attempt to lay a trap
            if (trap != NULL)
                {
                    res = distance_exp(trap->value, c);
                    break;
                }
            wk_trap_count++;
        }

        // Tame kangaroo jump logic
        tk_jump = tame_kangaroo.t[0] & k_mask;
        incr_exp(&b, Jmap_exp[tk_jump]);
        tame_kangaroo = mul11585(tame_kangaroo, Jmap[tk_jump]);
        
        // Check if the tame kangaroo is on a distinguished element
        if ((tame_kangaroo.t[0] & d_mask) == 0)
        {
            trap = add_hash(traps, tame_kangaroo, b); // Attempt to lay a trap
                if (trap != NULL)
                {
                    res = distance_exp(b, trap->value);  // Attempt to lay a trap
                    break;
                }
            tk_trap_count++;
        }
        iter_count++;
    }

    // Print performance metrics
    printf("\n");
    printf("Iterations: %lu\n", iter_count);
    printf("Wild kangaroo traps: %lu\n", wk_trap_count);
    printf("Tame kangaroo traps: %lu\n", tk_trap_count);
    printf("\n");

    // Free allocated memory
    free(Jmap);
    free(Jmap_exp);
    free_hash(traps);

    return res;
}