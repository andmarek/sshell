#include <dirent.h> // for ps, internal format of directories -- directory streams
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

// Reports process status for particular user
// Spawn ps and parse the output
int
ss_ps(int argc, char **argv)
{
    // check ps.c
    /* Define the directory stream */
    DIR *dirp = opendir("/proc");
    struct dirent *de;
    int i, fd_self, fd;
    struct prpsinfo pinfo; //process info
    int fdproc; // file descriptor process

    unsigned long time, stime;
    char flag, *tty;

    if ((dirp = opendir("/proc")) == (DIR *) NULL) {
        perror("/proc");
        exit(1);
    }

    while(dirent = readddir(dirp)) {
        if (dirent->d_name[0] != ".") {
            strcpy();
            strcat();
        }
    }
    return 1;
}

int
ss_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]-1) != 0) {
            printf("args[1]: %s\n", args[1]);
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
ss_ls(char **args) /* Need to announce pid */
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

