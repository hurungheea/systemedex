#include <wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipe-common.h"
#include "pipe-message.h"

char** global_argv;

int main(int argc, char **argv)
{
  int pipefd[2];

  pipe_message_t message_tampon,test;

  int sec = 1, id = 1, times_receive = 1, times_sending = 1, seconds_sending = 1;
  char* pathname = "file.ftok";
  int option_index = 0;

  if(pipe2(pipefd,O_DIRECT) == -1)
  {
    perror("pipefd error\n");
    exit(EXIT_FAILURE);
  }

  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &id, &pathname, &sec, &times_receive, &message_tampon,&times_sending, &seconds_sending);

  if(times_receive == 0)
    waitingForEnter();

  if(fork() == 0)
  {
    if(pipe_message_set_text(&message_tampon,"This is the default message text") == -1)
      exit(EXIT_FAILURE);

    if(pipe_message_set_pid(&message_tampon,(pid_t) getpid()) == -1)
      exit(EXIT_FAILURE);

    close(pipefd[0]);
    write(pipefd[1],&message_tampon,sizeof(message_tampon));
    pipe_message_print(message_tampon,WRITTEN);

    exit(0);
  }
  wait(0);

  while(times_receive > 0)
  {
    close(pipefd[1]);
    if(times_receive == 0)
      waitingForEnter();
    else
      sleep(times_receive);
    if(read(pipefd[0],&test,sizeof(test)) > 0)
      pipe_message_print(test,READ);

  }


  return 0;
}
