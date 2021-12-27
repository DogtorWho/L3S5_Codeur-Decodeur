#ifndef _ERROR_
#define _ERROR_

/**
 * @fn void log_error(const char *msg)
 * print the message in the stderr
 * @param msg  [description]
 * @brief log a message
 */
void log_error(const char *msg){
  fprintf(stderr, "error::%s\n", msg);
  exit(1);
}

#endif
