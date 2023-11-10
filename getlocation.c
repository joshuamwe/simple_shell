#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *strdup_checked(const char *str);
char *build_file_path(const char *directory, const char *command);
int file_exists(const char *file_path, struct stat *buffer);
char *search_in_path(const char *path_copy, const char *command);
/**
 * Duplicate a string and check for errors
 * @str: parameter
 * Return: duplicate
 */
char *strdup_checked(const char *str)
{
	char *duplicate = strdup(str);

	if (!duplicate)
	{
		perror("strdup");
	}

	return (duplicate);
}

/**
 * build_file_path - main function
 * @directory: parameter 1
 * @command: parameter 2
 * Return: 0
 */
char *build_file_path(const char *directory, const char *command)
{
	int directory_length = strlen(directory);
	int command_length = strlen(command);

	char *file_path = malloc(directory_length + command_length + 2);

	if (!file_path)
	{
		perror("malloc");

		return (NULL);
	}

	strcpy(file_path, directory);
	strcat(file_path, "/");
	strcat(file_path, command);

	return (file_path);
}

/**
 * file_exists - Check if a file exists at the given path
 * @file_path: parameter 1
 * @buffer: parameter 2
 * Return: 0
 */
int file_exists(const char *file_path, struct stat *buffer)
{
	return (stat(file_path, buffer) == 0);
}

/**
 * search_in_path -Search location of a command in PATH
 * @path_copy: paramet 1
 * @command: para 2
 * Return: NULL
 */
char *search_in_path(const char *path_copy, const char *command)
{
	char *path_token;
	char *file_path;
	for (path_token = strtok(strdup_checked(path_copy), ":"); path_token != NULL; path_token = strtok(NULL, ":"))
	{
		file_path = build_file_path(path_token, command);

		if (!file_path)
		{
			return (NULL);
		}

		if (file_exists(file_path, NULL))
		{
			return (file_path);
		}
		else
		{
			free(file_path);
		}
	}
	return (NULL);
}

/**
 * Main function to get the location of a command
 */
char *get_location(char *command) {
    char *path = getenv("PATH");

    if (path) {
        char *path_copy = strdup_checked(path);

        if (!path_copy) {
            return NULL;
        }

        char *result = search_in_path(path_copy, command);

        free(path_copy);

        if (result) {
            return result;
        }
        struct stat buffer;

        if (file_exists(command, &buffer)) {
            return strdup_checked(command);
        }
    }

    return NULL;
}

