#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

typedef const char* (*strfn)(char c);

static char* argv0;

static void
usage(void)
{
	fprintf(stderr, "usage: %s\n", argv0);
	exit(1);
}

static const char*
c_escape(char c)
{
	static char buf[5];

	if (iscntrl(c) || !isascii(c) || c == '\"' || c == '\\')
		(void) snprintf(buf, 5, "\\x%02hhx", c);
	else
		buf[0] = c, buf[1] = '\0';
	return buf;
}

static void
interact(FILE* out, FILE* in, strfn go)
{
	int c;

	while ((c = fgetc(in)) != EOF)
		if (fputs(go((char)c), out) == EOF)
			err(1, "fputs");
	if (ferror(in))
		err(1, "fgetc");
}

int
main(int argc, char* argv[])
{
	argv0 = *argv, argv++, argc--;
	if (argc)
		usage();
	interact(stdout, stdin, c_escape);
	return 0;
}
