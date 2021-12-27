/**
 * @file Huffman_Decoder.h
 * File containing the functions to use the Huffman decoder.
 */

#include "Huffman_Decoder.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "byteArray.h"
#include "globals.h"
#include "tools.h"

void codeFile_to_freqChar(char* code_file, FreqChar *fc){
  FILE *fp = fopen(code_file, "r");
  assert(fp != NULL);

  // empty the freqChar
  free_freqChar(fc);
  fc = init_freqChar();

  int i;
  char c;
  char s[SIZE_B_VALUE] = "";
  while(fscanf(fp, "%d;%c;%s\n", &i, &c, s) != EOF)
    add_to_freqChar(fc, c, i);

  fclose(fp);
}

void codeFile_to_huffmanTree(char* code_file, HuffmanTree* ht){
  FreqChar* fc = init_freqChar();
  printf(" - codeFile_to_freqChar\n");
  codeFile_to_freqChar(code_file, fc);

  // empty the tree
  free_HuffmanTree(ht);
  ht = init_HuffmanTree();

  printf(" - freqChar_to_HuffmanTree\n");
  freqChar_to_HuffmanTree(fc, ht);

  free_freqChar(fc);
}

void binaryFile_to_text(char* binary_file, char* filename){
  FILE *output = fopen(filename, "w");
  assert(output != NULL);

  byteArray a;
  init_byteArray(&a, 1);
  printf(" - binaryFile_to_byteArray\n");
  binaryFile_to_byteArray(&a, binary_file);

  HuffmanTree* ht = init_HuffmanTree();
  printf(" - codeFile_to_huffmanTree\n");
  codeFile_to_huffmanTree("bin/huffman.cod", ht);

  HuffmanTreeNode* node = ht->root;
  for(int i=0; i < a.used; i++){
    for(int j=8; j > 0; j--){ // read bit by bit
      if(biread(a.array[i], j) == 1)
        node = node->right;
      else // == 0
        node = node->left;

      if(node->haveData){ // found a char
        if(node->data != EOT){ // continue reading the code
          fputc(node->data, output);
          //printf("%c", node->data);
          node = ht->root; // restart to the top of the tree
        }
        else{ // data = EOT, reach the end of the code
          break;
        }
      }
    }
  }

  free_HuffmanTree(ht);

  fclose(output);
}

void Huffman_decoding(char* binary_file){
  printf(" binaryFile_to_text\n");
  binaryFile_to_text(binary_file, "bin/huffman_decoded.txt");
}
