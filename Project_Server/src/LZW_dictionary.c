/**
 * @file LZW_dictionary.c
 * File containing the functions to use the LZW dictionary.
 */

#include "LZW_dictionary.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "tools.h"
#include "globals.h"

void init_dictionary(dico_t *dico){
  assert(dico != NULL);

  dico->nb_mots = 0;
}

void fill_asciiTable(dico_t *dico, twelveBitArray *a){
  assert(a != NULL);
  assert(a->array != NULL);

  free_twelveBitArray(a);
	init_twelveBitArray(a, ASCII_SIZE);

  free_dictionary(dico);
  dico->nb_mots = ASCII_SIZE; // 0-255 ascii table

  for (int i=0; i < ASCII_SIZE; i++){
    char c = i;
    char *s = (char *)malloc(2);
    s[0] = c;
    s[1] = '\0';
    dico->mots[i] = s;

    insert_twelveBitArray(a, i);
  }
}

void add_dictionary(dico_t *dico, char *string){
  assert(dico != NULL);

  dico->mots[dico->nb_mots] = string;
  dico->nb_mots++;
}


void empty_dictionary(dico_t *dico){
  assert(dico != NULL);

  for(int i=ASCII_SIZE; i < dico->nb_mots; i++)
    free(dico->mots[i]);

  dico->nb_mots = ASCII_SIZE;
}

void free_dictionary(dico_t *dico){
  assert(dico != NULL);

  for(int i=0; i < dico->nb_mots; i++) {
    free(dico->mots[i]);
  }
}

void print_dictionary(dico_t *dico, bool seeAsciiCodes){
  assert(dico != NULL);

  printf("Dictionary words : (%d)\n", dico->nb_mots);

  int i = 0;
  if(!seeAsciiCodes){
    i = ASCII_SIZE;
    printf(" Skipping the ascii table\n");
  }


  for (int j = i; j < dico->nb_mots; j++)
    printf("%d : %s\n", j, dico->mots[j]);
  printf("\n");
}

bool find_string(dico_t *dico, char *string){
  assert(dico != NULL);

  for(int i=0; i < dico->nb_mots; i++){
    if(strcmp(string, dico->mots[i]) == 0){
      return true;
    }
  }
  return false;
}
