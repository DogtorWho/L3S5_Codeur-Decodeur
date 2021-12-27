/**
 * @file Huffman_PriorityQueue.c
 * File containing functions to control a priority queue.
 */

#include "Huffman_PriorityQueue.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

QueueNode* init_QueueNode(HuffmanTreeNode* data){
  assert(data != NULL);
  QueueNode* node = malloc(sizeof(QueueNode));
  assert(node != NULL);

  node->data = data;
  node->next = NULL;

  return node;
}

void free_QueueNode(QueueNode *node){
  assert(node != NULL);

  //free_HuffmanTreeNode(node->data);
  free(node);
}

void show_QueueNode(const QueueNode *node){
  assert(node != NULL);

  if(node->data == NULL)
    printf("data is NULL\n");
  else
    show_HuffmanTreeNode(node->data);
}

/* --------------------------------------------------------------- */

Queue* init_Queue(){
  Queue* q = malloc(sizeof(Queue));
  assert(q != NULL);

  q->first = NULL;
  q->size = 0;

  return q;
}

void free_Queue(Queue *q){
  assert(q != NULL);

  for(QueueNode *i = q->first; i; ) {
    QueueNode *N = i;
    i = i->next;
    free(N);
  }

  free(q);
}

void show_Queue(const Queue *q){
  assert(q != NULL);
  printf("   = Affichage de la queue a %d elements =\n\n", q->size);
	if(q->size == 0){
		printf(" - Queue vide, rien a afficher\n");
		printf("-----------------------------------------\n");
	}
	else{
    QueueNode* tmp = q->first;
    while(tmp != NULL){
      show_QueueNode(tmp);
      tmp = tmp->next;
    }
	}
}

void insertFirst_Queue(Queue *q, QueueNode *node){
  assert(q != NULL);
  assert(node != NULL);

  node->next = q->first;
  q->first = node;

  q->size++;
}

void insertLast_Queue(Queue *q, QueueNode *node){
  assert(q != NULL);
  assert(node != NULL);

  if(q->first == NULL){
    insertFirst_Queue(q, node);
  }
  else{
    QueueNode* tmp = q->first;
    while(tmp->next != NULL){
      tmp = tmp->next;
    }
    tmp->next = node;

    q->size++;
  }
}

void insert_Queue(Queue *q, QueueNode *node){
  assert(q != NULL);
  assert(node != NULL);

  if(q->first == NULL){
    insertFirst_Queue(q, node);
  }
  else{
    QueueNode* tmp = q->first;
    while(tmp != NULL){
      if(tmp->data->key > node->data->key){
        node->next = tmp->next;
        tmp->next = node;
        q->size++;
        break;
      }

      if(tmp->next == NULL){
        insertLast_Queue(q, node);
        break;
      }

      tmp = tmp->next;
    }
  }
}

void removeFirst_Queue(Queue *q){
  assert(q != NULL);

  if(q->first != NULL){
    QueueNode* rm = q->first;
    q->first = q->first->next;
    free_QueueNode(rm);

    q->size--;
  }
}
