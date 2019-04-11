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
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include "pipe-message.h"

#define WRITTEN "written"
#define READ "   read"

void waitingForEnter();
void display_help(char **argv);
void display_error(void* t, ...);
void display_version(char **argv);
void argument_opt(int argc, char **argv, char* optOptions, int* option_index, int* id, char** pathname,int* sec, int* times_receive, pipe_message_t* messageTMP, int* times_sending, int* seconds_sending);

#endif
