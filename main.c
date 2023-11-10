#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
char **tokenizeString(const char *str, const char *delim, int num_tokens);
ssize_t readLine(char **lineptr, size_t *n);
char *copyString(const char *source);
int countTokens(const char *str, const char *delim);

void executeCommand(char **argv);
/**
 * readLine - Reads a line from stdin.
 * @lineptr: Pointer to the buffer
 * @n: Size of the buffer.
 * Return: ssize_t Number of characters read.
 */

ssize_t readLine(char **lineptr, size_t *n)
{
	ssize_t nochars_read = getline(lineptr, n, stdin);

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
 * @num_tokens: tokens Number of tokens in the string.
 * Return: char** Array of tokens.
 */
char **tokenizeString(const char *str, const char *delim, int num_tokens)
{
	char **tokens = malloc(sizeof(char *) * num_tokens);
	int i;
	char *token = strtok(copyString(str), delim);

	if (tokens == NULL)
	{
		perror("memo alloc error");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		tokens[i] = copyString(token);
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}


/**
 * execmd - Executes a command with arguments.
 * @argv: Array of command arguments.
*/
void execmd(char **argv);
{
	printf("Executing command...\n");
}


/**
 * main - main function
 * @ac: parameter 1
 * @argv: para 2
 * Return: 0
 */
int main(int ac, char **argv)
{
	ssize_t nochars_read;
	size_t n = 0;
	char *prompt = "shell";
	char *lineptr = NULL, *lineptr_copy = NULL;
	const char *delim = " \n";
	int num_tokens = countTokens(lineptr, delim);
        char **tokenized = tokenizeString(lineptr_copy, delim, num_tokens);
	(void)ac;

	for (;;)
	{
		nochars_read = readLine(&lineptr, &n);
		printf("%s", prompt);

		if (nochars_read == -1)
		{
			printf("shell exit...\n");
			return (-1);
		}
		lineptr_copy = copyString(lineptr);

		executeCommand(tokenized);


		free(lineptr_copy);

		free(tokenized);
	}
	free(lineptr);
	return (0);
}

