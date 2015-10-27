#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DobLinkedList.h"
#include "../../../dbg.h"

/**
 * Initialize a linked list
 *
 * @return LinkedList *
 */
DobLinkedList *DobLLInit() {
    DobLinkedList *dobll = malloc(sizeof (DobLinkedList));
    check(dobll, "Unable to allocate memory for Double Linked List");

    dobll->head = NULL;
    dobll->tail = NULL;
    dobll->nodeCount = 0;

    return dobll;

error:
    return NULL;
}

//<editor-fold defaultstate="collapsed" desc="Add Functions">

enum AddStrategy {
    HEAD,
    TAIL
};

static DobLinkedListNode *NodeInit(void *data, DobLinkedListNode *prev, DobLinkedListNode *next) {
    DobLinkedListNode *doblln = malloc(sizeof (DobLinkedListNode));
    check(doblln, "Unable to allocate memory for linked list node");

    doblln->data = data;
    doblln->prev = prev;
    doblln->next = next;

    return doblln;
error:
    return NULL;
}

static DobLinkedListNode *DobLLAddBase(DobLinkedList *dobll, void *data, enum AddStrategy stype) {
    check(dobll, "LLAddBase received null pointer");
    DobLinkedListNode *node = NodeInit(data, NULL, NULL);

    if (dobll->head == NULL) {
        dobll->tail = dobll->head = node;
    } else {
        if (stype == HEAD) {
            node->next = dobll->head;
            dobll->head->prev = node;
            dobll->head = node;
        } else {
            dobll->tail->next = node;
            node->prev = dobll->tail;
            dobll->tail = node;
        }
    }

    dobll->nodeCount++;
    return node;
error:
    return NULL;
}

DobLinkedListNode *DobLLAddHead(DobLinkedList *dobll, void *data) {
    return DobLLAddBase(dobll, data, HEAD);
}

DobLinkedListNode *DobLLAddTail(DobLinkedList *dobll, void *data) {
    return DobLLAddBase(dobll, data, TAIL);
}

DobLinkedListNode *DobLLAdd(DobLinkedList *dobll, void *data) {
    return DobLLAddTail(dobll, data);
}

//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="Remove functions">

void *DobLLRemoveHead(DobLinkedList *dobll) {
    return DobLLRemoveNode(dobll, dobll->head);
}

void *DobLLRemoveTail(DobLinkedList *dobll) {
    return DobLLRemoveNode(dobll, dobll->tail);
}

void *DobLLRemoveNode(DobLinkedList *dobll, DobLinkedListNode *node) {
    if (node == NULL) {
        return NULL;
    }
    void *data = node->data;

    if (node == dobll->head) {
        if (dobll->tail == dobll->head) {
            dobll->tail = dobll->head = NULL;
        } else {
            dobll->head = dobll->head->next;
            dobll->head->prev = NULL;
        }
    } else {
        node->prev->next = node->next;

        if (node == dobll->tail) {
            dobll->tail = node->prev;
        } else {
            node->next->prev = node->prev;
        }
    }

    dobll->nodeCount--;
    free(node);
    return data;
}

//</editor-fold>

//<editor-fold defaultstate="collapsed" desc="Find functions">

DobLinkedListNode *DobLLFindNodeByData(DobLinkedList *dobll, void *data, bool(*comp)(const void *, const void *)) {
    DobLinkedListNode *current = dobll->head;

    while (current != NULL) {
        if (comp(data, current->data) == true) {
            break;
        }

        current = current->next;
    }

    return current;
}

//</editor-fold>
