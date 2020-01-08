typedef struct job
{
    struct job *next;
    char *command;
    process *first_process;
    pid_t pgid;
    char notified;
    struct termios tmodes;
    int stdin, stdout, stderr;
} job_t;

job* find_job(pid_t);
int job_is_stopped(job *j);
int job_is_completed(job *j);