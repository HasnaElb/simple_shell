#include "shell.h"
/**
 * _execev - Execute a programming exec
 * @line:  recieved from strtok the token
 * @argv: line of arguments of file
 * @num:  variablei internal
 * @isatty_val: is the tty
 * @envi: enviroment variable
 * Return: None
 */
void _execev(char **line, char *argv, int num, int isatty_val, char **envi)
{
	pid_t pid;
	int _exec = 0;

	if (line == NULL || line[0] == NULL)
		return;

	if (is_buit(line, envi) == 1)
		return;

	pid = fork();
	if (pid < 0)
	{
		perror("Error during fork");
		free_dp(line);
		exit(EXIT_FAILURE);
	}
	else if (pid != 0)
	{
		wait(NULL);
		return;
	}
	else
	{
		unsetenv("PATH");

		_exec = execve("/bin/ls", line, envi);

		if (_exec < 0)
		{
			if (isatty_val == 1)
				fprintf(stderr, "%s: No such file or directory\n", argv);
			else
				fprintf(stderr, "%s: %d: %s: not found\n", argv, num, line[0]);

			free_dp(line);
			exit(EXIT_FAILURE);
		}
		free_dp(line);
		exit(EXIT_SUCCESS);
	}
}
