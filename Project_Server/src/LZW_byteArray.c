#include "LZW_byteArray.h"

#include <stdio.h>
#include <assert.h>

#include "tools.h"

void init_byteArray(byteArray *a, size_t initialSize) {
  assert(a != NULL);
  assert(initialSize > 0);

  a->array = malloc(initialSize * sizeof(byte_t));
  a->used = 0;
  a->size = initialSize;
}

void insert_byteArray(byteArray *a, byte_t byte) {
  assert(a != NULL);
  assert(a->array != NULL);

  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(byte_t));
    assert(a->array != NULL);
  }
  a->array[a->used++] = byte;
}

void free_byteArray(byteArray *a) {
  assert(a != NULL);

  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void print_byteArray(byteArray *a) {
  assert(a != NULL);
  assert(a->array != NULL);

  printf(" - Size : %ld\n", a->size);
  printf(" - Size used : %ld\n", a->used);
  printf(" - Variables : \n");
  for(int i=0; i < a->used; i++)
    byprintf(a->array[i], "   ", 1);
  printf("\n");
}

void byteArray_to_binaryFile(byteArray *a, char *filename){
  assert(a != NULL);
  assert(a->array != NULL);

  FILE *fd = fopen(filename, "wb");
  assert(fd != NULL);

  fwrite(a->array, 1, a->used, fd);

  fclose(fd);
}

void binaryFile_to_byteArray(byteArray *a, char *filename){
  assert(a != NULL);

  FILE *fd = fopen(filename, "rb");
  assert(fd != NULL);

  unsigned long size = fsize(fd);

  free_byteArray(a);
  init_byteArray(a, size);

  fread(a->array, 1, size, fd);

  a->used = size;

  fclose(fd);
}
