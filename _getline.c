#include "shell.h"

/**
 * _getline - read one line from the prompt
 * @data: struct for the program's data
 *
 * Return: reading counting bytes
 */
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_commands[10] = {NULL};
	static char array_operators[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* check if doesnot exit more commands in the array */
	/* and cheks the logical operators */
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
			(array_operators[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exits */
		for (i = 0; array_commands[i]; i++)
		{
			free(array_commands[i]);
			array_commands[i] = NULL;
		}

		/* read from the file descriptor int to buff */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* split lines for \n or ; */
		i = 0;
		do {
			array_commands[i] = str_duplicate(_strtok(i ? NULL : buff, "\n;"));
			/*checks and splits for && and  || operators*/
			i = check_logic_ops(array_commands, i, array_operators);
		} while (array_commands[i++]);
	}

	/*obatins the next commands (command 0) and remove it for the arrays*/
	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
	{
		array_commands[i] = array_commands[i + 1];
		array_operators[i] = array_operators[i + 1];
	}

	return (str_length(data->input_line));
}


/**
 * check_logic_ops - checks and split for && and || operators
 * @array_commands: array of the command
 * @i: index in the array_commands to be checked
 * @array_operators: array of the logical operators for each previous command
 *
 * Return: index of the last command in the array_commands
 */
int check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *tmp = NULL;
	int j;

	/* checks for the & char in the command lines*/
	for (j = 0; array_commands[i] != NULL && array_commands[i][j]; j++)
	{
		if (array_commands[1][j] == '&' && array_commands[i][j + 1] == '&')
		{
			/* split the line when chars && was found */
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_operators[i] = '&';
			free(tmp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{
			/* split the line when the chars || was found */
			tmp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = str_duplicate(array_commands[i]);
			array_commands[i + 1] = str_duplicate(tmp + j + 2);
			i++;
			array_operators[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}

