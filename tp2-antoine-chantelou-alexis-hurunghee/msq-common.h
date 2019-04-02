#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdarg.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include "msq-message.h"

#define CLIENT 1
#define SERVER 0

extern char* global_argv;



void waitingForEnter();
void displayError(void* t, ...);
void afficheVersion(char **argv);
void afficheHelp(char **argv, int client);
void argumentFromServer(int argc, char **argv, char* optOptions, int* option_index, int* id, char** pathname,int* sec, int* times);
void argumentFromClient(int argc, char **argv, char* optOptions, int* option_index, int* id, char** pathname,int* sec, int* times, msq_message_t* messTMP);

#endif
