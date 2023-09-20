#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
void display_prompt()
{
printf("($) ");
}
int main()
{
char command[MAX_COMMAND_LENGTH];
while (1)
{
display_prompt();
/*Read the command from the user*/
if (fgets(command, sizeof(command), stdin) == NULL)
{
if (feof(stdin))
{
/* End of file (Ctrl+D)*/
printf("\n");
break;
}
else
{
perror("Error reading command");
exit(EXIT_FAILURE);
}
}
/* Remove the newline character*/
size_t len = strlen(command);
if (len > 0 && command[len - 1] == '\n')
{
command[len - 1] = '\0';
}
/* Execute the command*/
pid_t pid = fork();
if (pid == -1)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/*Child process*/
if (execlp(command, command, NULL) == -1)
{
printf("Command not found: %s\n", command);
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process*/
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status))
{
int exit_status = WEXITSTATUS(status);
if (exit_status != 0)
{
printf("Command failed with exit status: %d\n", exit_status);
}
}
else if (WIFSIGNALED(status))
{
printf("Command terminated abnormally\n");
}
}
}
return (0);
}
