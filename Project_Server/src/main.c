#include <stdio.h>

#include "tcp.h"

int main(void){
  /* create and initialize the variables */
  args_tcp *a = malloc(sizeof(args_tcp));
  a->buffer = 0;

  /* open tcp */
  create_tcp(a);
  create_socket_tcp(a);

  /* get the client connexion */
  bind_tcp(a);
  listen_tcp(a);

  /* encode the client file and send it */
  connect_tcp(a);

  /* close tcp */
  disconnect_tcp(a);

  /* free variables */
  free(a);

  /* clean the /bin folder */
  remove("bin/lzw_encoded.bin");
  remove("bin/code.tmp");
  remove("bin/huffman_encoded.bin");
  remove("bin/huffman.cod");

  return 0;
}
