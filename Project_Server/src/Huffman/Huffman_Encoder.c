/**
 * @file Huffman_Encoder.c
 * File containing the functions to use the Huffman encoder.
 */

#include "Huffman_Encoder.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "Huffman_FreqChar.h"
#include "Huffman_Tree.h"
#include "tools.h"

void codefile_to_binaryfile(char* codefile, char* filename){
  FILE *fp_code = fopen(codefile, "r");
  assert(codefile != NULL);

  FILE *fp_bin = fopen(filename, "wb");
  assert(fp_bin != NULL);

  int cpt=8; // start at the most significant bit
  byte_t byte=0;
  bool finished=false;
  char c;
  while((c=fgetc(fp_code)) != EOF){
    if(cpt > 0){
      if(c == '1') // filling the 1's in the byte
        byte = biwrite(byte, cpt);

      finished=false;
      cpt--;
    }
    else{ // need a new byte
      fwrite(&byte, 1, 1, fp_bin);
      cpt=8; // restart the cpt for the new byte
      byte=0;

      if(c == '1'){
        byte = biwrite(byte, cpt);
        finished=false;
      }
      else{ // if the code stop here, no need to put the last byte (=0)
        finished=true;
      }
      cpt--;
    }
  }
  if(!finished) // insert the last byte (which is not filled completely)
    fwrite(&byte, 1, 1, fp_bin);

  fclose(fp_bin);
  fclose(fp_code);
}

void text_to_binaryfile(char* filename, char* file_codes){
  FILE *fp = fopen(file_codes, "r");
  assert(fp != NULL);

  char codes[ASCII_SIZE][SIZE_B_VALUE];
  for(int i=0; i<ASCII_SIZE; i++) // init
    strcpy(codes[i], "");

  int x;
  char c;
  char s[SIZE_B_VALUE] = "";
  while(fscanf(fp, "%d;%c;%s\n", &x, &c, s) != EOF)
    strcpy(codes[(int)c], s);

  fclose(fp);

  FILE *input = fopen(filename, "r");
  assert(input != NULL);

  FILE *codefile = fopen("build/code.tmp", "w");
  assert(codefile != NULL);

  // creating the code
  char c2;
  while((c2=getc(input)) != EOF){
    if(c2 >= 0) // avoid negative overflow with unicode char
      fputs(codes[(int)c2], codefile);
  }
  fputs(codes[4], codefile); // add the EOT at the end of the code

  fclose(codefile);
  fclose(input);

  printf(" - codefile_to_binaryfile\n");
  codefile_to_binaryfile("build/code.tmp", "build/huffman_encoded.bin");
}

void Huffman_encoding(char* filename){
  FreqChar* fc = init_freqChar();
  printf(" file_to_freqChar\n");
  file_to_freqChar(filename, fc);

  HuffmanTree* ht = init_HuffmanTree();
  printf("\n freqChar_to_HuffmanTree\n");
  freqChar_to_HuffmanTree(fc, ht);

  FILE* fp = fopen("build/huffman.cod", "w"); // clear the file
  fclose(fp);

  printf("\n save_Huffman_coding\n");
  save_Huffman_coding("build/huffman.cod", ht->root);

  free_freqChar(fc);
  free_HuffmanTree(ht);

  printf("\n text_to_binaryfile\n");
  text_to_binaryfile(filename, "build/huffman.cod");
  printf("\n\n");
}
