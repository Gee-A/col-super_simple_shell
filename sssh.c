#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define BUFSIZE	256

char *_getline(void);
char **_strtok(char *str);
void sssh_loop(void);
int sssh_execute(char **argv);
/**
 * main - The very first super simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	/* load config files, if any */

	/* Run command loop on a different process created by the same */
	sssh_loop();

	return (0);

}
void sssh_loop(void)
{
	char *lineptr;
	char **argv;
	int status;

	do
	{
		status = 0;
		printf("#cisfun$ ");
		lineptr = _getline();
		argv = _strtok(lineptr);

		if (argv)
			status = sssh_execute(argv);

		free(lineptr);
		free(argv);
	} while (status);
}

char *_getline(void)
{
	int bufsize = BUFSIZE;
	int i = 0, c;
	char *buffer = malloc(sizeof(*buffer) * bufsize);

	while (1)
	{
		c = getchar(); 

		if (c == EOF || c == '\n')
		{
			buffer[i] = '\0';
			return (buffer);
		}
		else buffer[i] = c;
		i++;

		if (i >= bufsize)
		{
			bufsize += BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer)
			{
				dprintf(2, "%s\n", "reallocation error");
				exit(1);
			}
		}
	}
}

int count_lineword(char *str)
{
	int i, c, in, nw;

	i = in = nw = 0;
	while ((c = str[i]))
	{
		if (c == ' ' || c == '\t')
			in = 0;
		else if (!in)
		{
			in = 1;
			nw++;
		}
		i++;
	}
	return (nw);
}
int panic(char **strs, int row)
{
	if (strs)
	{
		while (row >= 0)
			free(strs[row--]);
		free(strs);
	}
	return (1);
}

char **_strtok(char *str)
{
	char **strs;
	int wc, s, c, i, j;

	if (str == NULL ||  *str == '\0')
		return (NULL);

	wc = count_lineword(str);
	strs = malloc(sizeof(char *) *wc);
	if (!strs)
		panic (strs, 0);

	wc = s = j = 0;
	for (i = 0; (c = str[i]); i++)
	{
		if (c == ' ' || c == '\t')
			s++;
		else
		{
			j++;
			if (str[i + 1] == '\0' || str[i + 1] == ' ')
			{
				strs[wc] = malloc(sizeof(char) * (j + 1));
				if (!strs[wc])
					panic(strs, wc);

				for (j = 0; s <= i; j++)
					strs[wc][j] = str[s++];
				strs[wc][j] = '\0';
				wc++;
				j = 0;
			}
		}
	}
	strs[wc] = NULL;
	return (strs);
}

int sssh_launch(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		perror("Error:");
	else if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
			perror("Error:");
	}
	else 
		wait(&status);

	return (1);
}

int sssh_execute(char **argv)
{
	if (argv == NULL)
		return (1);

	return (sssh_launch(argv));
}
