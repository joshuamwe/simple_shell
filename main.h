#ifndef MAIN_H
#define MAIN_H
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
char *get_location(char *command);
int main(void);
ssize_t readLine(char **lineptr, size_t *n);
char *copyString(const char *source);
int countTokens(const char *str, const char *delim);
char **tokenizeString(const char *str, const char *delim, int *num_tokens);
void execmd(char **argv);
#endif
