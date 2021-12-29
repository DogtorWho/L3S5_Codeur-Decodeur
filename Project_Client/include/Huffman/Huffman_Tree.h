/**
 * @file Huffman_Tree.h
 * File containing the functions to use the Huffman tree.
 */

#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "Huffman_FreqChar.h"

#include <stdbool.h>

/**
 * @def SIZE_B_VALUE
 * @brief Size of the string of the binary value
 */
#define SIZE_B_VALUE 32

/**
 * @struct HuffmanTreeNode
 * @param key the key of the node
 * @param data the data of the node
 * @param haveData says if the data should be treated
 * @param left pointer to the left child node
 * @param right pointer to the right child node
 */
typedef struct HuffmanTreeNode {
  int key; // freq
  char data; // char
  char bit; // 0 or 1
  char* binary_value; // ex : 100, 0, 1010
  bool haveData; // true if the binary_value can be decoded into a data (char)

  struct HuffmanTreeNode *left;
  struct HuffmanTreeNode *right;
} HuffmanTreeNode;

/**
 * @struct HuffmanTree
 * @param root the top node of the tree
 * @param size the size of the tree
 */
typedef struct HuffmanTree {
  struct HuffmanTreeNode *root;
  int size;
} HuffmanTree;

/**
 * @fn HuffmanTreeNode* init_HuffmanTreeNode(int key, int data, bool haveData)
 * @brief initialize a new huffman tree node
 * @param key the key of the new node
 * @param data the data of the new node
 * @param haveData says if the data should be treated in the new node
 * @return the new huffman tree node
 */
HuffmanTreeNode* init_HuffmanTreeNode(int key, int data, bool haveData);

/**
 * @fn void free_HuffmanTreeNode(HuffmanTreeNode *node)
 * @brief free the memory allocated of a huffman tree node
 * @param node the huffman tree node to free
 */
void free_HuffmanTreeNode(HuffmanTreeNode *node);

/**
 * @fn void show_HuffmanTreeNode(const HuffmanTreeNode *node)
 * @brief print a huffman tree node
 * @param node the huffman tree node to print
 */
void show_HuffmanTreeNode(const HuffmanTreeNode *node);

/**
 * @fn HuffmanTreeNode* insert_HuffmanTreeNode(HuffmanTreeNode *node, int key, int data, bool haveData)
 * @brief insert a new huffman tree node in the tree starting at the node
 * begin the search for a place for a new node in the tree recursively, starting at the node
 * @param node the node for the recursion
 * @param key the key for the new node created
 * @param data the data for the new node created
 * @param haveData the bool for the new node created
 * @return a child node of the node for the recursion
 */
HuffmanTreeNode* insert_HuffmanTreeNode(HuffmanTreeNode *node, int key, int data, bool haveData);

/* --------------------------------------------------------------- */

/**
 * @fn HuffmanTree* init_HuffmanTree()
 * @brief initialize a new huffman tree
 * @return the new tree created
 */
HuffmanTree* init_HuffmanTree();

/**
 * @fn void free_HuffmanTree(HuffmanTree *ht)
 * @brief free the memory allocated of the huffman tree recursively
 * @param ht the huffman tree to free
 */
void free_HuffmanTree(HuffmanTree *ht);

/**
 * @fn void show_HuffmanTree(const HuffmanTree *ht)
 * @brief print a huffman tree recursively
 * @param ht the huffman tree to print
 */
void show_HuffmanTree(const HuffmanTree *ht);

/**
 * @fn void insert_HuffmanTree(HuffmanTree *ht, int key, int data, bool haveData)
 * @brief insert a new node in the huffman tree recursively
 * @param ht the huffman tree to insert into
 * @param key the key of the new node inserted
 * @param data the data of the new node inserted
 * @param haveData the bool of the new node inserted
 */
void insert_HuffmanTree(HuffmanTree *ht, int key, int data, bool haveData);

/* --------------------------------------------------------------- */

/**
 * @fn void freqChar_to_HuffmanTree(FreqChar *fc, HuffmanTree *ht)
 * @brief convert a FreqChar to a huffman tree
 * @param fc the FreqChar to convert
 * @param ht the huffman tree converted
 */
void freqChar_to_HuffmanTree(FreqChar *fc, HuffmanTree *ht);

/**
 * @fn void add_binaryValue_Huffman(HuffmanTreeNode *node, char* value, bool first)
 * @brief add the binary values to all the node from the huffman tree node recursively
 * @param node the starting node of the recursion
 * @param value the binary value for the recursion
 * @param first says if it's the first node of the recursion
 */
void add_binaryValue_Huffman(HuffmanTreeNode *node, char* value, bool first);

/**
 * @fn void save_Huffman_coding(char* filename, HuffmanTreeNode *node)
 * @brief save all the codes of the tree in a file
 * @param filename the name of the file stocking the codes
 * @param node the starting node of the recursion
 */
void save_Huffman_coding(char* filename, HuffmanTreeNode *node);

#endif
