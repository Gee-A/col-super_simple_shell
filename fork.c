#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int duplicate(void);
int who(void);
int wait_for_me(void);

/**
 * main - fork exampe
 * Return: Always 0.
 */
int main(void)
{
	// duplicate();
	// who();
	wait_for_me();
}

/* Fork creates a new child process almost identical to the parent
 * process but with different pid, stacks, datas and heaps. */
int duplicate(void)
{
	pid_t pid, wpid;

	printf("Before fork\n");
	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (-1);
	}
	printf("After fork\n");
	wpid = getpid();
	printf("Working pid is %u\n", wpid);
	return (0);
}

/* fork returns 0 to the child, and the PID of the child to the father. */
int who(void)
{
	pid_t pid, cpid;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return (1);
	}
	pid = getpid();
	printf("My pid is %u\n", pid);
	if (cpid == 0)
		printf("(%u) Noooooo!\n", pid);
	else
		printf("(%u) %u, I am your father\n", pid, cpid);
	return (0);
}

/* fork & wait example */
int wait_for_me(void)
{
	pid_t cpid;
	int status;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (cpid == 0)
	{
		printf("Wait for me, wait for me\n");
		sleep(3);
	}
	else
	{
		wait(&status);
		printf("Oh, it's all better now\n");
	}
	return (0);
}
