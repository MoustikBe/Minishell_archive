#ifndef MINISHELL
# define MINISHELL
// -- Include of the external lib -- //
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
// -- End of include -- //
// -------------------- //
// # -- STRUCTURE -- # //
typedef struct t_shell
{
    char **cmd_token;
}    t_shell;

// -- End -- //

// -- Declaration of external function -- //

// parsing/checker/main_check.c //
int main_check(char *command);

// parsing/token.c //
void    token(char *command, t_shell *shell);

// parsing/checker/option_check.c //
int echo_checker(char *command);

// src/mini_lib/utils.c //
int ft_strlen(char *str);

// src/mini_lib/ft_split.c //
char	**ft_split(char *s, char c);

// -- End of declaration -- //
#endif