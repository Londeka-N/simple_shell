#include "shell.h"
#define MAX_COMMAND_LENGTH 100
/**
 * readInput - reads the input of the user
 * @command: A character array to store the user's input
 * @max_length: The maximum length of the input
 * Return: 0 when successful
 *
*/

ssize_t readInput(char *command, size_t max_length)
{
	write(STDOUT_FILENO, "hellin$hell ", 13);
	return (read(STDIN_FILENO, command, max_length));
}

/**
 * executeCommand - function that executes the available command
 * @command: command string to parse
*/
void executeCommand(const char *command)
{
	execlp(command, command, NULL);

	write(STDERR_FILENO, "No such command in Hell Oh Shell\n", 32);
	_exit(EXIT_FAILURE);
}

/**
 * main - encloses the code
 * read_size - reads the size of input
 * Return: 0 when successful
*/

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int status;
	pid_t pid;

	while (1)
	{
		ssize_t read_size = readInput(command, MAX_COMMAND_LENGTH);

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
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			executeCommand(command);
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}

