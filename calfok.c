#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/**
 * MaiN - main function
 * Return: 0
 */
int MaiN(void)
{
	pid_t pid = fork();
	const char *childMessage = "Hello from the child process!\n";
	const char *parentMessage = "Hello from the parent process!\n";

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		int childFileDescriptor = open("child_file.txt",
				O_CREAT | O_WRONLY | O_TRUNC,
				0644);


		if (childFileDescriptor == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		write(childFileDescriptor, childMessage, strlen(childMessage));

		close(childFileDescriptor);
		exit(EXIT_SUCCESS);
	}
	else
	{
		int parentFileDescriptor = open("parent_file.txt",
				O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		if (parentFileDescriptor == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		write(parentFileDescriptor, parentMessage, strlen(parentMessage));
		close(parentFileDescriptor);
		wait(NULL);
	}
	return (0);
}

