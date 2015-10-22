/* 
 * File:   DLinkedList.h
 * Author: antoniocs
 *
 * Created on 16 de Outubro de 2015, 16:19
 */

#include <stdio.h>
#include <stdbool.h>

#ifndef DobLINKEDLIST_H
#define	DobLINKEDLIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct DobLinkedListNode {
        void *data;
        
        struct DobLinkedListNode *prev;
        struct DobLinkedListNode *next;
    } DobLinkedListNode;

    typedef struct DobLinkedList {
        DobLinkedListNode *head;
        DobLinkedListNode *tail;

        unsigned int nodeCount;
    } DobLinkedList;

    DobLinkedList *DobLLInit();

    DobLinkedListNode *DobLLAddHead(DobLinkedList *, void *);
    DobLinkedListNode *DobLLAddTail(DobLinkedList *, void *);
    DobLinkedListNode *DobLLAdd(DobLinkedList *, void *);

    void *DobLLRemoveHead(DobLinkedList *);
    void *DobLLRemoveTail(DobLinkedList *);
    void *DobLLRemoveNode(DobLinkedList *, DobLinkedListNode *);

    DobLinkedListNode *DobLLFindNodeByData(DobLinkedList *, void *, bool (*comp)(const void *, const void *));
    DobLinkedListNode *DobLLFindNodeByNext(DobLinkedList *, DobLinkedListNode *);
    DobLinkedListNode *DobLLFindNodeByPrev(DobLinkedList *, DobLinkedListNode *);

#ifdef	__cplusplus
}
#endif

#endif	/* DobLINKEDLIST_H */

