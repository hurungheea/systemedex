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
    int opt = 0, option_index = 0, sec = 1, id = 1, time=1, daemon = 1,shmGetRes = 0;
    char* pathname = "file.ftok";
    shm_message_t messageTMP;
    shm_message_t* messSHM = NULL;
    static struct option long_options[] =
    {
      {"help", 0, NULL,'h'},
      {"key-proj-id=", 1, NULL,'i'},
      {"key-pathname=", 1, NULL,'p'},
      {"seconds=", 1, NULL,'s'},
      {"times=", 1, NULL,'t'},
      {"version", 1, NULL,'v'},
      {"message-name=", 1, NULL,'n'},
      {"message-text=", 1, NULL,'x'},
      {0, 0, 0, 0}
    };

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
      strcpy(pathname,optarg);
      break;

      case 's':
      sec = strtol(optarg,NULL,10);
      break;

      case 't':
      daemon = 0;
      time = strtol(optarg,NULL,10);
      break;

      case 'n':
      shm_message_set_name(&messageTMP,optarg);
      break;

      case 'x':
      shm_message_set_text(&messageTMP,optarg);
      break;

      default:
        shm_message_empty(&messageTMP);
        break;
    }
  } while(opt != -1);

    printf("proj_id = \"%d\"\n",id);
    printf("pathname = \"%s\"\n",pathname);

    messSHM = getSHM(pathname,&id,&shmGetRes,CLIENT);
    if(messSHM   == (void*)-1) /* Si SHMAT return -1 */
    {
      printf("pas d'addr SHM\n");
      shmctl(shmGetRes,IPC_RMID,NULL);
      exit(1);
    }

    shm_message_copy(messageTMP, messSHM);

    while(time)
    {
      sleep(sec);
      if(!daemon)
        time--;

    }
    shmctl(shmGetRes,IPC_RMID,NULL);
    return 0;
}
