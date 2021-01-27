include ../beegfs-conf.sh

CC=gcc
CXX=g++
CFLAGS?=-I${CONF_LEVELDB_INCLUDEPATH} -Wall -Wextra -pedantic -std=gnu99 -g -Os
LDFLAGS?=-L${CONF_LEVELDB_LIBPATH}
SOURCES=perf.c filelist-runner.c getentry-runner.c bp-cm-query.c
OBJECTS=$(SOURCES:.c=.o)
PROGRAMS=bp-cm-filelist bp-cm-getentry bp-cm-query bp-chunkmap-create bp-chunkmap-query

all: $(PROGRAMS)
	cp -f ../beegfs-conf.sh ../../bin/

clean:
	rm -f ${OBJECTS}
	cd ../../bin/ && rm -f ${PROGRAMS}

%.o: %.c Makefile
	$(CC) -c $(CFLAGS) $(CFLAGS) $< -o $@

bp-cm-query: bp-cm-query.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lleveldb -lpthread
	mv -f $@ ../../bin/

bp-cm-filelist: filelist-runner.o
	$(CC) $(LDFLAGS) $^ -o $@ -lpthread
	mv -f $@ ../../bin/

bp-cm-getentry: perf.o getentry-runner.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lpthread -lleveldb
	mv -f $@ ../../bin/

bp-chunkmap-create: beegfs-chunkmap-create.sh
	cp -f $^ $@
	mv -f $@ ../../bin/

bp-chunkmap-query: beegfs-chunkmap-query.sh
	cp -f $^ $@
	mv -f $@ ../../bin/
