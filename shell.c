#include "main.h"

/**
 * execute_command - executes a command with fork and execve
 * @argv: array of command and arguments
 * @shell_name: name of the shell program
 * @line_count: current command line number
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **argv, char *shell_name, unsigned int line_count)
{
	pid_t pid;

	if (argv[0] == NULL)
		return (-1); /* do nothing if command is empty */

	pid = fork(); /* create child process */
	if (pid == -1)
	{
		perror("fork"); /* print error if fork fails */
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			fprintf(stderr, "%s: %u: %s: not found\n",
					shell_name, line_count, argv[0]); /* print error message */
			exit(127);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}
