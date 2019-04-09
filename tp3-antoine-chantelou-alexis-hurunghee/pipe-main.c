#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipe-common.h"
#include "pipe-message.h"

char** global_argv;

int main(int argc, char **argv)
{
  int times = -1;
  pid_t pid;
  pipe_message_t messageTMP;
  int sec = 1, id = 1;
  char* pathname = "file.ftok";
  int option_index = 0;

  if(pipe_message_set_text(&messageTMP,"This is the default message text") == -1)
    exit(EXIT_FAILURE);

  pid = getpid();

  if(pipe_message_set_pid(&messageTMP,pid) == -1)
    exit(EXIT_FAILURE);

  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &id, &pathname, &sec, &times, &messageTMP);


  pipe_message_print(messageTMP,READ);

  return 0;
}
