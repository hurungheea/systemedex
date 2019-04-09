/**
  * \file pipe-common.h
  */
#ifndef PIPE_COMMON_H
#define PIPE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdarg.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

void display_help(char **argv);
void display_error(void* t, ...);
void display_version(char **argv);
void argument_opt(int argc, char **argv, char* optOptions, int* option_index, int* id, char** pathname,int* sec, int* times);

#endif
