#include <stdlib.h>
#include <sys/wait.h>
#include "main.h"

pid_t execute_command(char **argv);
void wait_for_child(pid_t child_pid, int *exit_status);

/**
 * execmd - main function
 * @argv: argument
 * Return: void
 */
void execmd(char **argv)
{
	pid_t child_pid;
	int exit_status;
	int exit_code = WEXITSTATUS(exit_status);

	if (!argv)
	{
		fprintf(stderr, "Error: No command provided\n");
		return;
	}
	child_pid = execute_command(argv);
	wait_for_child(child_pid, &exit_status);

	if (WIFEXITED(exit_status))
	{
		printf("Child process exited with status %d\n", exit_code);
	}
	else
	{
		fprintf(stderr, "Child process did not exit normally\n");
	}
}

/**
 * execute_command - Execute the command in a child process
 * @argv: Argument vector for the command
 * Return: PID of the child process
 */
pid_t execute_command(char **argv)
{
	pid_t child_pid;
	int exit_status;
	char *command = argv[0];
	char *actual_command = get_location(command);

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (actual_command == NULL)
		{
			perror("Error:");
			_exit(EXIT_FAILURE);
		}
		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error:");
			_exit(EXIT_FAILURE);
		}

		free(actual_command);
	}
	if (waitpid(child_pid, &exit_status, 0) == -1)
	{
		perror("waitpid error");
		exit(EXIT_FAILURE);
	}
	return (child_pid);
}

/**
 * wait_for_child - Wait for the child process to complete
 * @child_pid: PID of the child process
 * @exit_status: Pointer to the variable where the exit status will be stored
 */
void wait_for_child(pid_t child_pid, int *exit_status)
{
	if (waitpid(child_pid, exit_status, 0) == -1)
	{
		perror("waitpid error");
		exit(EXIT_FAILURE);
}
}

