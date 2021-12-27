/**
 * @file tools.h
 * File containing functions which can help in all sort of other functions.
 */

#ifndef _TOOLS_
#define _TOOLS_

#include <stdio.h>

#include "globals.h"
#include "LZW_byteArray.h"
#include "LZW_twelveBitArray.h"

/**
 * @fn unsigned long fsize(FILE *fd)
 * @brief get the size of a file
 * return the size (number of char) of the file pointed by fd
 * @param fd the file descriptor
 * @return the size of the file
 */
unsigned long fsize(FILE *fd);

/**
 * @fn void text_to_byteArray(byteArray *byte_array, char* filename)
 * @brief convert a text file into a byteArray
 * transform each character of a text file into a byte_t and form an array of all these bytes
 * @param byte_array the array of bytes which will stock the bytes converted
 * @param filename the name of the file to convert
 */
void text_to_byteArray(byteArray *byte_array, char* filename);

/**
 * @fn void text_to_b12Array(twelveBitArray *b12_array, char* filename)
 * @brief convert a text file into a twelveBitArray
 * transform each character of a text file into a twelveBit_t and form an array of all these 12-bit
 * @param b12_array the array of 12-bit which will stock the 12-bit converted
 * @param filename the name of the file to convert
 */
void text_to_b12Array(twelveBitArray *b12_array, char* filename);

/**
 * @fn void twoInt_to_threeBytes(twelveBit_t i1, twelveBit_t i2, byte_t *o1, byte_t *o2, byte_t *o3)
 * @brief convert two 12-bit into three bytes
 * @details
 * take two int (i1, i2) representing two binary numbers with 12 digits
 * and transform them into three bytes (o1, o2, o3)
 *       i1               i2
 * 0000 0000 0000 | 0000 0000 0000
 *     o1   |     o2    |    o3
 * @param i1 the first 12-bit to convert
 * @param i2 the second 12-bit to convert
 * @param o1 the first byte converted
 * @param o2 the second byte converted
 * @param o3 the third byte converted
 */
void twoInt_to_threeBytes(twelveBit_t i1, twelveBit_t i2, byte_t *o1, byte_t *o2, byte_t *o3);

/**
 * @fn void threeBytes_to_twoInt(byte_t o1, byte_t o2, byte_t o3, twelveBit_t *i1, twelveBit_t *i2)
 * @brief convert three bytes into two 12-bit
 * @details
 * take three bytes (o1, o2, o3)
 * and transform them into two int (i1, i2) representing two binary numbers with 12 digits
 * 	   o1   |     o2    |    o3
 * 0000 0000 0000 | 0000 0000 0000
 *       i1               i2
 * @param o1 the first byte to convert
 * @param o2 the second byte to convert
 * @param o3 the third byte to convert
 * @param i1 the first 12-bit converted
 * @param i2 the second 12-bit converted
 */
void threeBytes_to_twoInt(byte_t o1, byte_t o2, byte_t o3, twelveBit_t *i1, twelveBit_t *i2);

/**
 * @fn void byteArray_to_b12Array(byteArray *byte_array, twelveBitArray *b12_array)
 * @brief convert a byteArray into a twelveBitArray
 * take an array of bytes and transform them into an array of twelveBit_t
 * @param byte_array the array of bytes to convert
 * @param b12_array the array of 12-bit converted
 */
void byteArray_to_b12Array(byteArray *byte_array, twelveBitArray *b12_array);

/**
 * @fn void b12Array_to_byteArray(twelveBitArray *b12_array, byteArray *byte_array)
 * @brief convert a twelveBitArray into a byteArray
 * take an array of twelveBit_t and transform them into an array of bytes
 * @param b12_array the array of 12-bit to convert
 * @param byte_array the array of bytes converted
 */
void b12Array_to_byteArray(twelveBitArray *b12_array, byteArray *byte_array);

/**
 * @fn void b12_printf(const twelveBit_t Oc, const char *ident, const int mode)
 * @brief print a 12-bit
 * @param Oc the twelveBit_t to print
 * @param ident name of the twelveBit_t to indentify it
 * @param mode if 1, print the int value of the 12-bit
 */
void b12_printf(const twelveBit_t Oc, const char *ident, const int mode);

/**
 * @fn void b12Array_print(twelveBit_t b12_array[], int size_b12Array, const int mode)
 * @brief print a 12-bit array
 * @param b12_array the array to print
 * @param size_b12Array the size of the array
 * @param mode if 1, print the int value of the 12-bit
 */
void b12Array_print(twelveBit_t b12_array[], int size_b12Array, const int mode);

/**
 * @fn void byArray_print(byte_t byte_array[], int size_byArray, const int mode)
 * @brief print an array of bytes
 * @param byte_array the byteArray to print
 * @param size_byArray the size of the array
 * @param mode if 1, print the int value of the bytes
 */
void byArray_print(byte_t byte_array[], int size_byArray, const int mode);

/* -------------------------------------------------------------------------- */

/**
 * @fn void byprintf(const byte_t, const char *ident, const int mode)
 * @brief print a byte
 * @param byte_t the byte to print
 * @param ident name of the byte to indentify it
 * @param mode if 1, print the int value of the byte
 */
void byprintf(const byte_t, const char *ident, const int mode);

/**
 * @fn byte_t byread()
 * @brief read a byte (between 0 and 255)
 * @return the byte read
 */
byte_t byread();

/**
 * @fn int biread(const byte_t, const int)
 * @brief read a bit of byte_t (between 1 and 8)
 * @param byte_t the byte where to read a bit
 * @param int the place of the bit in the byte (1-8)
 * @return the bit (0 or 1)
 */
int biread(const byte_t, const int);

/**
 * @fn byte_t biwrite(const byte_t, const int)
 * @brief write a bit in a byte (between 1 and 8)
 * @param byte_t the byte to modify
 * @param int the place of the bit in the byte (1-8)
 * @return the modified byte
 */
byte_t biwrite(const byte_t, const int);

/**
 * @fn byte_t infQread(byte_t O)
 * @brief read the first 4 bits of a byte
 * @param O the byte to read
 * @return the modified byte
 */
byte_t infQread(byte_t O);

/**
 * @fn byte_t supQread(byte_t O)
 * @brief read the last 4 bits of a byte
 * @param O the byte to read
 * @return the modified byte
 */
byte_t supQread(byte_t O);

/**
 * @fn byte_t infQwrite(byte_t O, byte_t qi)
 * @brief write the first 4 bits of a byte
 * bits modified xxxx ->XXXX<-
 * @param O the byte to write
 * @param qi the 4 bits to write
 * @return the modified byte
 */
byte_t infQwrite(byte_t O, byte_t qi);

/**
 * @fn byte_t supQwrite(byte_t O, byte_t qi)
 * @brief write the last 4 bits of a byte
 * bits modified ->XXXX<- xxxx
 * @param O the byte to write
 * @param qi the 4 bits to write
 * @return the modified byte
 */
byte_t supQwrite(byte_t O, byte_t qs);

#endif
