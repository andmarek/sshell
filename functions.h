#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int     ss_exit(char **);
int     ss_cd(char **);
int     ss_help(char **);
int     ss_pwd(char **);
int     ss_clear(char **);
int     ss_ls(char **);
int     ss_ps(char **);

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "pwd",
    "clear",
    "ls",
    "pid",
    "ppid

};

char *non_builtin_str[] = {
    "ps"
}:
#endif
