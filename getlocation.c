#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
/**
 * get_location - main function
 * @command: parameter 1
 * Return: NULL
 */
char *get_location(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length;
	struct stat buffer;

	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);

		if (!path_copy)
		{
			perror("strdup");
			return (NULL);
		}

		command_length = strlen(command);

		for (path_token = strtok(path_copy, ":"); path_token != NULL; path_token = strtok(NULL, ":"))
		{
			int directory_length = strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);

			if (!file_path)
			{
				perror("malloc");

				free(path_copy);
				return (NULL);
			}

			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);

			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
			}
		}
		free(path_copy);

		if (stat(command, &buffer) == 0)
		{
			return (strdup(command));
		}
	}

	return (NULL);
}

