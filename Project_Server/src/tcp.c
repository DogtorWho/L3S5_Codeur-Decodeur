/**
 * @file tcp.c
 * File containing the functions to control the TCP between the client and the server.
 */

#include "tcp.h"

#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

#include "error.h"
#include "tools.h"
// LZW
#include "LZW_Encoder.h"
//Huffman
#include "Huffman_FreqChar.h"
#include "Huffman_Tree.h"
#include "Huffman_Encoder.h"


typedef enum coder { LZW, HUFFMAN, CODER_SIZE } coder;

void create_tcp(args_tcp *a){
  bzero(&(a->my_addr), sizeof(a->my_addr));
  a->my_addr.sin_port = htons(30000);
  a->my_addr.sin_family = AF_INET;
  a->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void create_socket_tcp(args_tcp *a){
  if((a->my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    log_error("create_socket_tcp::failed to create the socket");
}

void bind_tcp(args_tcp *a){
  bind(a->my_socket,(struct sockaddr *)&(a->my_addr),sizeof(a->my_addr));
}

void listen_tcp(args_tcp *a){
  listen(a->my_socket, 5);
}

void connect_tcp(args_tcp *a){
  a->my_addr_len = sizeof(a->client_addr);

  a->client_socket = accept(a->my_socket, (struct sockaddr *)&(a->client_addr), &(a->my_addr_len));

  if(fork() == 0){
    close(a->my_socket);

    //wait to receive the demand for encoding from the client
    encode_file(a);

    // tmp, close the server when finished
    shutdown(a->client_socket, 2);
    close(a->client_socket);
    exit(0);
  }
  wait(NULL);
}

void disconnect_tcp(args_tcp *a){
  shutdown(a->my_socket, 2);
  close(a->my_socket);
}

/* -------------------------------------------------------------------------- */

void encode_file(args_tcp *a){
  char tmp[3] = "";
  coder choice;
  char filename[BUFSIZ] = "include/texts/";

  do{
    read(a->client_socket, &a->buffer, 1);
    strcat(tmp, &a->buffer);
  }while(a->buffer != '\0');
  choice = atoi(tmp);

  do{
    read(a->client_socket, &a->buffer, 1);
    strcat(filename, &a->buffer);
  }while(a->buffer != '\0');

  printf("Encoding ...\n\n");
  switch(choice){
    case LZW :
      encoder_dictionary(filename);
      send_dictionary(a);
      break;
    case HUFFMAN :
      Huffman_encoding(filename);
      send_codefile(a);
      send_code(a);
      break;
    default : printf(" Client encoder choice is not valid\n"); exit(1);
      break;
  }
}

void send_dictionary(args_tcp *a){
  FILE *fp = fopen("build/lzw_encoded.bin", "rb");
  assert(fp);

  long nb_bytes = fsize(fp); // number of bytes to send
  char tmp[10];
  sprintf(tmp, "%ld", nb_bytes);
  char end = '\0';

  // send the size of the code
  for(int i=0; i < strlen(tmp); i++)
    write(a->client_socket, &tmp[i], 1);
  write(a->client_socket, &end, 1); // add the \0

  // send the code
  char c;
  for(int i=0; i < nb_bytes; i++){
    c = fgetc(fp);
    write(a->client_socket, &c, 1);
    //printf("%c", c);
  }

  fclose(fp);
}

void send_codefile(args_tcp *a){
  FILE *fp = fopen("build/huffman.cod", "r");
  assert(fp);

  char c;
  while((c = fgetc(fp)) != EOF){
    write(a->client_socket, &c, 1);
    //printf("%c", c);
  }
  c = '\0';
  write(a->client_socket, &c, 1); // add the \0

  fclose(fp);
}

void send_code(args_tcp *a){
  FILE *fp = fopen("build/huffman_encoded.bin", "rb");
  assert(fp);

  long nb_bytes = fsize(fp); // number of bytes to send
  char tmp[10];
  sprintf(tmp, "%ld", nb_bytes);
  char end = '\0';

  // send the size of the code
  for(int i=0; i < strlen(tmp); i++)
    write(a->client_socket, &tmp[i], 1);
  write(a->client_socket, &end, 1); // add the \0

  // send the code
  char c;
  for(int i=0; i < nb_bytes; i++){
    c = fgetc(fp);
    write(a->client_socket, &c, 1);
    //printf("%c", c);
  }

  fclose(fp);
}
