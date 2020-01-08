/* From https://www.gnu.org/software/libc/manual/html_node/Initializing-the-Shell.html#Initializing-the-Shell */

#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

pid_t shell_gpid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

void
init_shell()
{
    shell_terminal = STDIN_FILENO;
    shell_is_interactive = isatty (shell_terminal);

    if (shell_is_interactive) {
        /* Loop */
        while (tcgetpgrp (shell_terminal) != (shell_gpid = getpgrp())) {
            kill (- shell_gpid, SIGTTIN);

            /* Ignore interactive and job-control signals */
            signal (SIGINT, SIG_IGN);
            signal (SIGQUIT, SIG_IGN);
            signal (SIGTSTP, SIG_IGN);
            signal (SIGTTOU, SIG_IGN);
            signal (SIGCHLD, SIG_IGN);
            
            /* Put ourselves in our own process group */
            shell_gpid = getpid();
            if (setpgid (shell_gpid, shell_gpid) < 0) {
                perror("Couldn't put the shell in its own process group");
                exit(1);
            }
            /* Grab control of the terminal */
            tcsetpgrp(shell_terminal, shell_gpid);
            /* Save default terminal attributes for shell */
            /* Return a list containing the tty attributes for fd */
            tcgetattr(shell_terminal, &shell_tmodes);
        }
    }
}