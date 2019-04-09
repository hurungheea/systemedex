#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "pipe-message.h"
#include "pipe-common.h"
/**
  * Prints a message using the "prefix: YYYY-MM-DD HH:MM:SS: pid: text" format.
  * \param message The message.
  * \param prefix The prefix.
  */
void pipe_message_print(pipe_message_t message, const char *prefix)
{
  time_t temps;
  struct tm *t;

  temps = time(NULL);
  t = localtime(&temps);

  printf("%s: %04d-%02d-%02d %02d:%02d:%02d: %d: %s\n",prefix,t->tm_year + 1900,  t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,message.pid,message.text);
}
/**
  * Sets the text of a message.
  * \param message The message.
  * \param text The text.
  * \return -1 on error (if the message text size is greater than PIPE_MESSAGE_TEXT_SIZE), else 0.
  */
int pipe_message_set_text(pipe_message_t *message, const char *text)
{
  if(strlen(text) + 1 > PIPE_MESSAGE_TEXT_SIZE)
  {
    errno = 510;
    display_error(NULL, "./pipe-main.out", __FILE__, __LINE__, text, strlen(text) + 1,PIPE_MESSAGE_TEXT_SIZE);
    return -1;
  }
  strcpy(message->text,text);
  return 0;
}
  /**
  * Sets the process ID of a message.
  * \param message The message.
  * \param pid The process ID.
  * \return -1 on error (if the message pid value is less than 0), else 0.
  */
int pipe_message_set_pid(pipe_message_t *message, pid_t pid)
{
  if(pid <= (pid_t) 0)
    return -1;
  message->pid = (pid_t)pid;
  return 0;
}
