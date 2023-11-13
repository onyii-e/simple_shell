#include <stdio.h>
#include "shell.h"

/**
  * main - The shell entry.
  *
  * Return - Always 0.
  */
int main(void)
{
	ssize_t response;
	char *exit_message = "(: Leaving so soon?\n(: See you next time...\n";

	while (5)
	{
		entrance();
		response = get_exec_command();
		/* If user types exit or EXIT break the loop*/
		if (response == 99)
		{
			write(STDOUT_FILENO, exit_message, strlen(exit_message));
			return (0);
		}
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

	/*Now lets get the user input from the command line*/
	val = getline(&mesg, &n, stdin);
	if (val == -1)
	{
		/* Can't read mesg either no input or an error.*/
		if (feof(stdin))
		{
		/*If end of file in stdin i.e. no args*/
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
		/* If can't read due to error in getline*/
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	/*Now replace '\n' from the user input with '\0'*/
	mesg_copy = strdup(mesg); /* FREE ME LATER !!! */
	if (mesg_copy == NULL)
	{
		perror("Can't duplicate command line message");
		exit(EXIT_FAILURE);
	}
	mesg_copy[strcspn(mesg_copy, "\n")] = '\0';

	/*Find the number of command in the message*/
	token = strtok(mesg_copy, delim);
	while (token)
	{
		num_token++;
		token = strtok(NULL, delim);
	}
	num_token++; /* Cater for terminating NULL*/
	/*mesg_copy = strdup(mesg);  renew mesg, after first tokenization*/

	/* Allocate memory to hold num_token amount of strings */
	argv = malloc(sizeof(char *) * num_token);
	if (argv == NULL)
	{
		perror("Error in argv: Can't allocate space for message");
		exit(EXIT_FAILURE);
	}
	/* Write each token into the argv */
	token = strtok(mesg_copy, delim);
	for (i = 0; token; i++)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL; /* NULL-terminate the argv*/

	/* Now execute the argv */
	response = execute_command(argv);

	/* Avoid memory leaks*/
	for (i = 0; i < num_token; i++)
		free(argv[i]);
	free(argv);
	free(mesg);
	free(mesg_copy);

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
