#include "shm-common.h"

void displayError(void* t,...)
{
  char* toPrint = NULL;
  va_list args;
  switch(errno)
  {
    case 2:
      toPrint = "%s:%s:%d: Unable to create the System V IPC key from the \"%s\" pathname and the \"%d\" project identifier.\n";
      break;

    case 22:
      toPrint = "%s:%s:%d: Unable to get the identifier of the System V shared memory segment from the \"0x%x\" key.\n";
      break;

    case 140:
      toPrint = "%s:%s:%d: Unable to copy the message because the target message is not empty.\n";
      break;

    case 150:
      toPrint = "%s:%s:%d: Unable to copy the message.\n";
      break;

    case 160:
      toPrint = "%s:%s:%d: Unable to set the \"%s\" message text because its \"%d\" is greater than \"64\".\n";
      break;

    case 170:
      toPrint = "%s:%s:%d: Unable to set the \"%s\" message name because its \"%d\" is greater than \"16\".\n";
      break;

    default:
      fprintf(stderr,"Unknown error : %d\n",errno);
      break;
  }
  va_start(args,t);
  vfprintf(stderr,toPrint,args);
  va_end(args);
  exit(1);
}

void checkSHMMessage(shm_message_t* message)
{
  if(!shm_message_is_empty(*message))
  {
    shm_message_print(*message);
    shm_message_empty(message);
  }
}

void waitingForEnter()
{
  char k;
  do
  {
    printf("Press the Enter key to continue... ");
    k = getchar();
  }while(k != 0x0A);
}

shm_message_t* getSHM(key_t* key, int* shmGetRes,int client)
{
  shm_message_t* message = NULL;
  if(client)
    *shmGetRes = shmget(*key,sizeof(shm_message_t),0);
  else
    *shmGetRes = shmget(*key,sizeof(shm_message_t),IPC_CREAT|IPC_EXCL|0600);
  message = (shm_message_t*) shmat(*shmGetRes,NULL,0);
  return message;
}

void afficheHelp(char **argv, int client)
{
  printf("Usage: %s [OPTION] ...\n",argv[0]);
  if(client)
    printf("Send a message to a server through shared memory.\n \n");
  else
    printf("Receive messages from clients through shared memory.\n \n");
  printf("Options:\n");
  printf("\t -h, --help\n\t\tdisplay this help and exit\n");
  printf("\t -i, --key-proj-id=PROJ_ID\n\t\tset the key project identifier to PROJ_ID (the default value is \"1\")\n");
  if(client)
    printf("\t -n, --message-name=NAME\n\t\tset the message name to NAME (the default value is \"Default name\")\n");
  printf("\t -p, --key-pathname=PATHNAME\n\t\tset the key pathname to PATHNAME (the default value is \"file.ftok\")\n");
  printf("\t -s, --seconds=SECONDS\n\t\tset the seconds between each try (the default value is \"1\"), a value less than or equal to 0 enables the interactive mode where the input stream is read\n");
  if(client)
    printf("\t -t, --times=TIMES\n\t\tset the number of times this program tries to receive a message (the default value is \"1\"),a negative value means repeat for ever\n");
  else
    printf("\t -t, --times=TIMES\n\t\tset the number of times this program tries to receive a message (the default value is \"-1\"),a negative value means repeat for ever\n");
  printf("\t -v, --version\n\t\t output version information and exit\n");
  if(client)
    printf("\t -x, --message-text=TEXT\n\t\tset the message text to TEXT (the default value is \"This is the default message text\")\n");
  printf("\nReport bugs to Antoine Chantelou <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>.\n");
  exit(0);
}

void afficheVersion(char **argv)
{
  printf("%s 1.0.0\n\n",argv[0]);
  printf("Copyright (C) 2019 Chantelou Antoine and Hurunghee Alexis\n\n");
  printf("Written by Chantelou Antoine <achantelou@etud.univ-pau.fr> and Alexis Hurunghee <ahurunchee@etud.univ-pau.fr>. \n");
  exit(0);
}
