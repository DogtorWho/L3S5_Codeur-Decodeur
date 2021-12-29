/**
 * @file LZW_Encoder.h
 * File containing the functions to use the LZW encoder.
 */

#ifndef _LZW_ENCODER_
#define _LZW_ENCODER_

/**
 * @fn void encoder_dictionary(char *filename)
 * @brief Encodes a file
 * use the LZW algorithm to encode a text file
 * @param filename name of the text file
 * @warning Don't work with unicode characters
 */
void encoder_dictionary(char *filename);

#endif
