/* 
 * File:   Queue.h
  *
 * Created on 20 de Outubro de 2015, 23:07
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include <stdio.h>
#include "../LinkedList/Double/DobLinkedList.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef DobLinkedList Queue;

    Queue *QueueInit();
    void QueueEnQueue(Queue *, void *);
    void *QueueDeQueue(Queue *q);


#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */

