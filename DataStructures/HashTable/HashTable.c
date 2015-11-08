#include "HashTable.h"
#include <string.h>
#include "../../dbg.h"

#define DEFAULT_SIZE_LOCATION 0

int powers_of_two[] = {
    8, //2^3
    16, //2^4
    32, //2^5
    64, //2^6
    128, //2^7
    256, //2^8
    512, //2^9
    1024, // 2^10
    2048, // 2^11
    4096, // 2^12
    8192, // 2^13
    16384, // 2^14
    32768 // 2^15
};

static unsigned oat_hash(void *key, int len) {
    unsigned char *p = key;
    unsigned h = 0;
    int i;

    for (i = 0; i < len; i++) {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}

static unsigned hash(void *key, int len) {
    return oat_hash(key, len);
}

static unsigned hashResult(HashTable *ht, void *key, int len) {
    printf("hash size -> %u -- \n", ht->size);
    return hash(key, len) & ht->size;
}

static DobLinkedList **createDobList(const unsigned size) {
    DobLinkedList **dobl = calloc(size, sizeof *dobl);

    if (dobl) {       
        for (int i = 0; i < size; i++) {
            dobl[i] = NULL;
        }

        return dobl;
    }

    return NULL;
}

HashTable *HashTableInitBase(const struct HashTableInitParams *params) {
    HashTable *ht = calloc(1, sizeof (HashTable));
    check(ht, "Unable to allocate hashtable structure");

    ht->items = 0;
    ht->size = powers_of_two[DEFAULT_SIZE_LOCATION];

    ht->htable = createDobList(ht->size);

    check(ht->htable, "Unable to allocate space for internal struct");

    if (params) {
        if (params->comp) {
            ht->comp = params->comp;
        }
        if (params->del) {
            ht->del = params->del;
        }
    }

    return ht;

error:
    if (ht) {
        free(ht);
    }

    return NULL;
}

void HashTableAdd(HashTable *ht, char *key, void *data) {
    printf("key -> %u\n", hashResult(ht, key, strlen(key)));    
}