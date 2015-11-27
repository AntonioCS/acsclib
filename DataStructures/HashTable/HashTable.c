#include "HashTable.h"
#include <string.h>
#include "../../dbg.h"

#define DEFAULT_SIZE_LOCATION 0


typedef struct {
    char *key;
    void *data;
} HashTableNode;

int powers_of_two[] = {
    8, //2^3 = 8
    16, //2^4 = 16
    32, //2^5 = 32
    64, //2^6 = 64
    128, //2^7 = 128
    256, //2^8 = 256
    512, //2^9 = 512
    1024, // 2^10 = 1024
    2048, // 2^11 = 2048
    4096, // 2^12 = 4096
    8192, // 2^13 = 8192
    16384, // 2^14 = 16384
    32768 // 2^15 = 32768
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
    return (hash(key, len) % ht->size);
}

static DobLinkedList **createDobListArray(const unsigned size) {
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

    ht->htable = createDobListArray(ht->size);

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

static HashTableNode *createHtNode(char *key, void *data) {
    HashTableNode *htNode = calloc(1, sizeof (HashTableNode));
    check (htNode, "Unable to create HashTable Node\n");

    htNode->key = key;
    htNode->data = data;

    return htNode;

    error:
        return NULL;
}

static bool compHashTableNode(const void *cmp, const void *cmp2) {
    return (strcmp(cmp, cmp2) == 0);
}

static void htAdd(HashTable *ht, unsigned key_numeric, char *key, void *data) {
    HashTableNode *htNode = createHtNode(key, data);
    check(htNode, "No hash table Node");

    DobLinkedList *dob = ht->htable[key_numeric];

    if (dob == NULL) {
        dob = DobLLInit();
        check(dob != NULL, "Unable to create Linked List");

        DobLLAdd(dob, htNode);
    }
    else {
        DobLinkedListNode *dobExistingNode = DobLLFindNodeByData(dob, htNode, compHashTableNode);

        if (dobExistingNode != NULL) {
            HashTableNode *htNodeExisting = (htNodeExisting *)dobExistingNode->data;
            htNodeExisting->data = data;
        }
        else {
            DobLLAdd(dob, htNode);
        }
    }

error:
    return NULL;

}

void HashTableAdd(HashTable *ht, char *key, void *data) {
    unsigned key_numeric = hashResult(ht, key, strlen(key));
    check(key_numeric < ht->size, "Returned key is bigger than size: %s --- %u\n", key, key_numeric);
    htAdd(ht, key_numeric, key, data);

error:
    //do nothing
    ;
}

void *HashTableGet(HashTable *ht, char *key) {

}