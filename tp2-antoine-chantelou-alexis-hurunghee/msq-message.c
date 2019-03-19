#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "msq-common.h"
#include "msq-message.h"
/**
* Prints a message using the "YYYY-MM-DD HH:MM:SS: type: text" format.
* \param message The message.
*/
void msq_message_print(msq_message_t message)
{
  time_t temps;
  struct tm *t;

  temps = time(NULL);
  t = localtime(&temps);

  printf("%04d-%02d-%02d %02d:%02d:%02d : %ld: %s\n",t->tm_year + 1900, t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec,message.type,message.text);
}
/**
* Sets the text of a message.
* \param message The message.
* \param text The text.
* \return -1 on error (if the message text size is greater than MSQ_MESSAGE_TEXT_SIZE), else 0.
*/
int msq_message_set_text(msq_message_t *message, const char *text)
{
  if(strlen(text)>MSQ_MESSAGE_TEXT_SIZE)
  {
    errno = 510;
    return -1;
  }
  strcpy(message->text,text);
  return 0;
}
/**
* Sets the type of a message.
* \param message The message.
* \param type The type.
* \return -1 on error (if the message type value is less than or equal to 0), else 0.
*/
int msq_message_set_type(msq_message_t *message, long int type)
{
  if(type <= 0)
  {
    errno = 520;
    return -1;
  }
  message->type = type;
  return 0;
}
