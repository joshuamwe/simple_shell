#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **tokenize_string(const char *str, const char *delim, int *num_tokens);
ssize_t read_line(char **lineptr, size_t *n);
char *copy_string(const char *source);
int count_tokens(const char *str, const char *delim);
void print_environment(void);
int execute_command(char **tokens);
/**
 * read_line - Reads a line from stdin.
 * @lineptr: Pointer to the buffer
 * @n: Size of the buffer.
 * Return: ssize_t Number of characters read.
 */
ssize_t read_line(char **lineptr, size_t *n)
{
	ssize_t no_chars_read = getline(lineptr, n, stdin);

	if (no_chars_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("read_line error");
			exit(EXIT_FAILURE);
		}
	}
	return (no_chars_read);
}

/**
 * copy_string - Allocates memory
 * @source: String to be copied.
 * Return: char* Pointer to the newly allocated string.
 */
char *copy_string(const char *source)
{
	char *copy = malloc(strlen(source) + 1);

	if (copy == NULL)
	{
		perror("memory allocation error");
		exit(EXIT_FAILURE);
	}

	strcpy(copy, source);
	return (copy);
}

/**
 * count_tokens - counts the number of tokens.
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * Return: int Number of tokens.
 */
int count_tokens(const char *str, const char *delim)
{
	char *str_copy = copy_string(str);
	int num_tokens = 0;
	char *token = strtok(str_copy, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	free(str_copy);

	return (num_tokens);
}

/**
 * tokenize_string - Tokenizes a string and stores tokens
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * @num_tokens: Pointer to the variable to store the number of tokens.
 * Return: char** Array of tokens.
 */
char **tokenize_string(const char *str, const char *delim, int *num_tokens)
{
	char **tokens;
	int i = 0;
	char *token;

	*num_tokens = 0;

	tokens = malloc(sizeof(char *));

	*tokens = NULL;

	if (tokens == NULL)
	{
		perror("memory allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(copy_string(str), delim);

	while (token != NULL)
	{
		(*num_tokens)++;

		tokens = realloc(tokens, sizeof(char *) * (*num_tokens));

		if (tokens == NULL)
		{
			perror("memory allocation error");
			exit(EXIT_FAILURE);
		}
		tokens[i] = copy_string(token);
		i++;
		token = strtok(NULL, delim);
	}
	free(tokens[(*num_tokens) - 1]);
	tokens[i] = NULL;

	return (tokens);
}
/**
 * execute_command - main
 * @tokens: para
 * Return: child_pid
 */
int execute_command(char **tokens)
{
	pid_t child_pid;
	char *command = tokens[0];
	int wait_status;
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
		if (execve(actual_command, tokens, NULL) == -1)
		{
			perror("Error:");
			_exit(EXIT_FAILURE);
		}
		free(actual_command);
	}
	if (waitpid(child_pid, &wait_status, 0) == -1)
	{
		perror("waitpid error");
		exit(EXIT_FAILURE);
	}
	return (child_pid);
}

/**
 * print_environment - Prints the current environment.
 */
void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * main - main function
 * Return: 0
 */
int main(void)
{
	ssize_t no_chars_read;
	size_t n = 0;
	char *prompt = "shell";
	char *lineptr = NULL, *lineptr_copy = NULL;
	const char *delim = " \n";
	int num_tokens;
	char **tokenized;
	int i;
	long int value;
	char *endptr;

	for (;;)
	{
		printf("%s", prompt);
		no_chars_read = readLine(&lineptr, &n);

		if (no_chars_read == -1)

		{
			printf("shell exit...\n");
			break;
		}

		lineptr_copy = copyString(lineptr);

		tokenized = tokenizeString(lineptr_copy, delim, &num_tokens);

		free(lineptr_copy);

		if (num_tokens > 0 && strcmp(tokenized[0], "exit") == 0)
		{
			printf("Exiting shell...\n");
			break;
		}
		else if (num_tokens > 0 && strcmp(tokenized[0], "cd") == 0)
		{
			if (num_tokens > 1)
			{
				value = strtol(tokenized[1], &endptr, 10);

				if (*endptr == '\0')
				{
					if (chdir(tokenized[1]) != 0)
					{
						perror("chdir error");
					}
				}
				else
				{
					fprintf(stderr, "cd: invalid argument\n");
				}
			}
			else
			{
				fprintf(stderr, "cd: missing argument\n");
			}
		}
		else if (num_tokens > 0 && strcmp(tokenized[0], "env") == 0)
		{
			print_environment();
		}
		else
		{
			execute_command(tokenized);
		}

		for (i = 0; i < num_tokens; i++)
		{
			free(tokenized[i]);
		}
		free(tokenized);
	}
	free(lineptr);
	return (0);
}

