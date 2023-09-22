#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	while (1)
	{
		display_prompt();
		if (getline(&input, &len, stdin) == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		input[strcspn(input, "\n")] = '\0';
		execute_command(input);
		free(input);
		input = NULL;
		len = 0;
	}
	return (0);
}
