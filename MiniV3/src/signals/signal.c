#include "../../minishell.h"

void    sigint_handler(int sig) //IRIS (sigint_handler and manage_signals function)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    manage_signals(void)
{
    signal(SIGQUIT, SIG_IGN); //IRIS (sig_ign ignores the "\"" signal, i added the signal stuff in main)
    signal(SIGINT, &sigint_handler);
}