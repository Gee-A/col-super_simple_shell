#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * main - Exercise: fork + wait + execve
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t cpid, pid;
	int i = 0, status;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	while (i < 5)
	{
		cpid = fork();
		if (cpid == -1)
		{
			perror ("Error:");
			return (1);
		}

		pid = getpid();
		if (cpid == 0)
		{
			printf("(%u) \n", pid);
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error:");
		}
		else
		{
			wait(&status);
			printf("(%u) %u, I remain your father\n", pid, cpid);
		}
		i++;
	}
	return (0);
}

