#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 64
#define TOK_DELIM "\t\r\n\a"

typedef struct line {
    char **tokens;
    char *token;
    int bufsize;

} line_t;

line_t *split_line(char *line)
{
    int position = 0;

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
    l->token = strtok(line, TOK_DELIM);

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
    
    return l;
}
/* Reads user input */
char *lsh_read_line(void)
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

    do {
        printf("> ");
        line = lsh_read_line();
        //args = lsh_split_line(args);

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
