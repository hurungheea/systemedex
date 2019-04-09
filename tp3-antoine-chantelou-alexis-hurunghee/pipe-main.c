#include <stdio.h>
#include <stdlib.h>
#include "pipe-common.h"
#include "pipe-message.h"

int main(int argc, char **argv)
{
  int times = -1;
  int sec = 1, id = 1;
  char* pathname = "file.ftok";
  int option_index = 0;

  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &id, &pathname, &sec, &times);

  return 0;
}
