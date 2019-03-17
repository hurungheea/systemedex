/**
* \file msq-message.h
*/
#ifndef MSQ_MESSAGE_H
#define MSQ_MESSAGE_H
/**
* The size of the message text.
*/
#define MSQ_MESSAGE_TEXT_SIZE 64
/**
* A message.
*/
typedef struct
{
  long type; /**< The message type. */
  char text[MSQ_MESSAGE_TEXT_SIZE]; /**< The message text. */
} msq_message_t;
/**
* Prints a message using the "YYYY-MM-DD HH:MM:SS: type: text" format.
* \param message The message.
*/
void msq_message_print(msq_message_t message);
/**
* Sets the text of a message.
* \param message The message.
* \param text The text.
* \return -1 on error (if the message text size is greater than MSQ_MESSAGE_TEXT_SIZE), else 0.
*/
int msq_message_set_text(msq_message_t *message, const char *text);
/**
* Sets the type of a message.
* \param message The message.
* \param type The type.
* \return -1 on error (if the message type value is less than or equal to 0), else 0.
*/
int msq_message_set_type(msq_message_t *message, long int type);
#endif
