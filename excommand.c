#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * execute_command - Executes external commands.
 * @argv: Array of command and arguments.
 * Return: void
 */
void execute_command(char **argv)
{
	char *command_path = get_location(argv[0]);
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (command_path == NULL)
		{
			fprintf(stderr, "Command not found: %s\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		if (execv(command_path, argv) == -1)
		{
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status))
		{
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Child process terminated by signal %d\n", WTERMSIG(status));
		}
	}
}
