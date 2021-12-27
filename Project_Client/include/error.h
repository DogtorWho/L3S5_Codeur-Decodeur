/**
 * @file error.h
 * File containing error handling functions.
 */

#ifndef _ERROR_
#define _ERROR_

/**
 * @fn void log_error(const char *msg)
 * @brief log a message
 * print the message in the stderr
 * @param msg string containing the error message
 */
void log_error(const char *msg){
  fprintf(stderr, "error::%s\n", msg);
  exit(1);
}

#endif
