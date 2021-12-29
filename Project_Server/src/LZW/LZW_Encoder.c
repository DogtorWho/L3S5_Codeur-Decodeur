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
  FILE *fd = fopen(filename, "r");
  assert(fd != NULL);

  /* initialization of the dictionary and 12bit array with the ascii table */
  dico_t dico;
  twelveBitArray b12Array;
  init_dictionary(&dico);
  init_twelveBitArray(&b12Array, 1);
  fill_asciiTable(&dico, &b12Array);

  /* 12bit LZW encoding algorithm */
  char *S = (char *)calloc(1, BUFSIZ);
  twelveBit_t code = ASCII_SIZE; // starting the coding after the last ascii caracter

  twelveBitArray codes; // array of the codes sent to the output file
  init_twelveBitArray(&codes, 1);

  char *m = (char *)calloc(1, 2); // size of a char
	while((*m = fgetc(fd)) != EOF){
		char *s_m = (char *)calloc(1, strlen(S)+3); // 1 for \0 and 1 for m
		strcpy(s_m, S);
		strcat(s_m, m);

		if(find_string(&dico, s_m)){
			strcpy(S, s_m);
			free(s_m);
		}
		else{
      if(strlen(S) == 1) // the string is a char, so the code is between 0 and 255
        insert_twelveBitArray(&codes, S[0]);
      else{
        // we search for the code of S in the dictionary
        for(int i=0; i < dico.nb_mots; i++){
          if(strcmp(S, dico.mots[i]) == 0){
            insert_twelveBitArray(&codes, i);
            break;
          }
        }
      }

      if(dico.nb_mots == DICO_SIZE) // clear the dictionary if its full
        empty_dictionary(&dico);
      //printf("size : %d - code : %d - add : %s\n", dico.nb_mots, code, s_m);
      add_dictionary(&dico, s_m);
			insert_twelveBitArray(&b12Array, code);
			code++;

      strcpy(S, m);
		}
	}
  if(strlen(S) == 1) // the string is a char, so the code is between 0 and 255
    insert_twelveBitArray(&codes, S[0]);
  else{
    // we search for the code of S in the dictionary
    for(int i=0; i < dico.nb_mots; i++){
      if(strcmp(S, dico.mots[i]) == 0){
        insert_twelveBitArray(&codes, i);
        break;
      }
    }
  }

  /* creation of the output encoded binary file */
  char *output = "build/lzw_encoded.bin";

  byteArray outputArray;
  init_byteArray(&outputArray, 1);

  b12Array_to_byteArray(&codes, &outputArray);
  byteArray_to_binaryFile(&outputArray, output);

  /* free all the memory allocated */
  free(m);
	free(S);
  free_byteArray(&outputArray);
  free_twelveBitArray(&codes);
  free_twelveBitArray(&b12Array);
  free_dictionary(&dico);
  fclose(fd);
}
