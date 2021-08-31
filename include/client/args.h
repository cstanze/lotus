#ifndef LOTUS_CLIENT_ARGS_H
#define LOTUS_CLIENT_ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	int port;
	char *addr;
	char *identity;
} Arguments;

static char *argv0;

Arguments *Args_parse(int argc, char **argv);
void Args_printUsage();

#endif
