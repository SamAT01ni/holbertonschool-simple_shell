#include "main.h"

/**
 * main - entry point of the simple shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line, *args[64];
	size_t len;
	ssize_t read_chars;
	unsigned int line_count;
	int interactive;
	int status = 0; /* store last command status */

	(void)ac; /* avoid unused parameter warning */
	line = NULL; /* initialize getline buffer */
	len = 0; /* initialize buffer size */
	line_count = 0; /* initialize command counter */
	interactive = isatty(STDIN_FILENO); /* check interactive mode */

	while (1)
	{
		if (interactive)
			print_prompt(); /* print prompt only in interactive mode */

		read_chars = getline(&line, &len, stdin); /* read input line */
		if (read_chars == -1)
		{
			free(line);
			exit(status); /* exit with last command status */
		}

		line_count++; /* count every input line */
		clean_input(line); /* remove trailing newline */

		if (parse_input(line, args) == 0)
			continue; /* skip empty lines */

		status = execute_command(args, av[0], line_count); /* execute command */
	}
}
