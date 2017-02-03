CC     = gcc
CFLAGS = -I$(PWD)/libhash -g -MMD -MP -Werror
LFLAGS = -L$(PWD)/libhash -Wl,-rpath=$(PWD)/libhash
LIBS   = -lhash -lrt
OBJS   = main.o dclock.o
BIN    = a.out

.SUFFIXES: .c.o
.PHONY: clean

ALL: $(BIN)

$(LIBS):
	make -C libhash

.c.o:
	$(CC) -c $(CFLAGS) $<

$(BIN): $(OBJS) $(LIBS)
	$(CC) $(LFLAGS) $(LIBS) $^ -o $@

clean:
	rm -f *.o *.d *~ $(BIN)
	make -C libhash clean
