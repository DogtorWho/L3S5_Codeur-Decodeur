#ifndef _LZW_DICTIONARY_
#define _LZW_DICTIONARY_

#include <stdbool.h>

#include "byteArray.h"
#include "LZW_twelveBitArray.h"

#define DICO_SIZE 3840

// defining the dictionary structure :
typedef struct {
	char *mots[DICO_SIZE];
	int nb_mots;
} dico_t;

/* initialize the dictionary */
void init_dictionary(dico_t *dico);

/* fill the dictionary and the 12bit array with the ASCII table */
void fill_asciiTable(dico_t *dico, twelveBitArray *a);

/* add a string to the dictionary */
void add_dictionary(dico_t *dico, char *string);

/* empty the words in the dictionary */
void empty_dictionary(dico_t *dico);

/* free the memory allocated by the dictionary */
void free_dictionary(dico_t *dico);

/* print the contents of the dictionary */
void print_dictionary(dico_t *dico, bool seeAsciiCodes);

/* search for a string in the dictionary */
bool find_string(dico_t *dico, char *string);

/* receive a .txt file with the message to encode
	return a binary file with the encoded message */
void encoder_dictionary(char *filename);

/* receive a binary file with the encoded message to decode
	return a .txt file with the decoded message */
void decoder_dictionary(char *filename);

#endif
