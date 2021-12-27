#ifndef _TCP_
#define _TCP_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "inputs.h"

#define SERVEURNAME "127.0.0.1"

typedef struct args_tcp {
  int to_server_socket;
  struct sockaddr_in serverSockAddr;
  struct hostent *serverHostEnt;
  long hostAddr;
  char buffer; // send byte by byte
} args_tcp;

void create_tcp(args_tcp *a);
void create_socket_tcp(args_tcp *a);
void connect_tcp(args_tcp *a);
void disconnect_tcp(args_tcp *a);
/* -------------------------------------------------------------------------- */
void send_encoding_demand(args_tcp *a, coder encoder, char *filename);
void receive_dictionary(args_tcp *a);
void receive_codefile(args_tcp *a);
void receive_code(args_tcp *a);

#endif
