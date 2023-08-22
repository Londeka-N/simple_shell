#include "main.h"
/*
 *main - encloses the code
 *print_prompt - it basically assists in the printing of the prompt
*/

void print_prompt(void);
char *get_command(void);
void execute_command(char *command);
void wait_for_child(void);

int main(void)
{
	char *command;

	while (1)
	{
		print_prompt();
		command = get_command();

		if (command == NULL)
		{
			break;
		}
		if (strcmp(command, "quit\n") == 0)
		{
			free(command);
			break;
		}
		execute_command(command);
		wait_for_child();

		free(command);
	}
	return (0);
}

void print_prompt(void)
{
	if (write(1, "hell_in_shell$ ", 15) < 0)
	{
		perror("write");
		_exit(1);
	}
}

char *get_command(void)
{
	char *line = NULL;
	size_t size = 0;

	if (getline(&line, &size, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		else
		{
			perror("getline");
			_exit(1);
		}
	}
	return (line);
}

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *argv[2];
		argv[0] = command;
		argv[1] = NULL;

		char *environ[] = {NULL};

		if (execve(command, argv, environ) == -1)
		{
			perror("execve");
			_exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		_exit(1);
	}
}

void wait_for_child(void)
{
	int status;

	if (wait(&status) == -1)
	{
		perror("wait");
		_exit(1);
	}
}
