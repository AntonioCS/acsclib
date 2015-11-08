/* 
 * File:   HashTable.h
 * Author: antoniocs
 *
 * Created on 25 de Outubro de 2015, 17:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../LinkedList/Double/DobLinkedList.h"

#ifndef HASHTABLE_H
#define	HASHTABLE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define HASHTABLE_DEFAULT_SIZE 

    typedef struct HashTable {
        unsigned items;
        unsigned size;

        //array of hash tables
        DobLinkedList **htable;

        bool (*comp)(const void *, const void *);
        bool (*del)(void *);
    } HashTable;

    struct HashTableInitParams {        
        bool (*comp)(const void *, const void *);
        bool (*del)(void *);
    };

    HashTable *HashTableInitBase(const struct HashTableInitParams *);
    void HashTableAdd(HashTable *, char *, void *);
    void HashTableRemove(HashTable *, void *);

#define HashTableInit(...) HashTableInitBase(&( \
    (struct HashTableInitParams){\
            .comp = NULL,\
            .del = NULL,\
            __VA_ARGS__\
    }\
))

#ifdef	__cplusplus
}
#endif

#endif	/* HASHTABLE_H */

