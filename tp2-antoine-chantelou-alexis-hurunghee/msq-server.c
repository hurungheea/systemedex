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
  int times = -1;
  int sec = 1, id = 1;
  msq_message_t messTMP;
  char* pathname = "file.ftok";
  int request = 0, res = 0, option_index = 0;

  global_argv = malloc(sizeof(char) * strlen(argv[0]));
  global_argv = argv[0];

  argumentFromServer(argc,argv,":hvi:p:s:t:", &option_index, &id, &pathname, &sec, &times);

  printf("proj_id = \"%d\"\n", id);
  printf("pathname = \"%s\"\n", pathname);

  key = ftok(pathname, id);
  if(key == (key_t) -1)
    displayError(NULL, argv[0], __FILE__, __LINE__, pathname, id);

  request = msgget(key, IPC_CREAT|IPC_EXCL|0600);
  if(request == -1)
    displayError(NULL, argv[0], __FILE__, __LINE__, (int) key);

  while(times != 0)
  {
    if(sec == 0)
      waitingForEnter();
    else
      sleep(sec);
    if(times > 0)
      times--;
    res = msgrcv(request, &messTMP, sizeof(messTMP), 0, IPC_NOWAIT);
    if(res > 0)
      msq_message_print(messTMP);
  }
  msgctl(request, IPC_RMID, NULL);
  return 0;
}
