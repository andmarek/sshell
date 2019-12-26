#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 64

typedef struct line {
    char **tokens;
    char *token;
    int bufsize;

} line_t;

char **split_line(char *line)
{
    int position = 0;
    char *sep = "\t\r\n\a";

    // Allocate for struct
    line_t *l = (line_t *) malloc(sizeof (line_t));

    l->bufsize = BUFSIZE; // Is there a way to do this elsewhere?

    if (l == NULL)        // If malloc fails (returns void *)
        return NULL;

    // Allocate for tokens
    l->tokens = malloc(BUFSIZE * sizeof(char *));

    // Check for token's malloc
    if (!l->tokens) {
        fprintf(stderr, "lsh: allocation error\n");
    }

    /* Tokenize - the first time we call strtok,
       we expect that the first arg is specified.
       Always include the delimiter. */
    l->token = strtok(line, sep);

    while (l->token != NULL) {
        l->tokens[position] = l->token;
        position++;
        if (position >= l->bufsize) {
            /* Double the line's buffer size if the
               position exceeds the original buffer size */
            l->bufsize += BUFSIZE;
        }
    }

    // Remember to free...

    return l->tokens;
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
        args = split_line(line); // parsing the commands, of course

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
