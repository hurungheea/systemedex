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

int main(int argc, char *argv[])
{
    int opt = 0, option_index = 0, sec = 1, id = 1, times=0, daemon = 1,shmGetRes = 0;
    key_t key = 0;
    char* pathname = "file.ftok";
    shm_message_t messageTMP;
    shm_message_t* messSHM = NULL;
    static struct option long_options[] =
    {
      {"help", 0, NULL,'h'},
      {"key-proj-id", 1, NULL,'i'},
      {"key-pathname", 1, NULL,'p'},
      {"seconds", 1, NULL,'s'},
      {"times", 1, NULL,'t'},
      {"version", 1, NULL,'v'},
      {"message-name", 1, NULL,'n'},
      {"message-text", 1, NULL,'x'},
      {0, 0, 0, 0}
    };
    shm_message_set_name(&messageTMP,"Default name");
    shm_message_set_text(&messageTMP,"This is the default message text");
  do
  {
    opt = getopt_long(argc,argv,"hvi:p:s:t:x:n:",long_options,&option_index);
    switch(opt)
    {
      case 'h':
        afficheHelp(argv,1);
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

      case 'n':
        shm_message_set_name(&messageTMP,optarg);
        break;

      case 'x':
        shm_message_set_text(&messageTMP,optarg);
        break;

      default:
        /*  */
        break;
    }
  } while(opt != -1);

    printf("proj_id = \"%d\"\n",id);
    printf("pathname = \"%s\"\n",pathname);

    key = ftok(pathname,id);
    if(key == (key_t)-1)
      displayError(NULL,argv[0],__FILE__,__LINE__,pathname,id);

    messSHM = getSHM(&key,&shmGetRes,CLIENT);
    if(messSHM == (void*)-1)
      displayError(NULL,argv[0],__FILE__,__LINE__,key);

    shm_message_copy(messageTMP,messSHM);
    shm_message_print(messageTMP);

    while(times)
    {
      if(shm_message_copy(messageTMP,messSHM)!=0)
        displayError(NULL,argv[0],__FILE__,__LINE__);

      shm_message_print(messageTMP);
      if(times == 0)
        break;
      if(!daemon)
        times--;
      if(sec == 0)
      {
        daemon = 0;
        waitingForEnter();
      }
      else
      {
        sleep(sec);
      }
    }
    return 0;
}
