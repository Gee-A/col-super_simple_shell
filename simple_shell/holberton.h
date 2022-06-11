#ifndef _HOLBERTON_H
#define _HOLBERTON_H

#define EXEC	1
#define REDIR	2
#define PIPE	3
#define LIST	4
#define BG	5
#define AND	6
#define OR	7

#define MAXARGS	10

extern char **environ;

/**
 * struct cmd - suitable cast for every operations
 * @type: operations head
 */
typedef struct cmd
{
	int type;
} cmd_t;

/**
 * struct execcmd - handles cmd execution using execve
 * @type: denotes command type
 * @argv: stores commands and option upto MAXARGS - 1
 * @eargv: stores end of commands/ options assigned to argv
 */
typedef struct execcmd
{
	int type;
	char argv[MAXARGS];
	char eargv[MAXARGS];
} execcmd_t;

/**
 * struct redircmd - handles file redirection
 * @type: denotes command type
 * @file: file up for redirection
 * @efile: end of file
 * @mode: mode of opening file
 * @fd: file descriptor
 * @cmd: cmd to run (e.g 'cmd' >> file)
 */
typedef struct redircmd
{
	int type;
	char *file;
	char *efile;
	int mode;
	int fd;
	cmd_t cmd;
} redircmd_t;

/**
 * struct pipecmd - gives the output of left command as input to right
 * @type: denotes command type
 * @left: command to run in left sub-tee
 * @right: command to run int right sub-tree
 */
typedef struct pipecmd
{
	int type;
	cmd_t *left;
	cmd_t *right;
} pipecmd_t;

/**
 * struct listcmd - run left command then right
 * @type: denotes command type
 * @left: command to run in left sub-tree
 * @right: command to run in right sub-tree
 */
typedef struct listcmd
{
	int type;
	cmd_t *left;
	cmd_t *right;
} listcmd_t;

/**
 * struct bgcmd - run command in background
 * @type: denotes command type
 * @cmd: command to run in background
 */
typedef struct bgcmd
{
	int type;
	cmd_t *cmd;
} bgcmd_t;

/**
 * struct andcmd - run right command if only left runs
 * @type: denotes command type
 * @left: command to run in left sub-tree
 * @right: command to run in right sub-tree
 */
typedef struct andcmd
{
	int type;
	cmd_t *left;
	cmd_t *right;
} andcmd_t;

/**
 * struct orcmd - run right command only if left does not.
 * @type: denotes command type
 * @left: command to run in left sub-tree
 * @right: command to run in right sub-tree
 */
typedef struct orcmd
{
	int type;
	cmd_t *left;
	cmd_t *right;
} orcmd_t;

#endif /* _HOLBERTON_H */
