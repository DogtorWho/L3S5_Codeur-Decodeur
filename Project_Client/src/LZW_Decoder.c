#include "LZW_Decoder.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "LZW_dictionary.h"
#include "tools.h"

void decoder_dictionary(char *filename){
  // binary file containing the codes to decode
  FILE *fd = fopen(filename, "rb");
  assert(fd != NULL);

  // output decoded text file
  FILE *fdp = fopen("bin/lzw_decoded.txt", "w");
  assert(fdp != NULL);

  // initialization of the dictionary and 12bit array with the ascii table
  dico_t dico;
  twelveBitArray b12Array;
  init_dictionary(&dico);
  init_twelveBitArray(&b12Array, 1);
  fill_asciiTable(&dico, &b12Array);

  // transform the input binary file into a 12 bit array containing the codes
  twelveBitArray codes;
  byteArray inputArray;
  init_twelveBitArray(&codes, 1);
  init_byteArray(&inputArray, 1);
  binaryFile_to_byteArray(&inputArray, filename);
  byteArray_to_b12Array(&inputArray, &codes);

  char *S = (char *)calloc(1, BUFSIZ);
  int code = ASCII_SIZE; // starting the coding after the last ascii caracter

  int i = 0;
  char *m = (char *)calloc(1, BUFSIZ);
  while(i < codes.used){
    twelveBit_t c = codes.array[i];

    if(c != 0){ // to purge the potential extra bytes at the end of the conversion between 8bit and 12bit
      if(c < ASCII_SIZE){ // c in the initial dictionary
        strcpy(m, dico.mots[c]);
        fputc(m[0], fdp);

        char *s_m = (char *)calloc(1, strlen(S)+strlen(m)+1);
  			strcpy(s_m, S);
  			strcat(s_m, m);

  			if(find_string(&dico, s_m)){
  				strcpy(S, s_m);
  				free(s_m);
  			}
  			else{
          if(dico.nb_mots == DICO_SIZE) // clear the dictionary if its full
            empty_dictionary(&dico);
          //printf("size : %d - code : %d - add : %s\n", dico.nb_mots, code, s_m);
          add_dictionary(&dico, s_m);
  				insert_twelveBitArray(&b12Array, code);
  				code++;

          strcpy(S, m);
  			}
      }
      else{ // c > 255, m contains more than one char
        // check if the code can already be found in the dictionary (ex : aaa)
        if(c >= dico.nb_mots){ // code can't be found, we create it
          char *tmpS = (char *)calloc(1, sizeof(S)+1); // size of a char
          strcpy(tmpS, S);
          strcat(tmpS, S);
          strcpy(S, "");

          if(dico.nb_mots == DICO_SIZE) // clear the dictionary if its full
            empty_dictionary(&dico);
          //printf("size : %d - code : %d - add : %s\n", dico.nb_mots, code, tmpS);
          add_dictionary(&dico, tmpS);
          insert_twelveBitArray(&b12Array, code);
          code++;
        }

        strcpy(m, dico.mots[c]);

        char *cm = (char *)calloc(1, 2); // size of a char
        for (int i=0; i < strlen(m); i++){
          cm[0] = m[i];
          fputc(cm[0], fdp);

          char *s_cm = (char *)calloc(1, strlen(S)+2); // 1 for \0 and 1 for cm
    			strcpy(s_cm, S);
    			strcat(s_cm, cm);

          if(find_string(&dico, s_cm)){
    				strcpy(S, s_cm);
    				free(s_cm);
    			}
    			else{
            if(dico.nb_mots == DICO_SIZE) // clear the dictionary if its full
              empty_dictionary(&dico);
            //printf("size : %d - code : %d - add : %s\n", dico.nb_mots, code, s_cm);
            add_dictionary(&dico, s_cm);
    				insert_twelveBitArray(&b12Array, code);
    				code++;

            strcpy(S, cm);
    			}
        }
        free(cm);
      }
    }
    i++;
  }

  // free all the memory allocated
  free(m);
	free(S);

  free_byteArray(&inputArray);
  free_twelveBitArray(&codes);
  free_twelveBitArray(&b12Array);
  free_dictionary(&dico);

  fclose(fdp);
  fclose(fd);
}
