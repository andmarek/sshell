#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int ss_exit(char **);
int ss_cd(char **);
int ss_help(char **);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

#endif
