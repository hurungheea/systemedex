/**
  * \file pipe-common.h
  */
#ifndef PIPE_COMMON_H
#define PIPE_COMMON_H

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "pipe-message.h"

#define WRITTEN "written"
#define READ "read"

void waitingForEnter();
void display_help(char **argv);
void display_error(void* t, ...);
void display_version(char **argv);
void call_my_son(pipe_message_t* message_tampon,int *pipefd);
void argument_opt(int argc, char **argv, char* optOptions, int* option_index, int* seconds_receiving, pipe_message_t* messageTMP, int* times_sending, int* seconds_sending, int* times_receiving);

#endif
