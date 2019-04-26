/**
  * \file pipe-common.h
  */
#ifndef PIPE_COMMON_H
#define PIPE_COMMON_H

#include <errno.h> /* for errno */
#include <stdio.h> /* for input/output */
#include <stdlib.h> /* for exit */
#include <unistd.h> /* for unix tricks */
#include <stdarg.h> /* for vfprintf */
#include <getopt.h> /* for getopt_long */
#include <string.h> /* for strings */
#include <sys/types.h> /* for pid_t */
#include "pipe-message.h" /* for pipe_message_t */
/**
  * The written string
  */
#define WRITTEN "written"
/**
  * The read string
  */
#define READ "read"
/**
  * Waiting until user press the enter key
  * \param rw for 'r'|'w'
  */
void waitingForEnter(char rw);
/**
  * Display the help of the program
  * \param argv is the name of the program
  */
void display_help(char **argv);
/**
  * display program's errors
  * \param t is a null pointer
  * \param ... is for the list of arguments
  */
void display_error(void* t, ...);
/**
  * Display the version of the program
  * \param argv is the name of the program
  */
void display_version(char **argv);
/**
  * Get arguments from the starting command
  * \param argc is the number of argument
  * \param argv is the argument string
  * \param opt_options needed for getopt_long function
  * \param option_index needed for getopt_long function
  * \param seconds_receiving for the receiving sleeps
  * \param message_tmp is the default message
  * \param seconds_receiving for the sending sleeps
  * \param times_sending is the number of message to send
  * \param seconds_sending for the sending sleeps
  * \param times_receiving is the number of message to receive
  */
void argument_opt(int argc, char **argv, char* opt_options, int* option_index, int* seconds_receiving, pipe_message_t* message_tmp, int* times_sending, int* seconds_sending, int* times_receiving);
#endif
