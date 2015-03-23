#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

static char* argv0;

static void
usage(void)
{
	fprintf(stderr, "usage: %s\n", argv0);
	exit(1);
}

static size_t
c_escape(char c, char out[static 5])
{
	int r;

	if (iscntrl(c) || !isascii(c))
		r = snprintf(out, 5, "\\x%02hhx", c);
	else {
		if (c == '\"' || c == '\\')
			r = snprintf(out, 5, "\\%c", c);
		else {
			out[0] = c;
			out[1] = '\0';
			r = 1;
		}
	}
	assert(r > 0 && r < 5);
	return (size_t)r;
}

static void
c_escape_concat(FILE* out, FILE* in)
{
	char buf[5];
	int c;

	while ((c = fgetc(in)) != EOF) {
		(void) c_escape((char)c, buf);
		if (fputs(buf, out) != 0)
			err(1, "fputs");
	}
}

int
main(int argc, char* argv[])
{
	argv0 = *argv, argv++, argc--;
	if (argc)
		usage();
	c_escape_concat(stdout, stdin);
	return 0;
}
