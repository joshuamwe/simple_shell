#include "main.h"
#include <stdlib.h>

/**
 * execmd - main function
 * @argv: argument
 * Return: void
 */
void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv)
	{
		command = argv[0];
		actual_command = get_location(command);

		if (actual_command == NULL)
		{
			perror("Error:");
			return;
		}

		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error:");
		}
		free(actual_command);
	}
}

