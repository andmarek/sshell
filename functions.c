int
cd(char **args)
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
help(char **args)
{
    printf("Bruh you ain't need help.");
    return 1;
}
