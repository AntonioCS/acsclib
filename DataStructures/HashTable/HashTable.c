#include "HashTable.h"
#include <string.h>
#include "../../dbg.h"

#define DEFAULT_SIZE_LOCATION 0

typedef struct {
    char *key;
    void *value;
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
    check(htNode, "Unable to create HashTable Node\n");

    htNode->key = key;
    htNode->value = data;

    return htNode;

error:
    return NULL;
}

static bool compHashTableNodeKey(const void *cmp, const void *cmp2) {
    HashTableNode *a = (HashTableNode *) cmp;
    HashTableNode *b = (HashTableNode *) cmp2;

    return (strcmp(a->key, b->key) == 0);
}

bool HashTableAdd(HashTable *ht, char *key, void *data) {
    unsigned key_numeric = hashResult(ht, key, strlen(key));
    check(key_numeric < ht->size, "Returned key is bigger than size: %s --- %u\n", key, key_numeric);

#if defined(DEBUG_HASHTABLE)
    printf("Hashtable DEBUG: Numeric key %d from %s\n", key_numeric, key);
#endif

    HashTableNode *htNode = createHtNode(key, data);
    check(htNode, "No hash table Node");

    DobLinkedList *dob = ht->htable[key_numeric];

    if (dob == NULL) {
        dob = DobLLInit();
        check(dob != NULL, "Unable to create Linked List");

        DobLLAdd(dob, htNode);

        ht->htable[key_numeric] = dob;
        ht->items++;
    } else {
        DobLinkedListNode *dobExistingNode = DobLLFindNodeByData(dob, htNode, compHashTableNodeKey);

        if (dobExistingNode != NULL) {
            HashTableNode *htNodeExisting = (HashTableNode *) dobExistingNode->data;
            htNodeExisting->value = data;
        } else {
            DobLLAdd(dob, htNode);
        }
    }

    return true;

error:
    return false;
}

static bool compHashTableNodeKeyString(const void *cmp, const void *cmp2) {
    char *key = (char *) cmp;
    HashTableNode *b = (HashTableNode *) cmp2;

    return (strcmp(key, b->key) == 0);
}

void *HashTableGet(HashTable *ht, char *key) {
    unsigned key_numeric = hashResult(ht, key, strlen(key));

    DobLinkedList *dob = ht->htable[key_numeric];

    if (dob) {
        switch (dob->nodeCount) {
            case 0:
                return NULL;
            case 1:
                return ((HashTableNode *) dob->head->data)->value;
            default:
            {
                DobLinkedListNode *dobExistingNode = DobLLFindNodeByData(dob, key, compHashTableNodeKeyString);

                if (dobExistingNode) {
                    return ((HashTableNode *) dobExistingNode->data)->value;
                }
            }
        }
    }
#if defined(DEBUG_HASHTABLE)
    else {
        printf("Hashtable DEBUG: No value found for key - %s\n", key);
    }
#endif

    return NULL;
}

#if defined(DEBUG_HASHTABLE)

void HashTable_Debug(HashTable *ht) {
    printf("\n-------- HASHTABLE DUMP --------\n");

    printf("Hashtable size: %d\n", ht->size);
    printf("Hashtable items: %d\n", ht->items);

    for (int i = 0; i < ht->size; i++) {
        DobLinkedList *dob = ht->htable[i];

        if (dob) {
            printf("Listing item %d:\n", i);
            DobLinkedListNode *node = dob->head;

            while (node) {
                HashTableNode *hnode = (HashTableNode *) node->data;

                printf("\tHashNode Key: %s\n", hnode->key);
                printf("\tHashNode value: %s\n", (char *) hnode->value);

                node = node->next;
            }
        }
    }

    printf("-------- HASHTABLE DUMP END --------\n\n");
}

#endif