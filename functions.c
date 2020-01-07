#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cd(char **);
int help(char **);
int ss_exit(char **);



int
ss_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("problem");
        }
    }
    return 1;
}

int
ss_help(char **args)
{
    printf("Bruh you ain't need help.");
    return 1;
}

int
ss_exit(char **args)
{
    return 0;
}

