#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	extern char **environ;
	unsigned int i;

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
	return (0);
}
