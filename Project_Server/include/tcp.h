#ifndef _TCP_
#define _TCP_

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/un.h>

typedef struct args_tcp {
  int my_socket;
  int client_socket;
  struct sockaddr_in my_addr;
  struct sockaddr_in client_addr;
  socklen_t my_addr_len;
  char buffer; // send byte by byte
} args_tcp;

void create_tcp(args_tcp *a);
void create_socket_tcp(args_tcp *a);
void bind_tcp(args_tcp *a);
void listen_tcp(args_tcp *a);
void connect_tcp(args_tcp *a);
void disconnect_tcp(args_tcp *a);
/* -------------------------------------------------------------------------- */
void encode_file(args_tcp *a);
void send_dictionary(args_tcp *a);
void send_codefile(args_tcp *a);
void send_code(args_tcp *a);

#endif
