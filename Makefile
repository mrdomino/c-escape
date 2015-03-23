all: c-escape
include config.mk

c-escape: c-escape.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o c-escape c-escape.o

c-escape.o: c-escape.c
	$(CC) $(CFLAGS) -c c-escape.c

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f c-escape $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/c-escape

clean:
	rm -f c-escape{,.o}
