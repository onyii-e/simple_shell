#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>

extern char **environ;
void entrance(void);
ssize_t get_exec_command(void);
int execute_command(char **command);
char *pathfinder(char *filename);

#endif /*SHELL_H*/
