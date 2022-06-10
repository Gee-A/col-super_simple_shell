#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0
 */
int main(void)
{
	pid_t wpid, ppid;

	ppid = getppid();
	wpid = getpid();

	printf("Parent pid: %u\nWorking pid: %u\n", ppid, wpid);

	/* read 'proc/sys/kernel/pid_max' to get maximum pid value */
	return (0); 
}
