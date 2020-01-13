#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "functions.h"

#define BUFSIZE 64

/* Function prototypes */
int execute(char **args);
int launch(char **);
int num_builtins();
char **split_line(char *line);
char *read_line(void);
void event_loop(void);

void usage(char *name)
{
fprintf(stderr,
          "Usage: %s [-p|--prompt <promt_string>] \n",
          name);

  exit(-1);
}

int (*builtin_func[]) (char **) = {
    &ss_cd,
    &ss_help,
    &ss_exit,
    &ss_pwd,
    &ss_clear,
    &ss_ls

};

int
main(int argc, char **argv)
{
    uint32_t long_arg = 0;

    if (argc > 1) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') {
                argv[i]++;
                long_arg = 1;
            }
            switch (argv[i][1]) {
                switch 'p':
                    break;
            }
        }
    }

    event_loop();
    return EXIT_SUCCESS;
}

int
num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

char **
split_line(char *line)
{
    char *sep = "\t\r\n\a";

    char **tokens;
    char *token;

    int token_count = 0;

    tokens = malloc(sizeof (char*) * BUFSIZE);
    token = strtok(line, sep);

    while(token != NULL) {
        //printf("%s\n", token);
        // double the size to make sure it's not overflowed
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, sep);
    }
    // Putting a null byte here so we can count the args eventually
    tokens[token_count] = "\0";

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

/* Main loop for parsing input and delegating duties */
void
event_loop(void)
{
    char *line;
    char **args; // Getting the reference from the tokens we parsed.
    int status;
    int argc = 0;

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    char short_version[20];
    /* We'll need to find the length of the pwd (cwd variable)
       and determine where we need to cut this.
       Maybe tokenize it?.
       */
    strncpy(short_version, cwd + 19, 27 - 18);

    char *name = getlogin();

    if (!name) {
        fprintf(stderr, "Error getting username\n");
    }

    do {
        printf("> %s :: %s : ", name, short_version);
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);

    } while(status);

}

int
execute(char **args)
{
    printf("Execute gets called");
    int i;

    if (args[0] == NULL) {
        return 1;
    }

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
    return launch(args);
}

/* Forks the parent process to perform desired task */
int
launch(char **args)
{
    int status;
    pid_t pid, wpid;

    pid = fork();

    if (pid == 0) {
        //Exec encounters an error
        if (execvp(args[0], args) == -1) {
            perror("fork failed\n");
            fprintf(stderr, "an error occurred in execvp\n");
        }
        printf("do something\n");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed.");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

