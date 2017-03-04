#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <libgen.h>
#include <getopt.h>
#include <stdbool.h>

const char *VERSION = "0.0.1";

void usage(char *program) {
	fprintf(stderr, "usage: %s [-hvx] ip4address...\n", basename(program));
	fprintf(stderr, "print ip address in decimal format\n");
	fprintf(stderr, "\t-h print this help message and exit\n");
	fprintf(stderr, "\t-v print version number and exit\n");
	fprintf(stderr, "\t-x ip4address\n\t\tprint ip address in hexadecimal format\n");
	exit(EXIT_FAILURE);
}

void version(char *program) {
	fprintf(stderr, "%s version %s\n", basename(program), VERSION);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	regex_t re;
	bool hex = false;
	uint8_t sect1, sect2, sect3, sect4 = 0;
	uint32_t result = 0;
	int opt = 0;

	if (argc < 2) {
		usage(argv[0]);
	}
	while ((opt = getopt(argc, argv, "vx")) != -1) {
		switch (opt) {
			case 'v':
				version(argv[0]);
			case 'x':
				hex = true;
				break;
			case '?':
			default:
				usage(argv[0]);
		}
	}
	if ((argc - optind) == 0) {
		 usage(argv[0]);
	}

	if (regcomp(&re, "([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})", REG_EXTENDED) != 0) {
		fprintf(stderr, "%s: error compiling regex\n", argv[0]);
		return EXIT_FAILURE;
	}

	for (; optind < argc; optind++) {
		if (regexec(&re, argv[optind], 0, NULL, 0) != 0) {
			usage(argv[0]);
		}
		sscanf(argv[optind], "%hhu.%hhu.%hhu.%hhu", &sect1, &sect2, &sect3, &sect4);
		result = (sect1 << 24) + (sect2 << 16) + (sect3 << 8) + sect4;
		if (hex) {
			printf("%#0x\n", result);
		} else {
			printf("%u\n", result);
		}
	}
	return EXIT_SUCCESS;
}
