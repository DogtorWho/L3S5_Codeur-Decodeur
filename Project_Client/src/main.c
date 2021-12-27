#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tcp.h"
#include "inputs.h"
// LZW
#include "LZW_Decoder.h"
//Huffman
#include "Huffman_FreqChar.h"
#include "Huffman_Tree.h"
#include "Huffman_Decoder.h"

int main(int argc, char* argv[]){
  /* create and initialize the variables */
  args_tcp *a = malloc(sizeof(args_tcp));
  char* filename = malloc(BUFSIZ);
  coder choice;

  a->to_server_socket = -1;
  a->hostAddr = 0;
  a->buffer = 0;

  /* connect to server */
  create_tcp(a);
  create_socket_tcp(a);
  connect_tcp(a);

  /* get the filename */
  if(argv[1] != NULL){ // a filename is given in argument
    strcpy(filename, argv[1]);
    if(!check_filename(filename)) // the filename don't exist in the list
      strcpy(filename, choiceOfFile()); // let the user choose from a list of texts
  }
  else{ // no filename given
    strcpy(filename, choiceOfFile()); // let the user choose from a list of texts
  }
  printf(" You choose the file : %s\n", filename);

  /* get the encoder choice */
  choice = choiceOfCoder();
  switch(choice){
    case LZW : printf(" You choose the encoder : LZW\n");
      break;
    case HUFFMAN : printf(" You choose the encoder : Huffman\n");
      break;
    default : printf(" This is not a valid encoder\n"); exit(1);
      break;
  }

  /* ------------------------------------------------------------------------ */

  /* get the encoding from the server */
  send_encoding_demand(a, choice, filename);

  /* decode the file */
  printf("Decoding ...\n\n");
  switch(choice){
    case LZW :
      receive_dictionary(a);
      decoder_dictionary("bin/lzw_encoded.bin");
      break;
    case HUFFMAN :
      receive_codefile(a);
      receive_code(a);
      Huffman_decoding("bin/huffman_encoded.bin");
      break;
    default : break;
  }

  /* disconnect from server */
  disconnect_tcp(a);

  /* free variables */
  free(filename);
  free(a);

  /* clean the /bin folder */
  switch(choice){
    case LZW :
      remove("bin/huffman_decoded.txt");
    case HUFFMAN :
      remove("bin/lzw_decoded.txt");
    default : break;
  }
  remove("bin/lzw_encoded.bin");
  remove("bin/huffman_encoded.bin");
  remove("bin/huffman.cod");

  return 0;
}
