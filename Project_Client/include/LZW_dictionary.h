/**
 * @file LZW_dictionary.h
 * File containing the functions to use the LZW dictionary.
 */

#ifndef _LZW_DICTIONARY_
#define _LZW_DICTIONARY_

#include <stdbool.h>

#include "byteArray.h"
#include "LZW_twelveBitArray.h"

/**
 * @def DICO_SIZE
 * @brief Size of the dictionary
 */
#define DICO_SIZE 3840

/**
 * @struct dico_t
 * @param mots array of words
 * @param nb_mots number of words in the dictionary
 */
typedef struct {
	char *mots[DICO_SIZE];
	int nb_mots;
} dico_t;

/**
 * @fn void init_dictionary(dico_t *dico)
 * @brief initialize a dictionary
 * @param dico the dictionary to initialize
 */
void init_dictionary(dico_t *dico);

/**
 * @fn void fill_asciiTable(dico_t *dico, twelveBitArray *a)
 * @brief fill a dictionary and a 12-bit array with the ASCII characters
 * fill the first 256 words with all the ASCII characters, same with the array
 * @param dico the dictionary to fill
 * @param a 12-bit array to fill
 */
void fill_asciiTable(dico_t *dico, twelveBitArray *a);

/**
 * @fn void add_dictionary(dico_t *dico, char *string)
 * @brief add a word to the dictionary
 * @param dico the dictionary to fill
 * @param string the word to put in the dictionary
 */
void add_dictionary(dico_t *dico, char *string);

/**
 * @fn void empty_dictionary(dico_t *dico)
 * @brief empty the words in the dictionary
 * empty all the dictionary except for the ASCII characters (first 256 words)
 * @param dico the dictionary to empty
 */
void empty_dictionary(dico_t *dico);

/**
 * @fn void free_dictionary(dico_t *dico)
 * @brief free the memory allocated in the dictionary
 * @param dico the dictionary to free
 */
void free_dictionary(dico_t *dico);

/**
 * @fn void print_dictionary(dico_t *dico, bool seeAsciiCodes)
 * @brief print all the words in the dictionary
 * @param dico the dictionary to print
 * @param seeAsciiCodes see the first 256 words
 */
void print_dictionary(dico_t *dico, bool seeAsciiCodes);

/**
 * @fn bool find_string(dico_t *dico, char *string)
 * @brief search for a word in the dictionary
 * @param dico the dictionary to search in
 * @param string the word to search for
 * @return bool
 * @retval true if the word was found in the dictionary
 * @retval false if the word was not found in the dictionary
 */
bool find_string(dico_t *dico, char *string);

#endif
