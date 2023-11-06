#ifndef HELPERS_H
#define HELPERS_H

/* prompt to be printed */
#define PROMPT_MSG "$" /* Needed to work with signal */

/* Resume from the unused attribute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"       change the shell working directory.\n\n"\
"       if no argument is given to cd the command will be interpreted\n"\
"       as cd $HOME.\n"\
"       if the argumenthelp is - (cd -), the command will be interpreted\n"\
"       as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit = \n"\
"exit : \texit[STATUS]\n\n"\
"       Exit of the simple - shell.c\n\n"\
"       Exits the shell with a status of N.If N is omitted, the exit status\n"\
"       is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env = \n"\
"env : \tenv \n\n"\
"       print environment.\n\n"\
"       The env command willbe print complete list of enviroment variable.\n\n"

#define HELP_SETENV_MSG "setenv = \n"\
"setenv : \tsetenv VARIABLE VALUE\n\n"\
"       change or add an environment variable.\n\n"\
"       initialize a new environment variable, or modify an existing one\n"\
"       when there aren't correct number of argument print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv = \n"\
"unsetenv : \tunsetenv VARIABLE\n\n"\
"       The unsetenv function deletes one variable from the enviroment.\n\n"\
"       when there aren't correct numbers of argument print error message.\n\n"

#define HELP_MSG "help = \n"\
"help : \thelp[BUILTIN_NAME]\n\n"\
"       Display information about builtin commands.\n\n"\
"       Display breif summaries of builtin command. if BUILTIN_NAME is\n"\
"       specified, gives detail help onall commands matching BUILTIN_NAME, \n"\
"       otherwise the list of help topics is printed BUILTIN_NAME listt.\n"\
"       Argument : \n\n"\
"       BUILTIN_NAME specifying a help topic.\n\n"\
"       cd\t[dir]\n"\
"       exit\t[status]\n"\
"       env\n"\
"       setenv\t[variable value]\n"\
"       unset\t[variable]\n"\
"       help\t[built_name]\n\n"

#endif

