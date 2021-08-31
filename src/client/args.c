#include "client/args.h"
#include <string.h>

// AC(short, long)
// Ex. AC("-p", "--port")
#define AC(s, l) (strcmp(argv[i], s) == 0 || strcmp(argv[i], l) == 0)

Arguments *Args_parse(int argc, char **argv) {
	argv0 = argv[0];

	Arguments *args = NULL;

	for(int i = 1; i < argc; ++i) {
		if(!args)
			args = malloc(sizeof(Arguments));

		if(AC("-p", "--port")) {
			i++;
			if(argc < i) {
				printf("Expected value for argument: %s\n", argv[i - 1]);
				return NULL;
			}
			args->port = atoi(argv[i]);

			if(args->port <= 1 || args->port >= 65535) {
				printf("Expected value between 1-65535 for argument: %s\n", argv[i - 1]);
				return NULL;
			}
			i++;
		} else if(AC("-i", "--identity")) {
			i++;
			if(argc < i) {
				printf("Expected value for argument: %s\n", argv[i - 1]);
				return NULL;
			}
			args->identity = argv[i];
			i++;
		} else {
			args->addr = argv[i];
		}
	}

	if(!args->identity)
		args->identity = "ExampleIdentity";

	return args;
}

void Args_printUsage() {
	printf("Usage: %s [options] <address>\n", argv0);
	printf("\n");
	printf("Options:\n");
	printf("  -p,--port <port>  Specify the port number. This must be a number between 1-65535.");
}

