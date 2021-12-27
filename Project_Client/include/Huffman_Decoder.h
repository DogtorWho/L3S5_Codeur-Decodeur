#ifndef _HUFFMAN_DECODER_
#define _HUFFMAN_DECODER_

#include "Huffman_FreqChar.h"
#include "Huffman_Tree.h"

void codeFile_to_freqChar(char* code_file, FreqChar *fc);
void codeFile_to_huffmanTree(char* code_file, HuffmanTree* ht);
void binaryFile_to_text(char* binary_file, char* filename);
void Huffman_decoding(char* binary_file);

#endif
