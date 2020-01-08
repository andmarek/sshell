# Source
[https://www.gnu.org/software/libc/manual/html_node/Process-Creation-Concepts.html#Process-Creation-Concepts ] 
# Process Creation
  - posix_spawn, fork, or vfork is called = new process created
  - Each new process has a pid.
  - wait or waitpid = wait for a child process to finish executing before continuing
  - Child process can execute another program using one of the exec functions 
    - The program executed is called the process image.
  - Starting execution of a new program causes the process to forget about its
    - previous process image.
# Process Identification
   - pid_t - reused over time
   - Process ends when the parent process waits on the pid after the proc.
    - terminates
   - pthread_create - threadid <- thread id of the main thread is the same pid
    - of the entire process
    - tid and pid = task id
    - threads never waited for explicitly 
# Executing a file
    - unistd.h
    - execv (const char *filename, char* const argv[])

# Launching Jobs
  - 
