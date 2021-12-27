#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "Huffman_FreqChar.h"

#include <stdbool.h>

#define SIZE_B_VALUE 32

typedef struct HuffmanTreeNode {
  int key; // freq
  char data; // char
  char bit; // 0 or 1
  char* binary_value; // ex : 100, 0, 1010
  bool haveData; // true if the binary_value can be decoded into a data (char)

  struct HuffmanTreeNode *left;
  struct HuffmanTreeNode *right;
} HuffmanTreeNode;

typedef struct HuffmanTree {
  struct HuffmanTreeNode *root;
  int size;
} HuffmanTree;

HuffmanTreeNode* init_HuffmanTreeNode(int key, int data, bool haveData);
void free_HuffmanTreeNode(HuffmanTreeNode *node);
void show_HuffmanTreeNode(const HuffmanTreeNode *node);
HuffmanTreeNode* insert_HuffmanTreeNode(HuffmanTreeNode *node, int key, int data, bool haveData);
/* --------------------------------------------------------------- */
HuffmanTree* init_HuffmanTree();
void free_HuffmanTree(HuffmanTree *ht);
void show_HuffmanTree(const HuffmanTree *ht);
void insert_HuffmanTree(HuffmanTree *ht, int key, int data, bool haveData);
/* --------------------------------------------------------------- */
void freqChar_to_HuffmanTree(FreqChar *fc, HuffmanTree *ht);
void add_binaryValue_Huffman(HuffmanTreeNode *node, char* value, bool first);
void save_Huffman_coding(char* filename, HuffmanTreeNode *node);

#endif
