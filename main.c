#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 64

//char **split_line(char *line)
char **split_line(char *line)
{
    int position = 0;

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

    //return tokens;
    // Remember to free...
    return tokens;

}
/* Reads user input */
char *read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

/* Main loop for parsing input and delegating duties */
void event_loop(void)
{
    char *line;
    char **args;
    int status;

    char *name = getlogin();

    if (!name) {
        fprintf(stderr, "Error getting username\n");
    }

    do {
        printf("> %s: ", name);
        line = read_line();
        args = split_line(line);

        for (int i = 0; i < 3; i++) {
            printf("%s", args[i]);
        }


        free(line);
        free(args);

    } while(status);

}

/* Forks the parent process to perform desired task */
int launch(int argc, char **args)
{
    int status;
    pid_t pid, wpid;

    pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("fork failed");
        }
        printf("do something");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed.");
    } else {
        do {
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;

}
int main(int argc, char **argv)
{
    event_loop();
    return EXIT_SUCCESS;
}
