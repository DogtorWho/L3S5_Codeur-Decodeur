#include "Huffman_FreqChar.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "globals.h"

FreqChar* init_freqChar(){
  FreqChar* fc = malloc(sizeof(FreqChar));
  assert(fc != NULL);

  fc->A_char = malloc(ASCII_SIZE);
  fc->A_freq = malloc(sizeof(int)*ASCII_SIZE);

  fc->size = 0; // max ASCII_SIZE

  return fc;
}

void free_freqChar(FreqChar *fc){
  assert(fc != NULL);

  free(fc->A_char);
  free(fc->A_freq);
  free(fc);
}

void add_to_freqChar(FreqChar *fc, char c, int freq){
  assert(fc != NULL);

  fc->A_char[fc->size] = c;
  fc->A_freq[fc->size] = freq;
  fc->size++;
}

void show_freqChar(FreqChar *fc){
  assert(fc != NULL);

  printf("   = Affichage de freqChar a %d elements =\n\n", fc->size);
	if(fc->size == 0){
		printf(" - freqChar vide, rien a afficher\n");
		printf("-----------------------------------------\n");
	}
	else{
    printf(" [Char] | [Freq] \n");
    for (int i = 0; i < fc->size; i++) {
      switch(fc->A_char[i]){
        case '\'': printf("   [\']  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\"': printf("   [\"]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\?': printf("  [\\?]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\\': printf("   [\\]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\a': printf("  [\\a]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\b': printf("  [\\b]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\f': printf("  [\\f]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\n': printf("  [\\n]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\r': printf("  [\\r]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\t': printf("  [\\t]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\v': printf("  [\\v]  |  [%d] \n", fc->A_freq[i]);
          break;
        case '\0': printf("  [\\0]  |  [%d] \n", fc->A_freq[i]);
          break;
        default: printf("   [%c]  |  [%d] \n",fc->A_char[i], fc->A_freq[i]);
          break;
      }
    }
    printf("\n");
  }
}

void file_to_freqChar(char* filename, FreqChar *fc){
  assert(fc != NULL);

  FILE *fp = fopen(filename, "r");
  assert(fp != NULL);

  int tmpFreq[ASCII_SIZE];
  for (int i = 0; i < ASCII_SIZE; i++)
    tmpFreq[i] = 0;

  char c;
  while((c = fgetc(fp)) != EOF){
    if(c >= 0) // avoid negative overflow with unicode char
      tmpFreq[(int)c]++;
  }
  // adding a EOT which code will stop the decoder later
  tmpFreq[EOT]++;

  for(int i=0; i < ASCII_SIZE; i++){
    if(tmpFreq[i] > 0)
      add_to_freqChar(fc, i, tmpFreq[i]);
  }

  fclose(fp);
}

static void swapInt(int* a, int* b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static void swapChar(char* a, char* b){
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort_freqChar(FreqChar *fc){
  int min_i;

  for(int i = 0; i < fc->size - 1; i++){
    min_i = i;
    for (int j = i + 1; j < fc->size; j++){
      if (fc->A_freq[j] < fc->A_freq[min_i]){
        min_i = j;
      }
      else if(fc->A_freq[j] == fc->A_freq[min_i]){
        if (fc->A_char[j] < fc->A_char[min_i])
          min_i = j;
      }
    }

    swapInt(&fc->A_freq[min_i], &fc->A_freq[i]);
    swapChar(&fc->A_char[min_i], &fc->A_char[i]);
  }
}
