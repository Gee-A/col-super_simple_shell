#include <stdio.h>
#include <string.h>

char *_getenv(const char *name);
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	extern char **environ;
	unsigned int i;
	char buff[20];

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("\n%s\n\n", "You did yours main");

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);  /* prints in form of "variable=value" */
	printf("Address of env: %p\nAddress of environ: %p\n",
		       (void *)	env,(void *) environ);

	printf("Name of environment variable: ");
	fgets(buff, 20, stdin);
	printf("%s\n", _getenv(buff)); /* I ought to checl if getenv returns null */
	return (0);
}

int cmpenv(const char *nenv, const char *name);
char *_getenv(const char *name)
{
	extern char **environ;
	char *envptr = NULL;
	unsigned int i, j;

	i = 0;
	while (environ[i])
	{
		if ((j = cmpenv(environ[i], name)))
		{
			envptr = environ[i];
			break;
		} i++;
	}
	return (envptr + j);
}

int cmpenv(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
		if (nenv[i] != name[i])
			return (0);
	return (i + 1); /* get pass '=' */
}

/* if name does exit in the environment, then overwrite determines if
 * value should be reassigned, if 0 -> no overwrite, if non-zero -> overwrite */
int _setenv(const char *name, const char *value, int overwrite)
{
	extern char **environ;
	/* search the environ calling _getenv with name
	 * if null then open environ, fix in name and value.
	 */
	int success = -1;
	if (name && value)
	{
		if (_getenv(name))
	}

	return (success);
