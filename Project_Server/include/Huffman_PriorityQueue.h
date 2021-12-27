#ifndef _HUFFMAN_QUEUE_
#define _HUFFMAN_QUEUE_

#include "Huffman_Tree.h"

typedef struct QueueNode {
  HuffmanTreeNode *data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode* first;
  int size;
} Queue;


QueueNode* init_QueueNode(HuffmanTreeNode* data);
void free_QueueNode(QueueNode *node);
void show_QueueNode(const QueueNode *node);
/* --------------------------------------------------------------- */
Queue* init_Queue();
void free_Queue(Queue *q);
void show_Queue(const Queue *q);
void insertFirst_Queue(Queue *q, QueueNode *node);
void insertLast_Queue(Queue *q, QueueNode *node);
void insert_Queue(Queue *q, QueueNode *node);
void removeFirst_Queue(Queue *q);

#endif
