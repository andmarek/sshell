#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

/* Macros */
#define clear() printf("\033[H\033[J")

int
ss_ppid(void)
{
    pid_t ppid = getppid();
    printf("The ppid is: %d\n", ppid);
    return 1;
}

int
ss_pid(void)
{
    pid_t pid = getpid();
    printf("The pid is: %d\n", pid);
    return 1;
}

int
ss_help(char **argv)
{
    printf("Bruh you ain't need no help.\n");
    return 1;
}

int
ss_exit()
{
    return 0;
}

int
ss_ls(char **argv)
{
    DIR *dirhandle = opendir(".");

    if (!dirhandle) {
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
ss_pwd(char **argv)
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
ss_clear(char **argv)
{
    clear();
    return 1;
}

