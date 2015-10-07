
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include "../../../dbg.h"

enum LLAddStrategy {
    HEAD,
    TAIL
};

struct LLFindNodeBaseParams {
    LinkedList *ll;

    void *data;
    LLFindCompareFuncPtr compareFunc;

    LinkedListNode *node;
    LinkedListNode *next;
};

struct FindResult {
    LinkedListNode *prev;
    LinkedListNode *node;
};


static struct FindResult *FindNodeBase(struct LLFindNodeBaseParams *);

typedef bool(*findByFuncPtr)(struct LLFindNodeBaseParams *, struct FindResult *, LinkedListNode *);
static bool FindByData(struct LLFindNodeBaseParams *, struct FindResult *, LinkedListNode *);
//To the outside this function is not really necessary
static struct FindResult *LLFindNode(LinkedList *, LinkedListNode *);
static bool FindByNode(struct LLFindNodeBaseParams *, struct FindResult *, LinkedListNode *);
static bool FindByNextNode(struct LLFindNodeBaseParams *, struct FindResult *, LinkedListNode *);
static struct FindResult *InitFindResult(void);
static bool FindResultSetResult(bool, struct FindResult *, LinkedListNode *);
//static struct LLFindNodeBaseParams *InitLLFindNodeBaseParams();



static LinkedListNode *NodeInit();
static LinkedListNode *LLAddBase(LinkedList *, void *, enum LLAddStrategy);

LinkedList *LLInit() {
    LinkedList *ll = malloc(sizeof (LinkedList));
    check(ll, "Unable to allocate memory for linked list");

    ll->head = NULL;
    ll->tail = NULL;

    return ll;

error:
    return NULL;
}

/**
 * Add an item to the linked list in the head or the tail
 * 
 * @param ll
 * @param data
 * @param type
 * @return int (will be 1 for failure and 0 for sucess)
 */
LinkedListNode *LLAddBase(LinkedList *ll, void *data, enum LLAddStrategy stype) {
    check(ll, "LLAddBase received null pointer");
    LinkedListNode *node = NodeInit(data, NULL);

    if (ll->head == NULL) {
        ll->tail = ll->head = node;
    } else {
        if (stype == HEAD) {
            node->next = ll->head;
            ll->head = node;
        } else {
            ll->tail->next = node;
            ll->tail = ll->tail->next;
        }
    }

    return node;
error:
    return NULL;
}

/**
 * Add a node to the start of the Linked List
 * 
 * @param ll
 * @param data
 * @return
 */
LinkedListNode *LLAddHead(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, HEAD);
}

/**
 * Add a node to the end of the Linked List
 *
 * @param ll
 * @param data
 * @return
 */
LinkedListNode *LLAddTail(LinkedList *ll, void *data) {
    return LLAddBase(ll, data, TAIL);
}

/**
 * Shorter alias for LLAddTail
 * 
 * @param ll
 * @param data
 * @return
 */
LinkedListNode *LLAdd(LinkedList *ll, void *data) {
    return LLAddTail(ll, data);
}

/**
 *
 * @param data
 * @param next
 * @return
 */
LinkedListNode *NodeInit(void *data, LinkedListNode *next) {
    LinkedListNode *lln = malloc(sizeof (LinkedListNode));
    check(lln, "Unable to allocate memory for linked list node");

    lln->data = data;
    lln->next = next;

    return lln;
error:
    return NULL;
}

void *LLRemoveHead(LinkedList *ll) {
    return LLRemoveNode(ll, ll->head);
}

void *LLRemoveTail(LinkedList *ll) {
    return LLRemoveNode(ll, ll->tail);
}

void *LLRemoveNode(LinkedList *ll, LinkedListNode *node) {
    void *data = node->data;

    if (node == ll->head) {
        if (ll->head->next == NULL) {
            ll->head = ll->tail = NULL;
        } else {
            ll->head = ll->head->next;
        }
    } else {
        if (node == ll->tail) {
        }

    }

    return data;
}

struct FindResult *LLFindNode(LinkedList *ll, LinkedListNode *node) {

    struct FindResult *res = FindNodeBase(&((struct LLFindNodeBaseParams) {
        .ll = ll, .node = node}));
    return res;

}

LinkedListNode *LLFindNodeByData(LinkedList *ll, void *data, LLFindCompareFuncPtr func) {

    struct FindResult *res = FindNodeBase(&((struct LLFindNodeBaseParams) {
        .ll = ll, .data = data, .compareFunc = func}));

    LinkedListNode *node = res->node;
    free(res);

    return node;
}

LinkedListNode *LLFindNodeByNext(LinkedList *ll, LinkedListNode *nodeNext) {

    struct FindResult *res = FindNodeBase(&((struct LLFindNodeBaseParams) {
        .ll = ll, .next = nodeNext}));

    LinkedListNode *node = res->node;
    free(res);

    return node;
}

struct FindResult *FindNodeBase(struct LLFindNodeBaseParams *params) {
    findByFuncPtr fptr = NULL;

    if (params->data != NULL && params->compareFunc != NULL) {
        fptr = FindByData;
    } else if (params->node != NULL) {
        fptr = FindByNode;
    } else if (params->next != NULL) {
        fptr = FindByNextNode;
    } else {
        goto error;
    }

    LinkedListNode *node = params->ll->head;
    struct FindResult *res = InitFindResult();

    check(res, "Unable to allocate memory for FindResult structure");
    bool foundNode = false;

    while (node != NULL) {
        if ((foundNode = fptr(params, res, node))) {
            break;
        }
        node = node->next;
    }

    if (foundNode == false) {
        res->node = NULL;
        res->prev = NULL;
    }

    return res;

error:
    return NULL;
}

bool FindByData(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->compareFunc(params->data, node->data) == 0, res, node);
}

bool FindByNode(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->node == node, res, node);
}

/**
 * This one is a bit different from the others in terms of assignment
 *
 * @param params
 * @param res
 * @param node
 * @return
 */
bool FindByNextNode(struct LLFindNodeBaseParams *params, struct FindResult *res, LinkedListNode *node) {
    return FindResultSetResult(params->next == node->next, res, node);
}

bool FindResultSetResult(bool condition, struct FindResult *res, LinkedListNode *node) {
    if (condition) {
        res->node = node;
    } else {
        res->prev = node;
    }

    return condition;
}

struct FindResult *InitFindResult() {
    struct FindResult *res = malloc(sizeof (struct FindResult));
    check(res, "Unable to allocate memory for FindResult");

    res->node = NULL;
    res->prev = NULL;

    return res;

error:
    return NULL;
}

