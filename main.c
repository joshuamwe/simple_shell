#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int executeCommand(char **tokens);
char **tokenizeString(const char *str, const char *delim, int *num_tokens);
ssize_t readLine(char **lineptr, size_t *n);
char *copyString(const char *source);
int countTokens(const char *str, const char *delim);

/**
 * readLine - Reads a line from stdin.
 * @lineptr: Pointer to the buffer
 * @n: Size of the buffer.
 * Return: ssize_t Number of characters read.
 */
ssize_t readLine(char **lineptr, size_t *n)
{
	ssize_t nochars_read = getline(lineptr, n, stdin);

	if (nochars_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readLine error");
			exit(EXIT_FAILURE);
		}
	}
	return (nochars_read);
}

/**
 * copyString - Allocates memory
 * @source: String to be copied.
 * Return: char* Pointer to the newly allocated string.
 */
char *copyString(const char *source)
{
	char *copy = malloc(strlen(source) + 1);

	if (copy == NULL)
	{
		perror("memo alloc error");
		exit(EXIT_FAILURE);
	}

	strcpy(copy, source);
	return (copy);
}

/**
 * countTokens - counts the number of tokens.
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * Return: int Number of tokens.
 */
int countTokens(const char *str, const char *delim)
{
	char *strCopy = copyString(str);
	int num_tokens = 0;
	char *token = strtok(strCopy, delim);

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	free(strCopy);

	return (num_tokens);
}

/**
 * tokenizeString - Tokenizes a string and stores tokens
 * @str: String to be tokenized.
 * @delim: Delimiter used for tokenization.
 * @num_tokens: Pointer to the variable to store the number of tokens.
 * Return: char** Array of tokens.
 */
char **tokenizeString(const char *str, const char *delim, int *num_tokens)
{
	char **tokens;
	int i = 0;
	char *token;

	*num_tokens = 0;

	tokens = malloc(sizeof(char *));

	if (tokens == NULL)
	{
		perror("memo alloc error");
		exit(EXIT_FAILURE);
	}

	token = strtok(copyString(str), delim);

	while (token != NULL)
	{
		(*num_tokens)++;

		tokens = realloc(tokens, sizeof(char *) * (*num_tokens));

		if (tokens == NULL)
		{
			perror("memo alloc error");
			exit(EXIT_FAILURE);
		}

		tokens[i] = copyString(token);
		i++;
		token = strtok(NULL, delim);
	}

	free(tokens[(*num_tokens) - 1]);
	tokens[i - 1] = NULL;

	return (tokens);
}

/**
 * executeCommand - Executes the command
 * @tokens: Array of arguments.
 * Return: int Exit status of the command.
 */
int executeCommand(char **tokens)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(tokens[0], tokens) == -1)
		{
			perror("executeCommand error");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork error");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}

/**
 * main - main function
 * Return: 0
 */
int main(void)
{
	ssize_t nochars_read;
	size_t n = 0;
	char *prompt = "shell";
	char *lineptr = NULL, *lineptr_copy = NULL;
	const char *delim = " \n";
	int num_tokens;
	char **tokenized;
	int i;

	for (;;)
	{
		nochars_read = readLine(&lineptr, &n);
		printf("%s", prompt);

		if (nochars_read == -1)
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

		for (i = 0; i < num_tokens; i++)
		{
			free(tokenized[i]);
		}
		free(tokenized);
	}
	free(lineptr);
	return (0);
}

