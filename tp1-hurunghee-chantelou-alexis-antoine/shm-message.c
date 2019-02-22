#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shm-common.h"
#include "shm-message.h"

char* global_argv;

int shm_message_set_name(shm_message_t *message, const char *name)
{
  if((strlen(name)) > SHM_MESSAGE_NAME_SIZE)
  {
    errno = 170;
    displayError(NULL,global_argv,__FILE__,__LINE__,message->name,strlen(message->name));
    return -1;
  }else
  strcpy(message->name, name);
  return 0;
}

void shm_message_print(shm_message_t message)
{
  time_t temps;
  struct tm *t;

  temps = time(NULL);
  t = localtime(&temps);

  printf("%d-%d-%d %d:%d:%d : %s : %s\n",t->tm_year + 1900, t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,message.name,message.text);
}

void shm_message_empty(shm_message_t *message)
{
  message->text[0] = '\0';
  message->name[0] = '\0';
}

int shm_message_set_text(shm_message_t *message, const char *text)
{
  if(strlen(text) > SHM_MESSAGE_TEXT_SIZE)
  {
    displayError(NULL,global_argv[0],__FILE__,__LINE__,message->text,strlen(message->text));
    return -1;
  }
  strcpy(message->text,text);
  return 0;
}

int shm_message_copy(shm_message_t message_source, shm_message_t* message_target)
{
  if(shm_message_is_empty(message_source)==-1)
  {
    errno = 142;
    return -1;
  }
  else if((shm_message_set_name(message_target,message_source.name) == 0)&&(shm_message_set_text(message_target,message_source.text) == 0))
    return 0;
  else
    return -1;
}

int shm_message_is_empty(shm_message_t message)
{
  return ((strlen(message.text)>0) && (strlen(message.name)>0)) ? 0 : 1;
}
