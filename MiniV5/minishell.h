#ifndef MINISHELL
# define MINISHELL
// -- Include of the external lib -- //
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
#include <signal.h>
// -- End of include -- //
// -------------------- //
// # -- STRUCTURE -- # //
typedef struct t_utils
{
	int i;
	int j;
	int len;
	int flag;
	int i_copy;
	int j_copy;
	int i_exit;
	int ret_val;
	int temp_fd;
	int quot_flag;
	char *cmp_cmd_1;
}	t_utils;

typedef struct t_split
{
	int	count;
	int	word;
	int	in_quotes;
	int	in_quote;
	/* WORD_DUP*/
	int		s_start;
	int		new_alloc;
	int		inside;
	int		i_wd;
	/* MAIN_SPLIT*/
	int	i;
	int	j;
	int	index;
	int	i_qs;
	int	i_q;
}	t_split;

typedef struct t_env
{
	char *env_var;
	struct t_env *next;
}	t_env;

typedef struct t_shell
{
	char *cmd;
	int fd[2];
	int fd_temp;
	int nb_cmd;
	int index;
	int	len_token;
	int error;
	char *env_cmd;

	/* IN TEST */
	int status;
	int last_exit_status;
	/* IN TEST */

	t_env *env;
}	t_shell;

typedef struct t_token
{
    char *str; 
    int id;
}    t_token;
// -- End -- //

// -- Declaration of external function -- //

// -- Parsing -- //
// src/parsing/parsing_main.c //
int parsing_main(char *cmd);
int pars_except(char *cmd);
// src/parsing/pars_bin.c //
int direct_bin(char *cmd);
// src/parsing/pars_check.c //
int check_quotes(char *cmd);
int check_bin(char *command);
int check_dolar(char *cmd);
int check_syntax(char *cmd);
// src/parsing/pars_cd.c //
int pars_cd(char **pars_cmd);
// src/parsing/pars_cmd.c // 
int check_cmd_quotes(char *cmd_check);
// src/parsing/pars_export.c //
int pars_export(char **pars_cmd);
// src/parsing/pars_env.c //
int pars_syntax(char **pars_cmd);
// src/parsing/pars_dolar.c //
int pars_dolar(char **pars_cmd);
// src/parsing/pars_char.c //
int check_bin_quotes(char *command);

// -- Herdoc -- //
// src/heredoc/herdoc_exec.c //
void exec_herdoc(t_shell *shell);
void replace_heredoc(t_shell *shell);
int check_env_var(char *str);
// src/heredoc/herdoc_expansion.c //
void heredoc_expansion(t_shell *shell, char *gnl_val, int temp_fd);
// src/herdoc/hereedoc_main.c //
void here_doc(t_shell *shell);

// -- Signals -- //
void    sigint_handler(int sig);
void    manage_signals(void);

// -- Organizer -- //
void cmd_cleaner(t_shell *shell);
int verif_quotes(char *cmd);


// -- Env -- // 
// src/env/env_main.c //
void copy_env(char **envp, t_shell *shell);
// src/env/env_expansion.c //
void expansion(t_shell *shell);
int search_in_env(t_shell *shell, char *cmp_cmd);
// src/env/env_utils.c //
int search_in_env_writed(t_shell *shell, char *cmp_cmd, int temp_fd);


// -- Token -- //
// src/token/token_main.c //
t_token *token_main(char *cmd, t_token *token, t_shell *shell);
// src/token/token_set.c //
void token_id(t_token *token, int i);
// src/token/token_id.c // 
int is_var(t_token *token, int i);
int is_char(t_token *token, int i);
int is_pipe(t_token *token, int i);
int is_infile(t_token *token, int i);
int is_outfile(t_token *token, int i);
int is_outfile_append(t_token *token, int i);
int is_cmd(t_token *token, int i);
int is_flag(t_token *token, int i);
// src/token/token_utils.c //
void free_all_token(t_token *token);
int len_for_token(char *cmd, int i);
int len_token(char *cmd);
int token_copy(t_token *token, char *cmd, int i, int j);
// src/token/token_pars.c // 
void token_parser(t_token *token, t_shell *shell, int len);

// -- Executer -- //
// src/executer/exec_main.c //
void exec_main(t_token *token, char **envp, t_shell *shell);
char *make_path(char *token, t_shell *shell);
// src/executer/exec_pipe.c //
void pipex_simple(t_token *token, t_shell *shell);
// src/executer/exec_pipe_multi.c //
void pipex_multi(t_token *token, t_shell *shell);

// -- Builins -- // 
void echo(t_token *token, int j);
void pwd(void);
void cd(char *path);
void export(t_shell *shell, t_token *token, int j);
void env(t_shell *shell);
void unset(t_shell *shell, t_token *token, int j);
void ft_exit(void);
char *build_cmp(char *str);
int in_out(t_token *token, int j);

// -- Micro lib -- //
// src/micro_lib/utils.c //
int ft_strlen(char *str);
int str_cmp(char *cmd, char *cmp_cmd);
int str_cmp_quotes(char *cmd, char *cmp_cmd);
void free_array(char **arr);
int	ft_isalnum(int alph);
char	*ft_strdup(char *src);
char *clean_name(char *src);
void	ft_putchar_fd(char c, int fd);
// src/micro_lib/ft_split.c //
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
// src/micro_lib/split_basic.c //
char	**ft_split_basic(char *s, char c);
// src/micro_lib/get_next_line.c //
char	*get_next_line(int fd);
// src/micro_lib/put_nbr.c 
void	ft_putnbr(int n);
// src/micro_lib/ft_itoa.c // 
char	*ft_itoa(int n);
// src/micro_lib/init_struct.c //
void init_var_utils(t_utils *utils);

// -- End of declaration -- //
#endif