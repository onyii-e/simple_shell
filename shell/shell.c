#include <stdio.h>
#include "shell.h"


int main(void)
{
	int response;
	char *exit_message = ":( Exiting the shell...";

	while (1)
	{
		show_prompt();
		response = get_exec_command();
		/*If user type exit break the look*/
		if (response == 99)
		{
			write(STDOUT_FILENO, exit_message, strlen(exit_message));
			return (0);
		}
	}
	return (0);
}

/**
  * show_prompt - A function for showing the prompt.
  */

void show_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", strlen("#cisfun$ "));
}

/**
  * get_exec_command - A function to read and execute command line arguments
  *
  * Return: 99 if use type exit, -1 if other error.
  */
ssize_t get_exec_command(void)
{
	char *mesg = NULL, *token;
	size_t n = 0;
	int i, val, response, num_tok = 0;
	char *delim = " ", **argv;

	val = getline(&mesg, &n, stdin);
	if (val == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Error in get_command: getline()");
			exit(EXIT_FAILURE);
		}
	}
	/* Remove the \n in the message*/
	mesg[strcspn(mesg, "\n")] = '\0';
	/*Find the number of command in the message*/
	token = strtok(mesg, delim);
	while (token != NULL)
	{
		num_tok++;
		token = strtok(NULL, delim);
	}
	num_tok++; /*To cater for the terminating NULL*/

	/* Allocate memory space to hold each token (string) in the argv*/
	argv = malloc(sizeof(char *) * num_tok);
	if (argv == NULL)
	{
		perror("Error in get_command: Can't allocate memory for argv");
		return (-1);
	}
	/* Now lets put each token inside the string pointer argv until token is NULL*/
	token = strtok(mesg, delim);
	for (i = 0; token; i++)
	{
		/*Since size of each command vary allocate each string dynamically to*/
		argv[i] = malloc(sizeof(char) * strlen(token) + 1);
		if (argv[i] == NULL)
		{
			perror("Error in get_command: Can't allocate memory for argv[i]");
			return (-1);
		}
		/*Copy the token into argv[i]*/
		strcpy(argv[i], token);
	}
	/*NULL-terminate the argv*/
	argv[i] = NULL;

	/*================ NOW LETS EXECUTE OUR STRING =====================*/
	response = execute_command(argv);
	
	/*Avoid memory leaks*/
	for (i = 0; i < num_tok; i++)
		free(argv[i]);
	free(argv);
	free(mesg);

	return (response);
}

/**
  * execute_command - A function that call execute family of functions.
  *
  * @command: The string command to execute.
  * Return: 0 for success, 99 for exit.
  */

int execute_command(char **command)
{
	pid_t pid;
	int val;
	/*If user typed exit, return*/
	if (strcmp(command[0], "exit") == 0)
	{
		return (99);
	}

	val = fork();
	if (val == -1)
	{
		perror("Error: fork from execute_command");
		exit(EXIT_FAILURE);
	}
	if (val == 0)
	{
		/* Execute child process*/
		execve(command[0], command, NULL);
		/* If child process fail to run*/
		perror("Error: execlp from excute_command");
		exit(EXIT_FAILURE);
	}
	else
	{
		/*Parent process*/
		wait(NULL);
	}
	return (0);
}
