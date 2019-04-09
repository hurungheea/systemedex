#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include "pipe-common.h"
#include "pipe-message.h"

char** global_argv;

int main(int argc, char **argv)
{
  int times = -1;
  int pipefd[2];

  pid_t child = fork();
  pipe_message_t message_tampon;

  int sec = 1, id = 1;
  char* pathname = "file.ftok";
  int option_index = 0;

  if(pipe(pipefd,O_DIRECT) == -1)
  {
    perror("pipefd error\n");
    exit(EXIT_FAILURE);
  }

  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &id, &pathname, &sec, &times, &message_tampon);
  if(child == 0)
  {
    printf("child : %d\n",(pid_t) getpid());
    if(pipe_message_set_text(&message_tampon,"This is the default message text") == -1)
      exit(EXIT_FAILURE);

    if(pipe_message_set_pid(&message_tampon,(pid_t) getpid()) == -1)
      exit(EXIT_FAILURE);

    close(pipefd[]);

    exit(0);
  }
  wait(0);

  pipe_message_print(message_tampon,READ);

  return 0;
}
