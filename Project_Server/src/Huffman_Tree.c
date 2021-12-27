#include "Huffman_Tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Huffman_PriorityQueue.h"
#include "globals.h"

HuffmanTreeNode* init_HuffmanTreeNode(int key, int data, bool haveData){
  HuffmanTreeNode *node = malloc(sizeof(HuffmanTreeNode));
  assert(node != NULL);

	node->key = key;
  node->data = data;
  node->bit = '0';
	node->binary_value = calloc(SIZE_B_VALUE, 1);
  node->haveData = haveData;

	node->left = NULL;
	node->right = NULL;

	return node;
}

void free_HuffmanTreeNode(HuffmanTreeNode *node){
  if(node != NULL){
		free_HuffmanTreeNode(node->left);
		free_HuffmanTreeNode(node->right);

    //free(node->binary_value);
		free(node);
	}
}

void show_HuffmanTreeNode(const HuffmanTreeNode *node){
  if(node != NULL){
		show_HuffmanTreeNode(node->left);

		printf(" - Key : %d", node->key);
    if(node->haveData)
		  printf("  |  Data : %c", node->data);
    else
      printf("  |  NO DATA");
    printf("  |  bit : %c", node->bit);
    printf("  |  value : %s", node->binary_value);

		printf("\n-----------------------------------------\n");

		show_HuffmanTreeNode(node->right);
	}
}

HuffmanTreeNode* insert_HuffmanTreeNode(HuffmanTreeNode *node, int key, int data, bool haveData){
  assert(node != NULL);

  if(key > node->key){
    if(node->right == NULL){
      node->right = init_HuffmanTreeNode(key, data, haveData);
      return node;
    }
    else{
      return insert_HuffmanTreeNode(node->right, key, data, haveData);
    }
  }
  else{
    if(node->left == NULL){
      node->left = init_HuffmanTreeNode(key, data, haveData);
      return node;
    }
    else{
      return insert_HuffmanTreeNode(node->left, key, data, haveData);
    }
  }
}

/* --------------------------------------------------------------- */

HuffmanTree* init_HuffmanTree(){
  HuffmanTree *ht = malloc(sizeof(HuffmanTree));
  assert(ht != NULL);

	ht->root = NULL;
	ht->size = 0;

	return ht;
}

void free_HuffmanTree(HuffmanTree *ht){
  assert(ht != NULL);

  free_HuffmanTreeNode(ht->root);

  free(ht);
}

void show_HuffmanTree(const HuffmanTree *ht){
  assert(ht != NULL);

  printf("   = Affichage de l'arbre a %d elements =\n\n", ht->size);
	if(ht->size == 0){
		printf(" - Arbre vide, rien a afficher\n");
		printf("-----------------------------------------\n");
	}
	else{
		show_HuffmanTreeNode(ht->root);
	}
}

void insert_HuffmanTree(HuffmanTree *ht, int key, int data, bool haveData){
  if(ht->root == NULL)
  	ht->root = init_HuffmanTreeNode(key, data, haveData);
  else
  	insert_HuffmanTreeNode(ht->root, key, data, haveData);

  ht->size++;
}

/* --------------------------------------------------------------- */

void freqChar_to_HuffmanTree(FreqChar *fc, HuffmanTree *ht){
  assert(fc != NULL);
  assert(ht != NULL);

  printf(" - sort_freqChar\n");
  sort_freqChar(fc); // sorting the freqChar for the priority queue

  Queue *q = init_Queue();

  // filling the queue with the freqChar data
  for(int i=0; i<fc->size; i++){
    HuffmanTreeNode* data = init_HuffmanTreeNode(fc->A_freq[i], fc->A_char[i], true);
    QueueNode* node = init_QueueNode(data);
    insert_Queue(q, node);
  }

  if(q->first != NULL){
    int ht_size = 1; // 1 for the first node
    while(q->first->next != NULL){
      int key = q->first->data->key + q->first->next->data->key; // the new nodes key is a sum of its children
      HuffmanTreeNode* link = init_HuffmanTreeNode(key, 0, false); // don't need a data

      if(q->first->data->key <= q->first->next->data->key){ // left <= right
        link->left = q->first->data;
        link->right = q->first->next->data;
      }
      else{ // left > right
        link->left = q->first->next->data;
        link->right = q->first->data;
      }
      link->right->bit = '1'; // changing the value to create the huffman codes later

      // removing the data inserted to the tree from the queue
      removeFirst_Queue(q);
      removeFirst_Queue(q);

      // adding the new node to the queue
      QueueNode* node = init_QueueNode(link);
      insert_Queue(q, node);

      ht_size += 2;
    }

    // updating the tree
    ht->size = ht_size;
    ht->root = q->first->data; // the final tree is the only node left in the queue

    printf(" - add_binaryValue_Huffman\n");
    add_binaryValue_Huffman(ht->root, ht->root->binary_value, true); // adding the codes to the nodes
  } // else : the tree is empty, nothing to do

  free_Queue(q);
}

void add_binaryValue_Huffman(HuffmanTreeNode *node, char* value, bool first){
  if(node != NULL){
    if(!first){ // first only for the root of the tree
      strncat(node->binary_value, &node->bit, 1);

      if(node->left != NULL)
        strcpy(node->left->binary_value, node->binary_value);
      if(node->right != NULL)
        strcpy(node->right->binary_value, node->binary_value);
    }

    add_binaryValue_Huffman(node->left, value, false);
    add_binaryValue_Huffman(node->right, value, false);
  }
}

void save_Huffman_coding(char* filename, HuffmanTreeNode *node){
  if(node != NULL){
    if(node->haveData){ // skip the nodes with no data
      FILE *fp = fopen(filename, "a");
      assert(fp != NULL);

      fprintf(fp, "%d;%c;%s\n", node->key, node->data, node->binary_value); // saving the codes in the file

      fclose(fp);
    }

    save_Huffman_coding(filename, node->left);
    save_Huffman_coding(filename, node->right);
  }
}
