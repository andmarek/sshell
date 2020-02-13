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

int execute(char **argv);
int launch(char **, int);
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
                        //prompt = argv[2]; /* Sets the prompt */
                        prompt = argv[2];
                        //strcpy(prompt, argv[2]);
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

/* Checks to see if we are running this as a background process */
int
parse_ampersand(char **argv)
{
   int i;
   i = 0;
   while(argv[i] != NULL && argv[i][0] != '\0') { /* Make sure we check for NULL */
       if (argv[i][0] == '&') {
           printf("Ampersand in while loop\n");
           argv[i] = NULL;
           free(argv[i]);
           return 1;
       }
       i++;
   }
   return 0;
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
    while (token != NULL) {
        tokens[token_count] = token;
        token = strtok(NULL, sep);
        token_count++;
    }

    /* Putting a null byte here so we can count the argv eventually */
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
    return line;
}

/* Event loop is responsible for configuring the prompt for the user, and actually
 * prompting the user for input.  When a user enters a line, read_line() is
 * called, which gets and returns the line as a char *.  This gets passed to
 * char **split_line() which tokenizes the line into consumable C-strings.
 * Finally, execute() gets called.  */


void
event_loop(char *prompt)
{
    char *line;
    char **argv;
    int status;
    int argc = 0;
    char *name;
    int background;

    //char cwd[1024];
    //getcwd(cwd, sizeof(cwd));

    if (prompt == NULL) { 
        prompt = "308sh";
    }


    if (!name) {
        fprintf(stderr, "Error getting username\n");
    }

    do {
        printf(ANSI_COLOR_GREEN);
        printf("%s > ", prompt);
        printf(ANSI_COLOR_RESET);

        line = read_line();
        argv = split_line(line);

        background = (parse_ampersand(argv));

        if (background) {
            printf("found a dirty ampersand\n");
        }

        /* Some builtins, this feels like Go */
        if (!argv) {
            continue;
        }

        if (strcmp(argv[0], "cd") == 0) {
            if (ss_cd(argv[1]) < 0) {
                perror(argv[0]);
            }
            continue;
        }

        if (strcmp(argv[0], "exit") == 0) {
              status = ss_exit();
            continue;
        }

        if (strcmp(argv[0], "pwd") == 0) {
             status = ss_pwd(argv); 
            continue;
        }

        if (strcmp(argv[0], "pid") == 0) {
              status = ss_pid(argv); 
            continue;
        }
        if (strcmp(argv[0], "ppid") == 0) {
              status = ss_ppid(argv); 
            continue;
        }

        status = launch(argv, background);


        free(line);
        free(argv);
    } while(status);

}


/* Forks the parent process to perform desired task.  If the pid of fork() returns
 * 1, we replace the process image with some program that the user has entered.
 * The parent process waits until the child process is done executing until
 * returning to the parent function. */
int
launch(char **argv, int background)
{
    int status;
    pid_t pid, wpid;

    pid = fork();

    if (pid == 0) { // Child process
        printf("pid: %d\n", wpid);

        if (execvp(argv[0], argv) < 0) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }

    } else if (pid > 0) { // Parent process
        if (background) {
            //waitpid(pid, NULL, 0);
            setpgid(0, 0);
        } else {
            do {
                printf("pid: %d\n", wpid);
                wpid = waitpid(pid, &status, WUNTRACED);
            } while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    } else {
        perror("Fork failed: pid < 0\n");
    }

    return 1;
}

