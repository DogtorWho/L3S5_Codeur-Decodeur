/**
 * @file Huffman_PriorityQueue.h
 * File containing functions to control a priority queue.
 */

#ifndef _HUFFMAN_QUEUE_
#define _HUFFMAN_QUEUE_

#include "Huffman_Tree.h"

/**
 * @struct QueueNode
 * @brief node of a priority queue
 * @param data pointer of a node in an huffman tree
 * @param next pointer of the next node on the queue
 */
typedef struct QueueNode {
  HuffmanTreeNode *data;
  struct QueueNode *next;
} QueueNode;

/**
 * @struct Queue
 * @brief priority queue
 * @param first pointer of the first node of the priority queue
 * @param size size of the priority queue
 */
typedef struct Queue {
  QueueNode* first;
  int size;
} Queue;

/**
 * @fn QueueNode* init_QueueNode(HuffmanTreeNode* data)
 * @brief initialize a new node of a priority queue (allocates memory)
 * @param data data stocked in the new node created
 * @return the new node created
 */
QueueNode* init_QueueNode(HuffmanTreeNode* data);

/**
 * @fn void free_QueueNode(QueueNode *node)
 * @brief free the memory allocated in the node
 * @param node node to free
 */
void free_QueueNode(QueueNode *node);

/**
 * @fn void show_QueueNode(const QueueNode *node)
 * @brief print the node
 * @param node node to print
 */
void show_QueueNode(const QueueNode *node);

/* --------------------------------------------------------------- */

/**
 * @fn Queue* init_Queue()
 * @brief initialize a new priority queue (allocates memory)
 * @return the new priority queue created
 */
Queue* init_Queue();

/**
 * @fn void free_Queue(Queue *q)
 * @brief free the memory allocated in the priority queue
 * @param q the priority queue to free
 */
void free_Queue(Queue *q);

/**
 * @fn void show_Queue(const Queue *q)
 * @brief print the priority queue
 * @param q the priority queue
 */
void show_Queue(const Queue *q);

/**
 * @fn void insertFirst_Queue(Queue *q, QueueNode *node)
 * @brief insert a node at the first place in the priority queue
 * @param q the priority queue
 * @param node the node to insert
 */
void insertFirst_Queue(Queue *q, QueueNode *node);

/**
 * @fn void insertLast_Queue(Queue *q, QueueNode *node)
 * @brief insert a node at the last place in the priority queue
 * @param q the priority queue
 * @param node the node to insert
 */
void insertLast_Queue(Queue *q, QueueNode *node);

/**
 * @fn void insert_Queue(Queue *q, QueueNode *node)
 * @brief insert a node in the priority queue
 * check the key in the data of each node and insert it if the key is bigger
 * @param q the priority queue
 * @param node the node to insert
 */
void insert_Queue(Queue *q, QueueNode *node);

/**
 * @fn void removeFirst_Queue(Queue *q)
 * @brief remove the first node from the priority queue
 * @param q the priority queue
 */
void removeFirst_Queue(Queue *q);

#endif
