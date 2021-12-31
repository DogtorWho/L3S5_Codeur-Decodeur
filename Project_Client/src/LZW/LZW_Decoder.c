/**
 * @file LZW_Decoder.h
 * File containing the functions to use the LZW decoder.
 */

#include "LZW_Decoder.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "LZW_dictionary.h"
#include "tools.h"

void decoder_dictionary(char *filename){
  FILE *fd = fopen(filename, "rb"); // binary file containing the codes to decode
  assert(fd != NULL);

  FILE *fdp = fopen("build/lzw_decoded.txt", "w"); // output decoded text file
  assert(fdp != NULL);

  /* initialization of the dictionary with the ascii table */
  dico_t dico;
  init_dictionary(&dico);
  fill_asciiTable(&dico);

  /* 12bit LZW decoding algorithm */
  twelveBitArray codes;
  byteArray inputArray;
  init_twelveBitArray(&codes, 1);
  init_byteArray(&inputArray, 1);
  binaryFile_to_byteArray(&inputArray, filename);
  byteArray_to_b12Array(&inputArray, &codes);

  char* string = (char*)calloc(1, BUFFER);
  char* old = (char*)calloc(1, BUFFER);
  char* add = (char*)calloc(1, BUFFER);
  char c;

  twelveBit_t new_code = 0;
  twelveBit_t old_code = codes.array[0];

  strcpy(old, dico.mots[old_code]);
  fputs(old, fdp); // output first code

  for(int i = 1; i < codes.used; i++){ // read every codes
    new_code = codes.array[i]; // get the code to convert

    /* handling exception */
    if(new_code >= dico.nb_mots){
      strcpy(string, dico.mots[old_code]);
      strncat(string, &c, 1);
    }
    else{
      strcpy(string, dico.mots[new_code]);
    }

    fputs(string, fdp); // recreating the message
    c = string[0]; // c take the first char of the string

    strcpy(add, dico.mots[old_code]);
    strncat(add, &c, 1);
    add_dictionary(&dico, add); // add the new word to the dictionary

    old_code = new_code;
  }

  /* free all the memory allocated */
	free(string);
  free(old);
  free(add);

  free_byteArray(&inputArray);
  free_twelveBitArray(&codes);
  free_dictionary(&dico);

  fclose(fdp);
  fclose(fd);
}
