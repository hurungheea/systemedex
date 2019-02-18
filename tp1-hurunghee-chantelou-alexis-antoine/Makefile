CC = gcc
gflags = -Wall -Werror -D_GNU_SOURCE
version = -std=c89 -pedantic
exec = shm-client.out
exes = shm-server.out

all: $(exes) $(exec)

$(exes): shm-common.o shm-message.o
	$(CC) $(version) $(gflags) -g -o $(exes) shm-server.c shm-common.o shm-message.o

$(exec): shm-message.o shm-common.o
	$(CC) $(version) $(gflags) -g -o $(exec) shm-client.c shm-common.o shm-message.o

shm-message.o:
	$(CC) $(version) $(gflags) -g -c -o shm-message.o shm-message.c

shm-common.o:
	$(CC) $(version) $(gflags) -g -c -o shm-common.o shm-common.c

clean:
	rm -f *.o

mrproper:
	rm -fr $(exec) $(exes)
	rm -f *.o
