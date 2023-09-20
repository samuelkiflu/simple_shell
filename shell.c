#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
}
void execute_command(char *command)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		/* Child process*/
		char *args[] = {command, NULL};
		execve(command, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/* Parent process */
		int status;
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}
