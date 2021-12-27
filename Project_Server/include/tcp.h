/**
 * @file tcp.h
 * File containing the functions to control the TCP between the client and the server.
 */

#ifndef _TCP_
#define _TCP_

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/un.h>

/**
 * @struct args_tcp
 * @brief stock all the variables communicating with the TCP
 * @param my_socket socket of the server
 * @param client_socket socket connected to the client
 * @param my_addr the address of the server
 * @param client_addr the address of the client
 * @param my_addr_len size of the server's socket
 * @param buffer stock the byte received
 */
typedef struct args_tcp {
  int my_socket;
  int client_socket;
  struct sockaddr_in my_addr;
  struct sockaddr_in client_addr;
  socklen_t my_addr_len;
  char buffer; // send byte by byte
} args_tcp;

/**
 * @fn void create_tcp(args_tcp *a)
 * @brief create the TCP
 * @param a has all the variables to communicate with TCP
 */
void create_tcp(args_tcp *a);

/**
 * @fn void create_socket_tcp(args_tcp *a)
 * @brief create the socket of the server
 * @param a has all the variables to communicate with TCP
 */
void create_socket_tcp(args_tcp *a);

/**
 * @fn void bind_tcp(args_tcp *a)
 * @brief bind the socket of the server
 * @param a has all the variables to communicate with TCP
 */
void bind_tcp(args_tcp *a);

/**
 * @fn void listen_tcp(args_tcp *a)
 * @brief listen on the socket of the server
 * @param a has all the variables to communicate with TCP
 */
void listen_tcp(args_tcp *a);

/**
 * @fn void connect_tcp(args_tcp *a)
 * @brief connect to the server and talk to the client
 * when the client connects, lanch the encoding functions
 * @param a has all the variables to communicate with TCP
 */
void connect_tcp(args_tcp *a);

/**
 * @fn void disconnect_tcp(args_tcp *a)
 * @brief disconnect from the server
 * @param a has all the variables to communicate with TCP
 */
void disconnect_tcp(args_tcp *a);

/* -------------------------------------------------------------------------- */

/**
 * @fn void encode_file(args_tcp *a)
 * @brief encode a file chosen by the client and send it to him
 * @param a has all the variables to communicate with TCP
 */
void encode_file(args_tcp *a);

/**
 * @fn void send_dictionary(args_tcp *a)
 * @brief send the dictionary file to the client
 * @param a has all the variables to communicate with TCP
 */
void send_dictionary(args_tcp *a);

/**
 * @fn void send_codefile(args_tcp *a)
 * @brief send the code file to the client
 * @param a has all the variables to communicate with TCP
 */
void send_codefile(args_tcp *a);

/**
 * @fn void send_code(args_tcp *a)
 * @brief send the codes to the client
 * @param a has all the variables to communicate with TCP
 */
void send_code(args_tcp *a);

#endif
