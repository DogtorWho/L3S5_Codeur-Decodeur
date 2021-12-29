/**
 * @file inputs.c
 * File containing functions which communicates with the user.
 */

#include "inputs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @def list_size
 * @brief Size of the list of texts
 */
#define list_size 6

/**
 * @var file_list
 * @brief List of text files to encode
 */
static char file_list[list_size][BUFSIZ] = { 
	{"Text_de_base.txt"}, 
	{"10_000_bytes.txt"},
	{"100_000_bytes.txt"},
	{"1_000_000_bytes.txt"},
	{"Musketeers.txt"},
	{"Queens.txt"}
};


bool check_filename(const char *filename){
  for(int i = 0; i < list_size; i++)
    if(strcmp(filename, file_list[i]) == 0) // filename is in the list
      return true; // found the file

  return false; // didn't found the file
}

char* choiceOfFile(){
  char *choice = malloc(BUFSIZ);
  printf("\nYour filename is not valid,\n  please choose a file from this preselected list :\n\n");
  for(int i=0; i<list_size; i++)
    printf(" %d - %s\n", i+1, file_list[i]);
  printf("\n");

  int c;
  do{ // the user pick one file
    printf("Which file do you want ? (1 - %d) : ", list_size);
    scanf("%d", &c);
    printf("\n");
  } while(c<1 || c>list_size);

  strcpy(choice, file_list[c-1]); // get the name of the file picked
  return choice; // return the filename
}

coder choiceOfCoder(){
  printf("\nChoose a coder from this list : \n\n");
  printf(" 1 - LZW\n");
  printf(" 2 - Huffman\n");
  printf("\n");

  int choice;
  do{ // the user pick one coder
    printf("Which coder do you want to use ? (1 - %d) : ", CODER_SIZE);
    scanf("%d", &choice);
    printf("\n");
  } while(choice<1 || choice>CODER_SIZE);

  choice--; // the enum start at 0 so we subtract from choice which start at 1
  return choice; // return the coder
}
