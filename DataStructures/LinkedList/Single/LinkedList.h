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
        LinkedListNode *current;
    };

    struct LinkedListNode {
        void *data;
        LinkedListNode *next;
    };

    LinkedList *LLInit();

    int LLAddHead(LinkedList *, void *);
    int LLAddTail(LinkedList *, void *);
    int LLAdd(LinkedList *, void *);


    void *LLRemoveHead(LinkedList *);
    void *LLRemoveTail(LinkedList *);
    void *LLRemoveNode(LinkedList *, LinkedListNode *);

    void *LLFindNode(LinkedList *, void *);

#ifdef	__cplusplus
}
#endif

#endif	/* LINKEDLIST_H */

