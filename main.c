#include <stdio.h>
#include "shell.h"

/**
  * main - The shell entry.
  *
  * Return: Always 0.
  */
int main(void)
{
	ssize_t response;

	while (5)
	{
		entrance();
		response = get_exec_command();
		/* If user types exit or EXIT break the loop*/
		if (response == 99)
		{
			return (0);
		}
		if (response == 90)
			continue;
	}

	return (0);
}

/**
  * entrance - Prints the shell prompt
  */
void entrance(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", strlen("#cisfun$ "));
}

/**
  * get_exec_command - A function that accept and execute requests from cli
  *
  * Return: 0 or 99 for success.
  */

ssize_t get_exec_command(void)
{
	char *mesg = NULL, *token, *mesg_copy, **argv, *delim = " ";
	int i, val, response, num_token = 0;
	size_t n = 0;

	val = getline(&mesg, &n, stdin); /*Get user input*/
	if (val == -1)
	{
		if (feof(stdin))
			write(STDOUT_FILENO, "\n", 1), exit(EXIT_SUCCESS);
		else
			perror("getline"), exit(EXIT_FAILURE);
	}
	mesg_copy = strdup(mesg); /* FREE ME LATER !!! */
	if (mesg_copy == NULL)
		perror("strdup"), exit(EXIT_FAILURE);
	mesg_copy[strcspn(mesg_copy, "\n")] = '\0';
	if (*mesg_copy == '\0')
		return (90);
	token = strtok(mesg_copy, delim);
	while (token)
		num_token++, token = strtok(NULL, delim);
	argv = malloc(sizeof(char *) * (num_token + 1)); /*Null terminate*/
	if (argv == NULL)
		perror("malloc"), exit(EXIT_FAILURE);
	token = strtok(mesg_copy, delim); /*Write each token into argv*/
	for (i = 0; token; i++)
	{
		argv[i] = strdup(token);
		if (argv[i] == NULL)
			break;
		token = strtok(NULL, delim);
	}
	argv[i] = NULL, response = execute_command(argv); /* Execute argv*/
	for (i = 0; i < num_token; i++)
		free(argv[i]);
	free(argv), free(mesg), free(mesg_copy);
	return (response);
}

/**
  * execute_command - A function that execute the command line requests.
  * @command: The request made by the user.
  *
  * Return: 0 on success and 99 if the user types exit or EXIT.
  */

int execute_command(char **command)
{
	char *first_command;
	pid_t val;

	/* If user type exit or EXIT return 99*/
	if ((strcmp(command[0], "exit") == 0) || (strcmp(command[0], "EXIT") == 0))
		return (99);

	if (*command == NULL)
		write(STDOUT_FILENO, "\n", 1);

	val = fork();
	if (val == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (val == 0)
	{
		/*Check the path and then execute child process*/
		first_command = pathfinder(command[0]);
		execve(first_command, command, environ);
		/*If command is not executed due to error*/
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Hold on with parent process*/
		wait(NULL);
	}

	return (0);
}
