CC = gcc
gflags = -Wall -Werror -D_GNU_SOURCE
version = -std=c89 -pedantic
exec = msq-client.out
exes = msq-server.out

all: $(exec) $(exes)

$(exes): msq-server.c msq-common.o msq-message.o
	$(CC) $(version) $(gflags) -g -o $(exes) msq-server.c msq-common.o msq-message.o

$(exec): msq-client.c  msq-common.o msq-message.o
	$(CC) $(version) $(gflags) -g -o $(exec) msq-client.c msq-common.o msq-message.o

msq-message.o: msq-message.c
	$(CC) $(version) $(gflags) -g -c -o msq-message.o msq-message.c

msq-common.o: msq-common.c
	$(CC) $(version) $(gflags) -g -c -o msq-common.o msq-common.c

clean:
	rm -f *.o

mrproper:
	rm -f toto.tok
	rm -f $(exec) $(exes)
	rm -f *.o
