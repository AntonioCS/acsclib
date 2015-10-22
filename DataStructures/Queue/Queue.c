#include "Queue.h"

Queue *QueueInit() {
    return DobLLInit();
}

void QueueEnQueue(Queue *q, void *data) {
    DobLLAddTail(q, data);
}

void *QueueDeQueue(Queue *q) {
    return DobLLRemoveHead(q);
}