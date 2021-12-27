#ifndef _HUFFMAN_FREQCHAR_
#define _HUFFMAN_FREQCHAR_

// ASCII table size
#define ASCII_SIZE 256

typedef struct FreqChar{
  char* A_char; // store the char
  int* A_freq; // store the freq of the char in the same position
  int size; // < ASCII_SIZE
} FreqChar;

FreqChar* init_freqChar();
void free_freqChar(FreqChar *fc);
void add_to_freqChar(FreqChar *fc, char c, int freq);
void show_freqChar(FreqChar *fc);
void file_to_freqChar(char* filename, FreqChar *freqChar);
void sort_freqChar(FreqChar *fc);

#endif
