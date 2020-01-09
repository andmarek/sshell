#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

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
        printf("Hey this should have changed the dir");
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
    DIR *dirhandle = opendir(".");

    if (dirhandle == NULL) {
        fprintf(stderr, "issues.");
    }

    struct dirent *de;
    while (de = readdir(dirhandle)) {
        _Bool is_dir;
#ifdef _DIRECT_HAVE_D_TYPE
        if (de->d_type != DT_UNKNOWN && de->d_type != DT_LNK) {
            is_dir = (de->d_type == DT_DIR);
        } else
#endif
        {
            struct stat stbuf;
            stat(de->d_name , &stbuf);
            is_dir = S_ISDIR(stbuf.st_mode);
        }

        if (is_dir) {
            printf(ANSI_COLOR_RED);
            printf("%s/\n", de->d_name);
            printf(ANSI_COLOR_RESET);
        } else {
            printf("%s\n", de->d_name);
        }
    }
    return 1;
}

int
ss_pwd(char **args)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    /* Ugly, fix later */
    printf(ANSI_COLOR_RED);
    printf("%s\n", cwd  );
    printf(ANSI_COLOR_RESET);

    return 1;
}

int
ss_clear(char **args)
{
    clear();
    return 1;
}

