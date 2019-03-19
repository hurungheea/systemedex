#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include  "msq-common.h"
#include  "msq-message.h"

char* global_argv;

int main(int argc, char *argv[])
{
  int opt = 0, option_index = 0,times=-1,sec = 1,id = 1,request,res;
  key_t key;
  char* pathname = "file.ftok";
  msq_message_t messTMP;
  static struct option long_options[] =
  {
    {"help", 0, NULL,'h'},
    {"key-proj-id", 1, NULL,'i'},
    {"key-pathname", 1, NULL,'p'},
    {"seconds", 1, NULL,'s'},
    {"times", 1, NULL,'t'},
    {"version", 1, NULL,'v'},
    {0, 0, 0, 0}
  };
  global_argv = malloc(sizeof(char) * strlen(argv[0]));
  global_argv = argv[0];
  do
  {
    opt = getopt_long(argc,argv,"hvi:p:s:t:",long_options,&option_index);
    switch(opt)
    {
      case 'h':
        afficheHelp(argv,SERVER);
        break;

      case 'v':
        afficheVersion(argv);
        break;

      case 'i':
        id  = strtol(optarg,NULL,10);
        break;

      case 'p':
        pathname = optarg;
        break;

      case 's':
          sec = strtol(optarg,NULL,10);
        break;

      case 't':
        times = strtol(optarg,NULL,10);
        break;
    }
  } while(opt != -1);

  printf("proj_id = \"%d\"\n",id);
  printf("pathname = \"%s\"\n",pathname);

  key = ftok(pathname,id);
  if(key == (key_t)-1)
    displayError(NULL,argv[0],__FILE__,__LINE__,pathname,id);

  request = msgget(key,IPC_CREAT|IPC_EXCL|0600);
  if(request == -1)
    displayError(NULL,argv[0],__FILE__,__LINE__,(int)key);

  while(times!=0)
  {
    if(sec == 0)
      waitingForEnter();
    else
      sleep(sec);
    if(times > 0)
      times--;
    res = msgrcv(request,&messTMP,sizeof(messTMP),0,IPC_NOWAIT);
    if(res > 0)
      msq_message_print(messTMP);
  }
  msgctl(request,IPC_RMID,NULL);
  return 0;
}
