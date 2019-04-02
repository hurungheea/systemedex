#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include "msq-common.h"
#include "msq-message.h"

char* global_argv;

int main(int argc,  char *argv[])
{
  key_t key;
  msq_message_t messTMP;
  char* pathname = "file.ftok";
  int id = 1,sec = 1, times = 1;
  int option_index = 0, requests = 0;

  global_argv = malloc(sizeof(char) * strlen(argv[0]));
  global_argv = argv[0];

  msq_message_set_text(&messTMP, "This is the default message text");
  msq_message_set_type(&messTMP, 1);

  argumentFromClient(argc, argv, ":hvi:p:s:t:x:y:", &option_index, &id, &pathname, &sec, &times, &messTMP);

  printf("proj_id = \"%d\"\n", id);
  printf("pathname = \"%s\"\n", pathname);

  key = ftok(pathname, id);
  if(key == (key_t)-1)
    displayError(NULL, argv[0], __FILE__, __LINE__, pathname, id);

  requests = msgget(key, 0);
  if(requests == -1)
  {
    errno = 17;
    displayError(NULL, argv[0], __FILE__, __LINE__, pathname, id);
  }

  while(times > 0)
  {
    msgsnd(requests, &messTMP, sizeof(messTMP), 0);
    msq_message_print(messTMP);
    if(sec == 0)
      waitingForEnter();
    else
    {
      if(times > 1 && times != 0)
        sleep(sec);
    }
    if(times > 0)
      times--;
  }
  return 0;
}
