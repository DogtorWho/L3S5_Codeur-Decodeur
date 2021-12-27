#ifndef _ERROR_
#define _ERROR_

void log_error(const char *msg){
  fprintf(stderr, "error::%s\n", msg);
  exit(1);
}

#endif
