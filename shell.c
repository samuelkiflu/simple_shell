#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 1024
void display_prompt()
{
printf("simple_shell $ ");
}
void execute_command(char *command)
{
char *args[] = {command, NULL};
if(execvp(command, args) == -1)
{
perror("simple_shell");
}
}
int main()
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
display_prompt();
if (fgets(command, sizeof(command), stdin) == NULL)
{
printf("\n");
break;
}
size_t len = strlen(command);
if (len > 0 && command[len - 1] == '\n')
{
command[len - 1] = '\0';
}
if (strcmp(command, "exit") == 0)
{
break;
}
pid_t pid = fork();
if (pid < 0)
{
perror("simple_shell");
}
else if (pid == 0)
{
execute_command(command);
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
return (0);
}
