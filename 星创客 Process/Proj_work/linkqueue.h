#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;

typedef struct linkqueuenode{
	datatype data;
	struct linkqueuenode *next;
}linkqueue_node, *linkqueue_pnode;

typedef struct linkqueue{
	linkqueue_pnode front,rear;
}link_queue, *link_pqueue;

extern void init_linkqueue(link_pqueue *Q);
extern bool is_empty_linkqueue(link_pqueue q);
extern bool in_linkqueue(datatype data, link_pqueue q);
extern bool out_linkqueue(link_pqueue q, datatype *D);
extern void show_linkqueue(link_pqueue q);

#endif
