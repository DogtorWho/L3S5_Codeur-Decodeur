/**
 * @file tools.c
 * File containing functions which can help in all sort of other functions.
 */

#include "tools.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

unsigned long fsize(FILE *fd){
    unsigned long prev = ftell(fd);
    fseek(fd, 0L, SEEK_END);
    unsigned long size = ftell(fd);
    fseek(fd, prev, SEEK_SET); //go back to where we were
    return size;
}

void text_to_byteArray(byteArray *byte_array, char* filename){
	FILE *fd = fopen(filename, "r");
	assert(fd != NULL);

	free_byteArray(byte_array);
	init_byteArray(byte_array, 1);

	char c;
	while((c = fgetc(fd)) != EOF){
		if(c != '\n')
			insert_byteArray(byte_array, c);
	}

	switch (byte_array->used % 3) {
		case 1 :
			insert_byteArray(byte_array, 0);
			insert_byteArray(byte_array, 0);
			break;
		case 2 :
			insert_byteArray(byte_array, 0);
			break;
		default : break;
	}

  fclose(fd);
}

void text_to_b12Array(twelveBitArray *b12_array, char* filename){
	FILE *fd = fopen(filename, "r");
	assert(fd != NULL);

	free_twelveBitArray(b12_array);
	init_twelveBitArray(b12_array, 1);

	char c;
	while((c = fgetc(fd)) != EOF){
		insert_twelveBitArray(b12_array, c);
	}

	if(b12_array->used % 2 != 0)
		insert_twelveBitArray(b12_array, 0);

  fclose(fd);
}

void twoInt_to_threeBytes(twelveBit_t i1, twelveBit_t i2, byte_t *o1, byte_t *o2, byte_t *o3){
	assert((i1 >= 0) && (i1 < 4096)); // 2^12 = 4096
	assert((i2 >= 0) && (i2 < 4096));

	*o1 = 0; *o2 = 0; *o3 = 0;

	// filling o1 :
	for(int i = 4; i < 12; i++){
		twelveBit_t bit = (1 << i);
    if(i1 & bit)
      *o1 += pow(2, i-4);
	}

	// filling o2 :
	for(int i = 8; i < 12; i++){
		twelveBit_t bit = (1 << i);
    if(i2 & bit)
      *o2 += pow(2, i-8);
	}
	for(int i = 0; i < 4; i++){
		twelveBit_t bit = (1 << i);
    if(i1 & bit)
      *o2 += pow(2, i+4);
	}

	// filling o3 :
	for(int i = 0; i < 8; i++){
		twelveBit_t bit = (1 << i);
    if(i2 & bit)
      *o3 += pow(2, i);
	}
}

void threeBytes_to_twoInt(byte_t o1, byte_t o2, byte_t o3, twelveBit_t *i1, twelveBit_t *i2){
	assert((o1 >= 0) && (o1 < 256)); // 2^8 = 256
	assert((o2 >= 0) && (o2 < 256));
	assert((o3 >= 0) && (o3 < 256));

	*i1 = 0; *i2 = 0;

	// filling i1 :
	for(int i = 0; i < 4; i++){
		byte_t bit = (1 << (i+4));
    if(o2 & bit)
      *i1 += pow(2, i);
	}
	for(int i = 4; i < 12; i++){
		byte_t bit = (1 << (i-4));
    if(o1 & bit)
      *i1 += pow(2, i);
	}

	// filling i2 :
	for(int i = 0; i < 8; i++){
		byte_t bit = (1 << i);
    if(o3 & bit)
      *i2 += pow(2, i);
	}
	for(int i = 8; i < 12; i++){
		byte_t bit = (1 << (i-8));
    if(o2 & bit)
      *i2 += pow(2, i);
	}
}

void byteArray_to_b12Array(byteArray *byte_array, twelveBitArray *b12_array){
	assert(byte_array != NULL);

  switch (byte_array->used % 3) {
		case 1 :
			insert_byteArray(byte_array, 0);
			insert_byteArray(byte_array, 0);
			break;
		case 2 :
			insert_byteArray(byte_array, 0);
			break;
		default : break;
	}

	free_twelveBitArray(b12_array);
	init_twelveBitArray(b12_array, (byte_array->used*2)/3);

	int j = 0;
	for(int i = 0; i < byte_array->used; i+=3){
		twelveBit_t i1, i2;

		threeBytes_to_twoInt(byte_array->array[i], byte_array->array[i+1], byte_array->array[i+2], &i1, &i2);

		insert_twelveBitArray(b12_array, i1);
		insert_twelveBitArray(b12_array, i2);

		j+=2;
	}
}

