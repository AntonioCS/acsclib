#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashTable.h"
#include "../../../minunit.h"

int tests_run = 0;
int asserts_run = 0;

static void debug_hashtable(HashTable *ht) {
    printf("Hashtable size: %d\n", ht->size);
    printf("Hashtable items: %d\n", ht->items);

    for (int i = 0; i < ht->size; i++) {
        DobLinkedList *dob = ht->htable[i];

        if (dob) {
            printf("Listing item %d:\n", i);
            DobLinkedListNode *node = dob->head;

            while (node) {
                HashTableNode *hnode = (HashTableNode *)node->data;

                printf("HashNode Key: %s\n", hnode->key);
                printf("HashNode value: %s\n", (char *)hnode->value);

                node = node->next;
            }
        }
    }
}

static char *test_HashTableInit() {
    HashTable *ht = HashTableInit();

    mu_assert("No hast table", ht != NULL);

    return 0;
}

static char *test_HashTableAdd() {
    HashTable *ht = HashTableInit();

    mu_assert("Returned false" , (HashTableAdd(ht, "tes1te", "teste2")));

    return 0;
}

static char *test_HashTableAddOverwrite() {
    HashTable *ht = HashTableInit();

    mu_assert("Returned false" , (HashTableAdd(ht, "tes1te", "teste2")));

    debug_hashtable(ht);

    mu_assert("Returned false" , (HashTableAdd(ht, "tes1te", "teste333332")));

    debug_hashtable(ht);

    return 0;
}

/*
static char *test_HashTableAdd_and_Get() {
    HashTable *ht = HashTableInit();

    mu_assert("Returned false" , (HashTableAdd(ht, "tes1te", "teste2")));

    char *valor = (char *)HashTableGet(ht, "tes1te");
    printf("Valor: %s\n", valor);

    debug_hashtable(ht);

    return 0;
}*/

mu_all_tests(
        test_HashTableInit,
        test_HashTableAdd,
        test_HashTableAddOverwrite
   //     test_HashTableAdd_and_Get
        )

mu_main()