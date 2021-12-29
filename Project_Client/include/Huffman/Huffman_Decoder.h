/**
 * @file Huffman_Decoder.h
 * File containing the functions to use the Huffman decoder.
 */

#ifndef _HUFFMAN_DECODER_
#define _HUFFMAN_DECODER_

#include "Huffman_FreqChar.h"
#include "Huffman_Tree.h"

/**
 * @fn void codeFile_to_freqChar(char* code_file, FreqChar *fc)
 * @brief convert a code_file into a freqChar
 * @param code_file the name of the code file to convert
 * @param fc the freqChar converted
 */
void codeFile_to_freqChar(char* code_file, FreqChar *fc);

/**
 * @fn void codeFile_to_huffmanTree(char* code_file, HuffmanTree* ht)
 * @brief convert a code file into a huffman tree
 * @param code_file the name of the code file to convert
 * @param ht the huffman tree converted
 */
void codeFile_to_huffmanTree(char* code_file, HuffmanTree* ht);

/**
 * @fn void binaryFile_to_text(char* binary_file, char* filename)
 * @brief convert a binary file into a text file
 * @param binary_file the name of the binary file to convert
 * @param filename the name of the text file converted
 */
void binaryFile_to_text(char* binary_file, char* filename);

/**
 * @fn void Huffman_decoding(char* binary_file)
 * @brief Decodes a file
 * use the Huffman algorithm to decode an encoded file
 * @param binary_file name of the encoded binary file
 * @warning Don't decode unicode characters (then get removed in the output file)
 */
void Huffman_decoding(char* binary_file);

#endif
