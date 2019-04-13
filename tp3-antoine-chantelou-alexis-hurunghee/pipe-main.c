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

  int times_receive = 1, times_sending = 1, seconds_sending = 1, times_receiving = -1;
  int option_index = 0;


  argument_opt(argc,argv,":hvr:s:t:u:x:", &option_index, &times_receive, &message_tampon,&times_sending, &seconds_sending, &times_receiving);

  if(times_receive == 0)
    waitingForEnter();

  while(times_receiving < 0)
  {
    if(pipe2(pipefd,O_DIRECT) == -1)
    {
      perror("pipefd error\n");
      exit(EXIT_FAILURE);
    }

    if(times_sending > 0)
    {
      if(seconds_sending == 0)
        waitingForEnter();
      else
      {
        sleep(seconds_sending);
        times_sending--;
      }
      call_my_son(&message_tampon, pipefd);
    }

    wait(0);

    sleep(times_receive);

    close(pipefd[1]);
    if(read(pipefd[0],&test,sizeof(test)) > 0)
      pipe_message_print(test, READ);
  }

  return 0;
}
