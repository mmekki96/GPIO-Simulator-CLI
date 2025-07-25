#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cli.h"

char** commands;

char** CLI (char input[]) {
	commands = (char**)malloc(8 * sizeof(char*));
	int num_token = 0;
	input[strcspn(input, "\n")] = '\0';
	char* token = strtok(input, " ");
	while (token != NULL) {
		commands[num_token++] = strdup(token);
		token = strtok(NULL, " ");
	}
	commands[num_token] = NULL;
	if (num_token == 0)
		return NULL;
	else
		return commands;
}

int getCliArg (char** cmd) {
	int i = 0;
	while (cmd[i] != NULL)
		i++;
	return i;
}

void free_tokens (char** tokens) {
	int num_token = getCliArg(tokens);
	for (int i=0; i<num_token; i++)
		free(tokens[i]);

	free(tokens);
}

