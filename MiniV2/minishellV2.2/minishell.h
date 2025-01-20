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

typedef struct t_token
{
  char *str;
  int id;
}    t_token;
// -- End -- //

// -- Declaration of external function -- //

// parsing/checker/main_check.c //
int main_check(char *command);
int cmd_check(char *command, char *cmp_cmd);

// parsing/checker/option_check.c //
int check_bin(char *command);

// parsing/token/token.c //
void    token(char *command, t_shell *shell);

// parsing/token/token_id.c //
void    set_id(t_token *token, int j);

// parsing/checker/option_check.c //
int echo_checker(char *command);

// src/mini_lib/utils.c //
int ft_strlen(char *str);

// src/mini_lib/ft_split.c //
char	**ft_split(char *s, char c);

// -- End of declaration -- //
#endif