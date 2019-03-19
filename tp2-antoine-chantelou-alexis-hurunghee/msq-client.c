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
  int opt = 0, option_index = 0,id = 1,requests,sec = 1,times = 1;
  char* pathname = "file.ftok";
  key_t key;
  msq_message_t messTMP;
  static struct option long_options[] =
  {
    {"help", 0, NULL,'h'},
    {"key-proj-id", 1, NULL,'i'},
    {"key-pathname", 1, NULL,'p'},
    {"seconds", 1, NULL,'s'},
    {"times", 1, NULL,'t'},
    {"version", 1, NULL,'v'},
    {"message-text", 1, NULL,'x'},
    {"message-type", 1, NULL,'y'},
    {0, 0, 0, 0}
  };
  global_argv = malloc(sizeof(char) * strlen(argv[0]));
  global_argv = argv[0];
  msq_message_set_text(&messTMP,"This is the default message text");
  msq_message_set_type(&messTMP,1);
  do
  {
    opt = getopt_long(argc,argv,"hvi:p:s:t:x:y:",long_options,&option_index);
    switch(opt)
    {
      case 'h':
        afficheHelp(argv,CLIENT);
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

      case 'x':
        if(msq_message_set_text(&messTMP,optarg) == -1)
          displayError(NULL,argv[0],__FILE__,__LINE__,optarg,strlen(optarg),MSQ_MESSAGE_TEXT_SIZE);
        break;

      case 'y':
        if(msq_message_set_type(&messTMP,strtol(optarg,NULL,10)) == -1)
          displayError(NULL,argv[0],__FILE__,__LINE__,strtol(optarg,NULL,10));
        break;

      case '?':
          exit(1);
        break;
    }
  } while(opt != -1);


  printf("proj_id = \"%d\"\n",id);
  printf("pathname = \"%s\"\n",pathname);

  key = ftok(pathname,id);
  if(key == (key_t)-1)
    displayError(NULL,argv[0],__FILE__,__LINE__,pathname,id);

  requests = msgget(key,0);
  if(requests == -1)
  {
    errno = 17;
    displayError(NULL,argv[0],__FILE__,__LINE__,pathname,id);
  }

  while(times > 0)
  {
    if(sec == 0)
      waitingForEnter();
    else
    {
      if(times > 1)
        sleep(sec);
      msgsnd(requests,&messTMP,sizeof(messTMP),0);
      msq_message_print(messTMP);
    }
    if(times > 0)
      times--;
  }
  return 0;
}
