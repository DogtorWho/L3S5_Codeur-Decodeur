/**
 * @file LZW_Decoder.h
 * File containing the functions to use the LZW decoder.
 */

#ifndef _LZW_DECODER_
#define _LZW_DECODER_

/**
 * @fn void decoder_dictionary(char *filename)
 * @brief Decodes a file
 * use the LZW algorithm to decode an encoded file
 * @param filename name of the encoded file
 * @warning Don't work with unicode characters
 */
void decoder_dictionary(char *filename);

#endif
