#include "shell.h"
#define MAX_COMMAND_LENGTH 100

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "hellin$hell ", 13);

		ssize_t read_size = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);

		if (read_size <= 0)
		{
			if (read_size == 0)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			else
			{
				perror("read");
				continue;
			}
		}

		command[read_size - 1] = '\0';

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execlp(command, command, NULL);
			_exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	return 0;
}
