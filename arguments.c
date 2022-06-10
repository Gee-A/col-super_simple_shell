#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

char *_getline(void);
int count_lineword(char *str);
char **strtow(char *str);
/**
 * main - takes arguments
 *
 * @ac: number of argument(includes command)
 * @av: a NULL terminated array of strings
 * Return: Always 0
 */
int main(int __attribute__((__unused__)) ac, char **av)
{
	int i;
	char *lineptr;
	char **strs;

	for (i = 0; av[i]; i++)
		printf("%s\n", av[i]);

	printf("\n$ ");
	lineptr = _getline();
	printf("%s\n", lineptr);

	strs = strtow(lineptr);
	for (i = 0; strs[i]; i++)
		printf("%s\n", strs[i]);
	free(lineptr);

	return (0);
}

/* getline should allocate a buffer for storring the line, even if
 * *lineptr is set to NULL (so always free lineptr)
 * getline return number of char on sucess and -1 if failure.
 */
char *_getline(void)
{
	int bufsize = BUFSIZE;
	int i = 0, c;
	char *buf = malloc(sizeof(* buf) * bufsize);

	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buf[i] = '\0';
			return (buf);
		}
		buf[i++] = c;

		if (i >= BUFSIZE)
		{
			bufsize += BUFSIZE;
			buf = realloc(buf, bufsize);
			if (buf == NULL)
			{
				dprintf(2, "%s\n", "Cannot reallocate buffer");
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

char **strtow(char *str)
{
	char **strs;
	int wc, s, c, i, j;

	if (str == NULL || *str == '\0')
		return (NULL);

	wc = count_lineword(str);
	strs = malloc(sizeof(char *) * wc);
	if (!strs)
		panic(strs, 0);

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
