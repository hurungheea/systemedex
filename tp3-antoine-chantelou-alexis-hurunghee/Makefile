CC = gcc
gflags = -Wall -Werror -D_GNU_SOURCE
version = -std=c89 -pedantic
exec = pipe-main.out

all: $(exec)

$(exec): pipe-main.c  pipe-common.o pipe-message.o
	$(CC) $(version) $(gflags) -g -o $(exec) pipe-main.c pipe-common.o pipe-message.o

pipe-message.o: pipe-message.c
	$(CC) $(version) $(gflags) -g -c -o pipe-message.o pipe-message.c

pipe-common.o: pipe-common.c
	$(CC) $(version) $(gflags) -g -c -o pipe-common.o pipe-common.c

clean:
	rm -f *.o

mrproper:
	rm -f $(exec) *.o
