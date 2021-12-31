/**
 * @file LZW_Encoder.c
 * File containing the functions to use the LZW encoder.
 */

#include "LZW_Encoder.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "LZW_dictionary.h"
#include "tools.h"

void encoder_dictionary(char *filename){
  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);

  /* initialization of the dictionary with the ascii table */
  dico_t dico;
  init_dictionary(&dico);
  fill_asciiTable(&dico);

  /* 12bit LZW encoding algorithm */
  twelveBitArray codes; // array of the codes sent to the output file
  init_twelveBitArray(&codes, 1);

  char *string = (char *)calloc(1, BUFFER);
  strcpy(string, "");
  char* string_c = (char *)calloc(1, BUFFER);
  char c;

	while((c = fgetc(fp)) != EOF){
    // creating (string + c)
    strcpy(string_c, string);
    strncat(string_c, &c, 1);

    if(find_string(&dico, string_c)){
      strcpy(string, string_c);
    }
    else{
      for(int i=0; i < dico.nb_mots; i++){ // add the code of string
        if(strcmp(string, dico.mots[i]) == 0){
          insert_twelveBitArray(&codes, i);
          break;
        }
      }

      add_dictionary(&dico, string_c); // add the new word the the dictionary

      // string take c
      string[0] = c;
      string[1] = '\0';
    }
  }
  for(int i=0; i < dico.nb_mots; i++){ // add the code of string
    if(strcmp(string, dico.mots[i]) == 0){
      insert_twelveBitArray(&codes, i);
      break;
    }
  }

  /* creation of the output encoded binary file */
  char *output = "build/lzw_encoded.bin";

  byteArray outputArray;
  init_byteArray(&outputArray, 1);

  b12Array_to_byteArray(&codes, &outputArray);
  byteArray_to_binaryFile(&outputArray, output);

  /* free all the memory allocated */
  free(string);
  free(string_c);

  free_byteArray(&outputArray);
  free_twelveBitArray(&codes);
  free_dictionary(&dico);

  fclose(fp);
}
