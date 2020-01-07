#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

/* Macros */
#define clear() printf("\033[H\033[J")

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

int
ss_ls(char **args)
{
    DIR *dirp;
    struct dirent *direntp;

    /* Ugly hack, but we can get a const char * of the directory
     * to open.  I'm sure there's a better solution. */
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    dirp = opendir(cwd); // DIR *opendir (const char *dirname)

    if (dirp == NULL) {
        perror("problem");
    } else {
        for (;;) {
            direntp = readdir(dirp);
            if (direntp == NULL) break;
            printf("%s\n", direntp->d_name);
        }
        closedir(dirp);
    }

    return 1;
}

int
ss_pwd(char **args)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    printf("%s\n", cwd);
    return 1;
}

int
ss_clear(char **args)
{
    clear();
    return 1;
}



