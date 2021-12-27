#ifndef _INPUTS_
#define _INPUTS_

#include <stdbool.h>

typedef enum coder { LZW, HUFFMAN, CODER_SIZE } coder;

bool check_filename(const char *filename);
char* choiceOfFile();
coder choiceOfCoder();

#endif
