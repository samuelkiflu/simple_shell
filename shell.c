#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
void display_prompt()
{
	printf("SimpleShell$ ");
}
void execute_command(char *command)
{
	printf("Executing command: %s\n", command);
}
