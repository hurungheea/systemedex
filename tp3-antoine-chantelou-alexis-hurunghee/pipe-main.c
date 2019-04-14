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
  int pipefd[2], read_pipe = 0;

  pipe_message_t message_tampon,test;

  int seconds_receiving = 1, times_sending = 1, seconds_sending = 1, times_receiving = -1;
  int option_index = 0;


  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &seconds_receiving, &message_tampon,&times_sending, &seconds_sending, &times_receiving);

  if(seconds_receiving == 0)
    waitingForEnter();

  if(pipe2(pipefd,O_DIRECT) == -1)
  {
    perror("pipefd error\n");
    exit(EXIT_FAILURE);
  }

  while(times_receiving != 0)
  {
    if(times_sending > 0)
    {
      call_my_son(&message_tampon, pipefd,seconds_sending,times_sending);
      times_sending -= times_sending;
      wait(0);
    }

    close(pipefd[1]);
    while((read_pipe = read(pipefd[0],&test,sizeof(test))) > 0 )
    {
      if(seconds_receiving > 0)
      {
        sleep(seconds_receiving);
      }
      else
      {
        waitingForEnter();
      }
      pipe_message_print(test, READ);
    }
  }

  return 0;
}
