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
  int opt = 0, option_index = 0,times=1,sec = 0,id = 1,request,response = 0,res;
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
        afficheHelp(argv,0);
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
  msq_message_set_text(&messTMP,"i'm a fucking idiot");
  msq_message_set_type(&messTMP,1);


  printf("proj_id = \"%d\"\n",id);
  printf("pathname = \"%s\"\n",pathname);

  request = msgget(ftok(pathname,id),IPC_CREAT|0600);
  if(request == -1)
  {
    displayError(NULL);
  }

  response = msgget(ftok(pathname,id),IPC_CREAT|0600);
  if(response == -1)
  {
    displayError(NULL);
  }

  msq_message_print(messTMP);

  while(times!=0)
  {
    sleep(sec);
    res = msgsnd(request,&messTMP,MSQ_MESSAGE_TEXT_SIZE+1,0);
    if (res == -1)
    {
      printf("msgrcv");
    }
    if(times>0)
    {
      times--;
    }
  }

  return 0;
}
