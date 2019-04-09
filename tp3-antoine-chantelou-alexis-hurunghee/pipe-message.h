/**
  * \file pipe-message.h
  */
#ifndef PIPE_MESSAGE_H
#define PIPE_MESSAGE_H
#include <sys/types.h> /* for pid_t */
/**
  * The size of the message text.
  */
#define PIPE_MESSAGE_TEXT_SIZE 64
/**
  * A message.
  */
typedef struct
{
  pid_t pid; /**< The process ID. */
  char text[PIPE_MESSAGE_TEXT_SIZE]; /**< The message text. */
} pipe_message_t;
/**
  * Prints a message using the "prefix: YYYY-MM-DD HH:MM:SS: pid: text" format.
  * \param message The message.
  * \param prefix The prefix.
  */
void pipe_message_print(pipe_message_t message, const char *prefix);
/**
  * Sets the text of a message.
  * \param message The message.
  * \param text The text.
  * \return -1 on error (if the message text size is greater than PIPE_MESSAGE_TEXT_SIZE), else 0.
  */
int pipe_message_set_text(pipe_message_t *message, const char *text);
  /**
  * Sets the process ID of a message.
  * \param message The message.
  * \param pid The process ID.
  * \return -1 on error (if the message pid value is less than 0), else 0.
  */
int pipe_message_set_pid(pipe_message_t *message, pid_t pid);
#endif
