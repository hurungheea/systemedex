CC = gcc
gflags = -Wall -Werror -D_GNU_SOURCE
version = -std=c89 -pedantic
exec = shm-client.out
exes = shm-server.out

all: $(exec) $(exes)

$(exes): shm-server.c shm-common.o shm-message.o
	$(CC) $(version) $(gflags) -g -o $(exes) shm-server.c shm-common.o shm-message.o

$(exec): shm-client.c  shm-common.o shm-message.o
	$(CC) $(version) $(gflags) -g -o $(exec) shm-client.c shm-common.o shm-message.o

shm-message.o: shm-message.c
	$(CC) $(version) $(gflags) -g -c -o shm-message.o shm-message.c

shm-common.o: shm-common.c
	$(CC) $(version) $(gflags) -g -c -o shm-common.o shm-common.c

clean:
	rm -f *.o

mrproper:
	rm -f toto.tok
	rm -f $(exec) $(exes)
	rm -f *.o
