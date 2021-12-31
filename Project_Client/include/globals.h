/**
 * @file globals.h
 * File containing global defined constants.
 */

#ifndef _GLOBALS_
#define _GLOBALS_

/**
 * @def ASCII_SIZE
 * @brief Size of ASCII char (0-255)
 */
#define ASCII_SIZE 256

/**
 * @def BUFFER
 * @brief Size of the buffer for the words in the dictionary
 */
#define BUFFER 512

/**
 * @typedef byte_t
 * @brief Definition of byte type (8 bit)
 */
typedef unsigned char byte_t;

/**
 * @typedef twelveBit_t
 * @brief Definition of 12 bit type
 */
typedef unsigned int twelveBit_t;

/**
 * @def EOT
 * @brief Char representing the end of the encoded message
 */
#define EOT 4

#endif