void b12Array_to_byteArray(twelveBitArray *b12_array, byteArray *byte_array){
	assert(b12_array != NULL);

  if(b12_array->used % 2 != 0)
		insert_twelveBitArray(b12_array, 0);

	free_byteArray(byte_array);
	init_byteArray(byte_array, (b12_array->used*3)/2);

	int j = 0;
	for(int i = 0; i < b12_array->used; i+=2){
		byte_t o1, o2, o3;

		twoInt_to_threeBytes(b12_array->array[i], b12_array->array[i+1], &o1, &o2, &o3);

		insert_byteArray(byte_array, o1);
		insert_byteArray(byte_array, o2);
		insert_byteArray(byte_array, o3);

		j+=3;
	}
}

void b12_printf(const twelveBit_t Oc, const char *ident, const int mode) {
  static char buffer[12];

  printf("%s = 0b", ident);

  for(int n = 0; n < 12; n++) {
    twelveBit_t bit = (1 << n);
    buffer[11-n] = ((Oc & bit) ? '1' : '0');
  }

  printf("%s", buffer);

  if(mode == 1)
    printf(" = %u", Oc);
  printf("\n");
}

void b12Array_print(twelveBit_t b12_array[], int size_b12Array, const int mode){
	printf("Array of %d twelveBit_t :\n", size_b12Array);
	for(int i = 0; i < size_b12Array; i++){
		b12_printf(b12_array[i], "   ", 1);
	}
}

void byArray_print(byte_t byte_array[], int size_byArray, const int mode){
	printf("Array of %d byte_t :\n", size_byArray);
	for(int i = 0; i < size_byArray; i++){
		printf("cc\n");
		byprintf(byte_array[i], "   ", 1);
	}
}



/* TD 1 functions : 																												*/

void byprintf(const byte_t Oc, const char *ident, const int mode) {
  static char buffer[8];

  printf("%s = 0b", ident);

  for(int n = 0; n < 8; n++) {
    byte_t bit = (1 << n);
    buffer[7-n] = ((Oc & bit) ? '1' : '0');
  }

  printf("%s", buffer);

  if(mode == 1)
    printf(" = %u", Oc);
  printf("\n");
}

byte_t byread() {
  int c;

  printf("Donner un octet (0-255) : ");
  scanf(" %d" , &c);

  assert( -1 < c && c < 256 );

  return (byte_t) c;
}

int biread(const byte_t Oc, const int n) {
  assert(n >= 1 && n <= 8); // a byte has 8 bit

  byte_t tmp_Oc = Oc;

  byte_t mask = 255 - pow(2, n-1); // ex: if n=4 : target = 11110111
  byte_t res = (tmp_Oc | mask);
  //printf("res : %d\n", res);
  if(res == 255) // if res = 11111111
    return 1;
  else
    return 0;
}

byte_t biwrite(const byte_t Oc, const int n) {
  assert(n >= 1 && n <= 8); // a byte has 8 bit

  byte_t res = 0;

  if(biread(Oc, n) == 1){
    res = Oc - pow(2, n-1);
  }
  else { // == 0
    res = Oc + pow(2, n-1);
  }

  return res;
}

byte_t infQread(byte_t O) {
  assert(O >= 0 && O < 256);

  static byte_t mask = 15; //00001111
  byte_t res = 0;

  O = (O & mask);

  for(int i = 0; i < 8; i++) {
    byte_t bit = (1 << i);
    if(O & bit)
      res += pow(2, i);
  }

  return res;
}

byte_t supQread(byte_t O) {
  assert(O >= 0 && O < 256);

  static byte_t mask = 240; //11110000
  byte_t res = 0;

  O = (O & mask);

  for(int i = 0; i < 8; i++) {
    byte_t bit = (1 << i);
    if(O & bit){
      res += pow(2, i);
    }
  }

  return res;
}

byte_t infQwrite(byte_t O, byte_t qi) {
  assert(O >= 0 && O < 256);
  assert(qi >= 0 && qi < 16);

  for(int i = 0; i < 4; i++) {
    byte_t bit = (1 << i);
    if(qi & bit){
      O += pow(2, i);
    }
  }

  return O;
}

byte_t supQwrite(byte_t O, byte_t qs) {
  assert(O >= 0 && O < 256);
  assert(qs >= 16 && qs < 256);

  for(int i = 4; i < 8; i++) {
    byte_t bit = (1 << i);
    if(qs & bit){
      O += pow(2, i);
    }
  }

  return O;
}
