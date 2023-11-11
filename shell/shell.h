#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void show_prompt(void);
ssize_t get_exec_command(void);
int execute_command(char **command);

#endif /* SHELL_H */
