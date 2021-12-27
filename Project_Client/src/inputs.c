#include "inputs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define list_size 4
static char file_list[list_size][BUFSIZ] = { {"helloWorld.txt"}, {"Text_de_base.txt"}, {"10_000_bytes.txt"}, {"100_000_bytes.txt"} };

bool check_filename(const char *filename){
  for(int i = 0; i < list_size; i++)
    if(strcmp(filename, file_list[i]) == 0) // filename is in the list
      return true;

  return false;
}

char* choiceOfFile(){
  char *choice = malloc(BUFSIZ);
  printf("\nYour filename is not valid,\n  please choose a file from this preselected list :\n\n");
  for(int i=0; i<list_size; i++)
    printf(" %d - %s\n", i+1, file_list[i]);
  printf("\n");

  int c;
  do{
    printf("Which file do you want ? (1 - %d) : ", list_size);
    scanf("%d", &c);
    printf("\n");
  } while(c<1 || c>list_size);

  strcpy(choice, file_list[c-1]);
  return choice;
}

coder choiceOfCoder(){
  printf("\nChoose a coder from this list : \n\n");
  printf(" 1 - LZW\n");
  printf(" 2 - Huffman\n");
  printf("\n");

  int choice;
  do{
    printf("Which coder do you want to use ? (1 - %d) : ", CODER_SIZE);
    scanf("%d", &choice);
    printf("\n");
  } while(choice<1 || choice>CODER_SIZE);

  choice--;
  return choice;
}
