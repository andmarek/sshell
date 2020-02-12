#include <sys/types.h>
#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include "colors.h"
#include "functions.h"

#define BUFSIZE 64

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN     "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int execute(char **args);
int launch(char **);
int num_builtins();
char **split_line(char *line);
char *read_line(void);
void event_loop();
void usage(char *);

/* Sshell is a simple shell that interprets a set of builtin commands and can
 * execute various other programs. */
int
main(int argc, char **argv)
{
    char *prompt;
    uint32_t i, j;
    uint32_t long_arg = 0;

    if (argc > 1) {
        for(i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == '-') {
                    argv[i]++;
                    long_arg = 1;
                }

                switch (argv[i][1]) {
                    case 'p':
                        prompt = argv[2];
                        printf("arg[2]: %s\n", argv[2]);
                        printf("Shell initialized with prompt: %s\n", prompt);
                    break;
                    case 'h':
                        usage("SSHELL");
                        break;
                    default:
                        break;
                }
            }
        }
    }

    event_loop(prompt);

    return EXIT_SUCCESS;
}

void
usage(char *name)
{
    fprintf(stderr,
            "Usage: %s [-p|--prompt <promt_string>] \n",
            name);

    exit(-1);
}

void
(*colors_func[]) (void) = {
    &red,
    &yellow,
};

int
(*builtin_func[]) (char **) = {
    //&ss_cd,
    &ss_help,
    &ss_exit,
    &ss_pwd,
    &ss_clear,
    &ss_ls //    &ss_ps
};

/* returns the number of the builtin functions as an integer */
int
num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/* Takes a line and splits it into consumable tokens */
char **
split_line(char *line)
{
    char *sep = " \t\r\n\a";

    char **tokens;
    char *token;

    int token_count = 0;

    tokens = malloc(sizeof (char*) * BUFSIZE);
    token = strtok(line, sep);

    while(token != NULL) {
        tokens[token_count] = token;
        token = strtok(NULL, sep);
        token_count++;
    }

    /* Putting a null byte here so we can count the args eventually */
    tokens[token_count] = NULL;

    return tokens;

}

/* Reads user input */
char *
read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    //printf("%s ff\n", line); Get line consumes \n
    //return line-1;
    return line;
}

/* Event loop is responsible for configuring the prompt for the user, and actually
 * prompting the user for input.  When a user enters a line, read_line() is
 * called, which gets and returns the line as a char *.  This gets passed to
 * char **split_line() which tokenizes the line into consumable C-strings.
 * Finally, execute() gets called.  */
 
int ss_cd_short(char *path)
{
    char *home_dir = getenv("HOME");


    if (path == NULL) {
        ss_cd_short(home_dir);
    } 

    if ((chdir(path) < 0)) {
      perror(path);

    }
}

void
event_loop(char *prompt)
{
    char *line;
    char **args;
    int status;
    int argc = 0;
    char *name;

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    if (!prompt) { /* Should check if prompt is null. */
        printf("Not prompt\n");
        prompt = "308sh";
    }

    if (!name) {
        fprintf(stderr, "Error getting username\n");
    }

    do {
        
       /* for (int i = 0; i < 2; i++) {
            
            return (*colors_func[i])();

        }*/
        
        printf(ANSI_COLOR_GREEN);
        printf("%s > ", prompt);
        printf(ANSI_COLOR_RESET);

        line = read_line();
        args = split_line(line);

        /* Some builtins */
        if (strcmp(args[0], "cd") == 0) {
            if (ss_cd_short(args[1]) < 0) {
                perror(args[0]);
            }
            continue;
        } /*else if (strcmp(args[0], "ppid") == 0) {
            ss_ppid(pid) {

            }*/

        status = execute(args);

        free(line);
        free(args);
    } while(status);

}

/* Execute through a list of strings to see if we can call a respective function
 * pointer to a built-in function */
int
execute(char **args)
{
    int i;

    for (i = 0; i < num_builtins(); i++) {
        if ( strcmp( args[0], builtin_str[i] ) == 0 ) {
            return (*builtin_func[i])(args);
        }
    }
    return launch(args);
}

/* Forks the parent process to perform desired task.  If the pid of fork() returns
 * 1, we replace the process image with some program that the user has entered.
 * The parent process waits until the child process is done executing until
 * returning to the parent function. */
int
launch(char **args)
{
    int status;
    pid_t pid, wpid;

    pid = fork();

    if (pid == 0) { // Child process
        if (execvp(args[0], args) < 0) {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) { // Parent process
        do {
            printf("pid: %d\n", wpid);
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        perror("Fork failed: pid < 0\n");
    }
    return 1;
}

