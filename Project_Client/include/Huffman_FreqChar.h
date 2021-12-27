/**
 * @file Huffman_FreqChar.h
 * File containing the functions to use the FreqChar.
 */

#ifndef _HUFFMAN_FREQCHAR_
#define _HUFFMAN_FREQCHAR_

/**
 * @struct FreqChar
 * @param A_char an array of the characters
 * @param A_freq an array of the frequencies
 * @param size the size of the FreqChar
 */
typedef struct FreqChar{
  char* A_char; // store the char
  int* A_freq; // store the freq of the char at the same position
  int size; // < ASCII_SIZE
} FreqChar;

/**
 * @fn FreqChar* init_freqChar()
 * @brief initialize a FreqChar
 * @return the new FreqChar created
 */
FreqChar* init_freqChar();

/**
 * @fn void free_freqChar(FreqChar *fc)
 * @brief free the memory of a FreqChar
 * @param fc the FreqChar to free
 */
void free_freqChar(FreqChar *fc);

/**
 * @fn void add_to_freqChar(FreqChar *fc, char c, int freq)
 * @brief free the memory of a FreqChar
 * @param fc the FreqChar where we add
 * @param c the character to add in the FreqChar
 * @param freq the frenquecy to add in the FreqChar
 */
void add_to_freqChar(FreqChar *fc, char c, int freq);

/**
 * @fn void show_freqChar(FreqChar *fc)
 * @brief print a FreqChar
 * @param fc the FreqChar to print
 */
void show_freqChar(FreqChar *fc);

/**
 * @fn void file_to_freqChar(char* filename, FreqChar *freqChar)
 * @brief convert a file into a FreqChar
 * @param filename the name of the file to convert
 * @param freqChar the FreqChar converted
 */
void file_to_freqChar(char* filename, FreqChar *freqChar);

/**
 * @fn void sort_freqChar(FreqChar *fc)
 * @brief sort a FreqChar
 * ascending sorting of the frequencies of the FreqChar
 * @param fc the FreqChar to sort
 */
void sort_freqChar(FreqChar *fc);

#endif
