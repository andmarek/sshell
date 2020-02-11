#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int     ss_exit(char **);
//int     ss_cd(char **);
int     ss_help(char **);
int     ss_pwd(char **);
int     ss_clear(char **);
int     ss_ls(char **);
int     ss_pid(char **);
int     ss_ppid(char **);

char *builtin_str[] = {
   // "cd", // required
    "help",
    "exit", // required
    "pwd", // required
    "clear",
    "ls",
    "pid", // required
    "ppid", // required
};

#endif
