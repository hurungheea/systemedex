#ifndef SHM_COMMON_H
#define SHM_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include "shm-message.h"

#define CLIENT 1
#define SERVER 0

void waitingForEnter();
void afficheVersion(char **argv);
void afficheHelp(char **argv, int client);
void checkSHMMessage(shm_message_t* message);
shm_message_t* getSHM(char *pathname, int* id, int* shmGetRes, int client);

#endif
