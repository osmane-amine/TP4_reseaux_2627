CC = gcc
CFLAGS = -Wall -g
LDFLAGS= -L. # search current directory for library files
LIBS = -lseg # search for a library named libseg.a

all: client

#compile the client file linked with the libseg.a library
client: client.c segdef.h
	$(CC) $(CFLAGS) -o client client.c $(LDFLAGS) $(LIBS)

clean:
	rm -f client


