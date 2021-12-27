/**
 * @file tcp.h
 * File containing the functions to control the TCP between the client and the server.
 */

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

/**
 * @def SERVEURNAME
 * @brief adress of the server for the TCP
 */
#define SERVEURNAME "127.0.0.1"

/**
 * @struct args_tcp
 * @brief stock all the variables communicating with the TCP
 * @param to_server_socket socket connected to the server
 * @param sockaddr_in the address of the socket
 * @param hostent* the entities of the host
 * @param hostAddr address of the host
 * @param buffer stock the byte received
 */
typedef struct args_tcp {
  int to_server_socket;
  struct sockaddr_in serverSockAddr;
  struct hostent *serverHostEnt;
  long hostAddr;
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
 * @fn void connect_tcp(args_tcp *a)
 * @brief connect to the server
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
 * @fn void send_encoding_demand(args_tcp *a, coder encoder, char *filename)
 * @brief send a request for encoding to the server
 * send the choice of encoder and the filename to the server and ask it to encode
 * @param a has all the variables to communicate with TCP
 * @param encoder type of encoder
 * @param filename file to encode
 */
void send_encoding_demand(args_tcp *a, coder encoder, char *filename);

/**
 * @fn void receive_dictionary(args_tcp *a)
 * @brief receive an encoded dictionary
 * receive an encoded dictionary and create a binary file which can be decode with the LZW decoding
 * @param a has all the variables to communicate with TCP
 */
void receive_dictionary(args_tcp *a);

/**
 * @fn void receive_codefile(args_tcp *a)
 * @brief receive a code file
 * receive a code file and create a text file with all the codes
 * @param a has all the variables to communicate with TCP
 */
void receive_codefile(args_tcp *a);

/**
 * @fn void receive_code(args_tcp *a)
 * @brief receive a encoded file
 * receive an encoded string and create a binary file which can be decode with the Huffman decoding
 * @param a has all the variables to communicate with TCP
 */
void receive_code(args_tcp *a);

#endif
