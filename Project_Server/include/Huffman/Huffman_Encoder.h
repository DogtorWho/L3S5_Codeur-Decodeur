/**
 * @file Huffman_Encoder.h
 * File containing the functions to use the Huffman encoder.
 */

#ifndef _HUFFMAN_ENCODER_
#define _HUFFMAN_ENCODER_

/**
 * @fn void codefile_to_binaryfile(char* codefile, char* filename)
 * @brief convert a codefile into a binary file
 * @param codefile the name of the code file to convert
 * @param filename the name of the binary file converted
 */
void codefile_to_binaryfile(char* codefile, char* filename);

/**
 * @fn void text_to_binaryfile(char* filename, char* file_codes)
 * @brief convert a text file into a binary file
 * @param filename the name of the text file to convert
 * @param file_codes the name of the binary file converted
 */
void text_to_binaryfile(char* filename, char* file_codes);

/**
 * @fn void Huffman_encoding(char* filename)
 * @brief Encodes a file
 * use the Huffman algorithm to encode an text file
 * @param filename name of the text binary file to encode
 * @warning Don't encode unicode characters (then get removed in the codes)
 */
void Huffman_encoding(char* filename);

#endif
