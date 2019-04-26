#include <wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pipe-common.h"
#include "pipe-message.h"

int main(int argc, char **argv)
{
  pid_t pid;
  int option_index = 0;
  int pipefd[2], res_write = 0;
  pipe_message_t write_message, read_message;
  int seconds_receiving = 1, times_sending = 1, seconds_sending = 1, times_receiving = -1, sent = 0;


  if(pipe_message_set_text(&write_message, "This is the default message text") == -1)
    exit(EXIT_FAILURE);

  if(pipe_message_set_pid(&write_message, (pid_t) getpid()) == -1)
    exit(EXIT_FAILURE);

  argument_opt(argc, argv, ":hvr:s:t:u:x:", &option_index, &seconds_receiving, &write_message, &times_sending, &seconds_sending, &times_receiving);

  if(pipe2(pipefd, O_DIRECT) == -1)
  {
    perror("pipefd error\n");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if(pid == 0)
  {

    while(times_sending != 0)
    {
      if(sent > 0)
      {
        if(seconds_sending > 0)
          sleep(seconds_sending);
        else
          waitingForEnter('w');
        close(pipefd[0]);
        if((res_write = write(pipefd[1], &write_message, sizeof(pipe_message_t))) == 0)
        {
          errno = 524;
          display_error(NULL,);
        }
      }
      else
      {
        if(seconds_sending == 0)
          waitingForEnter('w');
        close(pipefd[0]);
        if((res_write = write(pipefd[1],&write_message,sizeof(pipe_message_t))) == 0)
        {
          perror("erreur write");
        }
      }
      pipe_message_print(write_message,WRITTEN);
      sent++;
      if(times_sending > 0)
        times_sending--;
    }
    exit(EXIT_SUCCESS);
  }
  else
  {
    while(times_receiving != 0)
    {
      if(seconds_receiving > 0)
        sleep(seconds_receiving);
      else
        waitingForEnter('r');

      close(pipefd[1]);
      if(read(pipefd[0],&read_message,sizeof(pipe_message_t)) > 0)
        pipe_message_print(read_message,READ);
      if(times_receiving > 0)
        times_receiving--;
    }
  }
  return 0;
}
