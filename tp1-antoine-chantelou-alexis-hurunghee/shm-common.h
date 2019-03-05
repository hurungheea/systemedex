#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include <stdarg.h>
#include <errno.h>
#include "shm-message.h"

#define CLIENT 1
#define SERVER 0

extern char* global_argv;

void waitingForEnter();
void displayError(void* t, ...);
void afficheVersion(char **argv);
void afficheHelp(char **argv, int client);
void checkSHMMessage(shm_message_t* message);
shm_message_t* getSHM(key_t* key, int* shmGetRes, int client);

#endif
