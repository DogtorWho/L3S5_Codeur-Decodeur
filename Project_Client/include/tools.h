#ifndef _TOOLS_
#define _TOOLS_

#include <stdio.h>

#include "globals.h"
#include "byteArray.h"
#include "LZW_twelveBitArray.h"

/* return the size (number of char) of fd */
unsigned long fsize(FILE *fd);

/* transform each character of a text file into a byte_t and return an array of all these bytes */
void text_to_byteArray(byteArray *byte_array, char* filename);

/* transform each character of a text file into a twelveBit_t and return an array of all these b12 */
void text_to_b12Array(twelveBitArray *b12_array, char* filename);

/* take two int (i1, i2) representing two binary numbers with 12 digits
		and transform them into three bytes (o1, o2, o3)
		      i1               i2
		0000 0000 0000 | 0000 0000 0000
	      o1   |     o2    |    o3         */
void twoInt_to_threeBytes(twelveBit_t i1, twelveBit_t i2, byte_t *o1, byte_t *o2, byte_t *o3);

/* take three bytes (o1, o2, o3)
		and transform them into two int (i1, i2) representing two binary numbers with 12 digits
			  o1   |     o2    |    o3
		0000 0000 0000 | 0000 0000 0000
		      i1               i2            */
void threeBytes_to_twoInt(byte_t o1, byte_t o2, byte_t o3, twelveBit_t *i1, twelveBit_t *i2);

/* take an array of twelveBit_t and transform them into an array of byte */
void byteArray_to_b12Array(byteArray *byte_array, twelveBitArray *b12_array);

/* take an array of byte and transform them into an array of twelveBit_t */
void b12Array_to_byteArray(twelveBitArray *b12_array, byteArray *byte_array);

/* print a twelveBit_t in binary format */
void b12_printf(const twelveBit_t Oc, const char *ident, const int mode);

void b12Array_print(twelveBit_t b12_array[], int size_b12Array, const int mode);

void byArray_print(byte_t byte_array[], int size_byArray, const int mode);


/* TD 1 functions : 																												*/

/* print a byte in binary format */
void byprintf(const byte_t, const char *ident, const int mode);

/* read a byte (between 0 and 255) */
byte_t byread();

/* read a bit of byte_t (between 0 and 7) */
int biread(const byte_t, const int);

/* write a bit on byte_t (between 0 and 7) */
byte_t biwrite(const byte_t, const int);

/* return the first 4 bits of the byte O */
byte_t infQread(byte_t O);

/* return the last 4 bits of the byte O */
byte_t supQread(byte_t O);

/* modify the byte O with the first 4 bits of qi and return O */
byte_t infQwrite(byte_t O, byte_t qi);

/* modify the byte O with the last 4 bits of qi and return O */
byte_t supQwrite(byte_t O, byte_t qs);

#endif
