#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<getopt.h>
#include<unistd.h>
#include<sys/types.h>
#include "shm-message.h"
#include "shm-common.h"

char* global_argv;

int main(int argc, char *argv[])
{
  int opt = 0, option_index = 0, sec = 1, id = 1, times=1, daemon = 1,shmGetRes = 0;
  key_t key = 0;
  shm_message_t* message = NULL;
  char* pathname = "file.ftok";
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
        daemon = 0;
        times = strtol(optarg,NULL,10);
        break;
    }
  } while(opt != -1);

  printf("proj_id = \"%d\"\n",id);
  printf("pathname = \"%s\"\n",pathname);

  key = ftok(pathname,id);
  if(key == (key_t)-1)
    displayError(NULL,argv[0],__FILE__,__LINE__,pathname,id);

  message = getSHM(&key,&shmGetRes,SERVER);
  if(message == (void*)-1)
    displayError(NULL,argv[0],__FILE__,__LINE__,key);

  while(times)
  {
    if(sec == 0)
    {
      waitingForEnter();
    }
    else
    {
      sleep(sec);
      if(!daemon)
        times--;
    }
    checkSHMMessage(message);
  }
  shmctl(shmGetRes,IPC_RMID,NULL);
  return 0;
}
