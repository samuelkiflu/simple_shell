#include <stdio.h>
#include "shell.h"

int main(void)
{
	char *line;
	while (1)
	{
		printf("$ ");
		line = read_line();
		if (!line)
			break;
		if (*line)
		{
			execute_command(line);
		}
		free(line);
	}
	return (0);
}
