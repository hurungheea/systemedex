#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include <stdarg.h>
#include <errno.h>
#include "msq-message.h"

#define CLIENT 1
#define SERVER 0

extern char* global_argv;



void waitingForEnter();
void displayError(void* t, ...);
int getMsg(key_t key,int client);
void afficheVersion(char **argv);
void afficheHelp(char **argv, int client);


#endif
