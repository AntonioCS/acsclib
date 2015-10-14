/* 
 * File:   LinkedList.h
 * Author: antoniocs
 *
 * Created on 26 de Setembro de 2015, 19:54
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct LinkedList LinkedList;
    typedef struct LinkedListNode LinkedListNode;

    struct LinkedList {
        LinkedListNode *head;
        LinkedListNode *tail;
    };

    struct LinkedListNode {
        void *data;
        LinkedListNode *next;
    };

    LinkedList *LLInit();

    LinkedListNode *LLAddHead(LinkedList *, void *);
    LinkedListNode *LLAddTail(LinkedList *, void *);
    LinkedListNode *LLAdd(LinkedList *, void *);

    void *LLRemoveHead(LinkedList *);
    void *LLRemoveTail(LinkedList *);
    void *LLRemoveNode(LinkedList *, LinkedListNode *);

    typedef int (*LLFindCompareFuncPtr)(void *, void *);    
    LinkedListNode *LLFindNodeByData(LinkedList *, void *, LLFindCompareFuncPtr);
    LinkedListNode *LLFindNodeByNext(LinkedList *, LinkedListNode *);


#ifdef	__cplusplus
}
#endif

#endif	/* LINKEDLIST_H */

