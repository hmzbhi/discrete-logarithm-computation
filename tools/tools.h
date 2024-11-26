#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../src/mul11585.h"

/* Hashmap Structure */
struct HashNode
{
  num128 key;
  num128 value;
  struct HashNode *next_node;
};

struct Hashmap
{
  struct HashNode **nodes;
  uint64_t size;
  uint64_t mask;
};


/**
 * @brief Initializes a hashmap to store chaining values for collision search.
 *
 * @param size The size of the hashmap.
 * @return A pointer to the initialized hashmap structure.
 */

struct Hashmap* init_hash(uint64_t size);


/**
 * @brief Search for a value in the hash table; if not found, insert it. 
 * Returns the corresponding node if the value is found, or NULL if it is not.
 *
 * @param hash The hashmap to add the key-value pair to.
 * @param key The key.
 * @param value The value.
 * @return A pointer to the hashnode containing the key-value pair.
 */

struct HashNode* add_hash(struct Hashmap* hash, num128 key, num128 value);

/**
 * @brief Frees the memory allocated for a hashmap.
 *
 * @param hash The hashmap to free.
 */

void free_hash(struct Hashmap* hash);

/**
 * @brief Calculates the absolute difference between two `num128` values.
 *
 * @param a The first value.
 * @param b The second value.
 * @return The distance between `a.s` and `b.s`.
 */

num128 distance_exp(num128 a, num128 b);
