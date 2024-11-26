#include "tools.h"

/* Hashmap 
 * init_hash() To initialize my hashmap
 * add_hash() To add an element in my hashmap
 * free_hash() To free the memory allocated for my hashmap
*/

struct Hashmap* init_hash(uint64_t size) 
{	
	struct Hashmap *hash = malloc(sizeof(struct Hashmap));
	if (!hash) 
	{
		fprintf(stderr, "Failed to allocate memory for Hashmap structure.\n");
		exit(EXIT_FAILURE);
	}

	uint64_t size_pow2 = 1;

    while (size_pow2 < size)
    {
        size_pow2 = size_pow2 << 1;
    }

    hash->size = size_pow2;
    hash->mask = size_pow2 - 1;
	hash->nodes = calloc(size, sizeof(struct HashNode*));

    if (!hash->nodes) 
    {
        fprintf(stderr, "Failed to allocate memory for HashNode array.\n");
        exit(EXIT_FAILURE);
    }

	return hash;
}

struct HashNode* add_hash(struct Hashmap* hash, num128 key, num128 value) 
{
	uint64_t h = key.t[0] % hash->size;
	struct HashNode *node = hash->nodes[h];
    while (node != NULL)
    {
        if (memcmp(&(node->key), &key, sizeof(num128)) == 0)
        {
            return node;
        }
        node = node->next_node;
    }
	
    node = malloc(sizeof(struct HashNode));
    if (!node) 
    {
        fprintf(stderr, "Failed to allocate memory for HashNode structure.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(&(node->key), &key, sizeof(num128));
    memcpy(&(node->value), &value, sizeof(num128));
    node->next_node = hash->nodes[h];
    hash->nodes[h] = node;

    return NULL;
}

void free_hash(struct Hashmap* hash) 
{
	for (unsigned i = 0; i < hash->size; i++)
	{
		struct HashNode *node = hash->nodes[i];
		while (node != NULL)
		{
			struct HashNode *next = node->next_node;
			free(node);
			node = next;
		}
	}

	free(hash->nodes);
	free(hash);
}

num128 distance_exp(num128 a, num128 b) {
    num128 res;
    res.s = (a.s >= b.s) ? (a.s - b.s) : (b.s - a.s);
    return res;
}