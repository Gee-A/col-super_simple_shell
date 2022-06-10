#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

char *_getline(void);
char **_strtok(char *str);
int path(void);

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	int i;
	struct stat st;

	if (ac < 2)
	{
		printf("Usage: %s path_to_file ...\n", av[0]);
		return (1);
	}
	i = 1;
	while (av[i])
	{
		printf("%s:", av[i]);
		if (stat(av[i], &st) == 0)
			printf(" FOUND\n");
		else
			printf(" NOT FOUND\n");
		i++;
	}

	/* Yet to run do-while loop for path process */
	do
	{
		i = path();
	} while (i);

	return (0);
}

int path(void)
{
	int i = 0;
	char *lineptr;
	char **argv;
	struct stat st;

	printf("#cisfun$: ");

	lineptr = _getline();
	argv = _strtok(lineptr);

	while (argv[i])
		i++;

	if (i < 2 || strcmp(argv[0], "_which"))
	{
		printf("Usage: _which filename ...\n");
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		printf("%s: ", argv[i]);
		if (stat(argv[i], &st) == 0)
			printf("FOUND\n");
		else printf("NOT FOUND\n");
		i++;
	}
	return (i);
}

char *_getline(void)
{
	char *lineptr;
	size_t bufsize = 0;

	if (getline(&lineptr, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(0);
		else
			exit(1);
	}
	return (lineptr);
}
char **_strtok(char *str)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (!tokens)
	{
		dprintf(STDERR_FILENO, "%s\n", "Allocation error");
		exit(1);
	}
	token = strtok(str, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[i++] = token;

		if(i <= bufsize)
		{
			bufsize *= 2;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				dprintf(STDERR_FILENO, "%s\n", "Reallocation error");
				exit(1); // I ought to free the buffer
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[i] = NULL;
	return (tokens);
}
