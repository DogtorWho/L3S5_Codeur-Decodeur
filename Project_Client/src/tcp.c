/**
 * @file tcp.c
 * File containing the functions to control the TCP between the client and the server.
 */

#include "tcp.h"

#include <string.h>
#include <assert.h>

#include "error.h"

void create_tcp(args_tcp *a){
  bzero(&(a->serverSockAddr), sizeof(a->serverSockAddr));
  a->hostAddr = inet_addr(SERVEURNAME);

  if((long)a->hostAddr != (long)-1)
    bcopy(&(a->hostAddr), &(a->serverSockAddr.sin_addr), sizeof(a->hostAddr));
  else{
    a->serverHostEnt = gethostbyname(SERVEURNAME);
    if(a->serverHostEnt == NULL)
      log_error("create_tcp::gethostbyname::serverHostEnt is NULL");

    bcopy(a->serverHostEnt->h_addr, &(a->serverSockAddr.sin_addr), a->serverHostEnt->h_length);
  }
  a->serverSockAddr.sin_port = htons(30000);
  a->serverSockAddr.sin_family = AF_INET;
}

void create_socket_tcp(args_tcp *a){
  if((a->to_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    log_error("create_socket_tcp::failed to create the socket");
}

void connect_tcp(args_tcp *a){
  if(connect(a->to_server_socket, (struct sockaddr*)&(a->serverSockAddr), sizeof(a->serverSockAddr)) < 0)
    log_error("connect_tcp::failed to connect");
}

void disconnect_tcp(args_tcp *a){
  shutdown(a->to_server_socket, 2);
  close(a->to_server_socket);
}

/* -------------------------------------------------------------------------- */

void send_encoding_demand(args_tcp *a, coder encoder, char *filename){
  char tmp[3];
  sprintf(tmp, "%d", encoder);

  a->buffer = '\0';
  for(int i=0; i < strlen(tmp); i++)
    write(a->to_server_socket, &tmp[i], 1);
  write(a->to_server_socket, &a->buffer, 1); // add the \0

  for(int i=0; i < strlen(filename); i++)
    write(a->to_server_socket, &filename[i], 1);
  write(a->to_server_socket, &a->buffer, 1); // add the \0
}

void receive_dictionary(args_tcp *a){
  FILE *fp = fopen("bin/lzw_encoded.bin", "wb");
  assert(fp);

  long nb_bytes = 0;
  char tmp[10] = "";
  do{
    read(a->to_server_socket, &a->buffer, 1);
    strcat(tmp, &a->buffer);
  }while(a->buffer != '\0');
  nb_bytes = atoi(tmp);

  for(int i=0; i < nb_bytes; i++){
    read(a->to_server_socket, &a->buffer, 1);
    fwrite(&a->buffer, 1, 1, fp);
  }

  fclose(fp);
}

void receive_codefile(args_tcp *a){
  FILE *fp = fopen("bin/huffman.cod", "w");
  assert(fp);

  do{
    read(a->to_server_socket, &a->buffer, 1);
    //printf("%c", a->buffer);
    if(a->buffer != '\0')
      fputc(a->buffer, fp);
  } while(a->buffer != '\0');

  fclose(fp);
}

void receive_code(args_tcp *a){
  FILE *fp = fopen("bin/huffman_encoded.bin", "wb");
  assert(fp);

  long nb_bytes = 0;
  char tmp[10] = "";
  do{
    read(a->to_server_socket, &a->buffer, 1);
    strcat(tmp, &a->buffer);
  }while(a->buffer != '\0');
  nb_bytes = atoi(tmp);

  for(int i=0; i < nb_bytes; i++){
    read(a->to_server_socket, &a->buffer, 1);
    fwrite(&a->buffer, 1, 1, fp);
  }

  fclose(fp);
}
