/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:52:33 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:57:41 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <signal.h>
// -- End of include -- //
// -------------------- //
// # -- STRUCTURE -- # //
typedef struct t_utils
{
	int		i;
	int		j;
	int		len;
	int		flag;
	int		i_copy;
	int		j_copy;
	int		i_exit;
	int		ret_val;
	int		temp_fd;
	int		quot_flag;
	int		in_quotes;
	int		in_quote;
	char	*cmp_cmd_1;
}	t_utils;

typedef struct t_split
{
	int	count;
	int	word;
	int	in_quotes;
	int	in_quote;
	int	s_start;
	int	new_alloc;
	int	inside;
	int	i_wd;
	int	i;
	int	j;
	int	index;
	int	i_qs;
	int	i_q;
}	t_split;

typedef struct t_env
{
	char			*env_var;
	struct t_env	*next;
}	t_env;

typedef struct t_shell
{
	char	*cmd;
	int		fd[2];
	int		fd_temp;
	int		nb_cmd;
	int		index;
	int		len_token;
	int		error;
	char	*env_cmd;
	int		flag;
	int		status;
	int		last_exit_status;
	t_env	*env;
}	t_shell;

typedef struct t_token
{
	char	*str;
	int		id;
}	t_token;
// -- End -- //

// -- Declaration of external function -- //
// -- Parsing -- //
// src/parsing/parsing_main.c //
int		parsing_main(char *cmd);
int		pars_except(char *cmd);
// src/parsing/pars_bin.c //
int		direct_bin(char *cmd);
// src/parsing/pars_check.c //
int		check_quotes(char *cmd);
int		check_bin(char *command);
int		check_dolar(char *cmd);
int		check_syntax(char *cmd);
// src/parsing/pars_cd.c //
int		pars_cd(char **pars_cmd);
// src/parsing/pars_cmd.c // 
int		check_cmd_quotes(char *cmd_check);
// src/parsing/pars_export.c //
int		pars_export(char **pars_cmd);
// src/parsing/pars_env.c //
int		pars_syntax(char **pars_cmd);
// src/parsing/pars_dolar.c //
int		pars_dolar(char **pars_cmd);
// src/parsing/pars_char.c //
int		check_bin_quotes(char *command);

// -- Herdoc -- //
// src/heredoc/herdoc_exec.c //
void	exec_herdoc(t_shell *shell);
void	replace_heredoc(t_shell *shell);
// src/heredoc/herdoc_expansion.c //
void	heredoc_expansion(t_shell *shell, char *gnl_val, int temp_fd);
// src/herdoc/heredoc_main.c //
void	here_doc(t_shell *shell);
// src/herdoc/heredoc_utils.c //
void	cal_len_heredoc(t_shell *shell, t_utils *utils);
void	copy_heredoc(t_shell *shell, t_utils *utils,
			char *new_cmd, char *tmp_file);
int		check_env_var(char *str);

// -- Signals -- //
void	sigint_handler(int sig);
void	manage_signals(void);

// -- Organizer -- //
// src/organizer/cmd_cleaner.c //
void	cmd_cleaner(t_shell *shell);
int		verif_quotes(char *cmd);
void	cmd_len_else(t_utils *u);
void	cmd_copy_else(t_utils *u, char *pipe_cmd);
// src/organizer/cmd_utils.c //
void	cmd_cleaner_len(t_utils *u, t_shell *shell);
void	cmd_cleaner_cutils(t_utils *u, t_shell *shell, char *pipe_cmd);
void	cmd_cleaner_copy(t_utils *u, t_shell *shell, char *pipe_cmd);
void	quote_management(t_shell *shell, t_utils *u);

// -- Env -- // 
// src/env/env_main.c //
void	copy_env(char **envp, t_shell *shell);
// src/env/env_expansion.c //
void	expansion(t_shell *shell);
int		search_in_env(t_shell *shell, char *cmp_cmd);
int		exit_val_mngt(t_shell *shell, t_utils *utils, int j_copy);
void	dolar_expansion(t_shell *shell, t_utils *utils);
void	check_len_expans(t_shell *shell, t_utils *utils);
// src/env/env_expansion_copy.c //
int		copy_env_cmd(int j_copy, int i, t_shell *shell);
void	copy_for_expansion(t_shell *shell, t_utils *utils, char *cmp_cmd);
void	copy_in_expansion(t_shell *shell, t_utils *utils);
void	copy_in_envcmd(t_env *env_v, t_utils *utils,
			t_shell *shell, int j_copy);
void	building_cmp_cmd(t_utils *utils, t_shell *shell, int *i);
// src/env/env_expansion_utils.c //
void	loop_utils(t_env *env_v, t_utils *utils);
int		if_possibility(t_utils *utils, char *cmp_cmd_1, char *cmp_cmd_2);
void	inter_step_expansion(t_utils *utils, int *i);
void	else_possibility(char *cmp_cmd_1, char *cmp_cmd_2);
void	utils_inter_step(t_utils *utils, t_shell *shell);
// src/env/env_utils.c //
int		search_in_env_writed(t_shell *shell, char *cmp_cmd, int temp_fd);

// -- Token -- //
// src/token/token_main.c //
t_token	*token_main(char *cmd, t_token *token, t_shell *shell);
// src/token/token_set.c //
void	token_id(t_token *token, int i, t_shell *shell);
// src/token/token_id.c //
int		is_outfile(t_token *token, int i, t_shell *shell, int j);
int		is_outfile_append(t_token *token, int i, t_shell *shell, int j);
int		is_cmd(t_token *token, int i);
int		is_flag(t_token *token, int i);
// src/token/token_id_utils.c //
int		is_var(t_token *token, int i);
int		is_char(t_token *token, int i);
int		is_pipe(t_token *token, int i);
int		is_infile(t_token *token, int i, t_shell *shell);
// src/token/token_utils.c //
int		len_token(char *cmd);
int		token_copy(t_token *token, char *cmd, int i, int j);
// src/token/token_utils_next.c //
void	free_all_token(t_token *token);
int		len_for_token(char *cmd, int i);
// src/token/token_pars.c // 
void	token_parser(t_token *token, t_shell *shell, int len);

// -- Executer -- //
// src/executer/exec_main.c //
void	exec_main(t_token *token, char **envp, t_shell *shell);
// src/executer/exec_main_path.c //
char	*make_path(char *token, t_shell *shell);
int		check_path(t_shell *shell);
void	binary_option(t_shell *shell, t_token *token, char **envp);
void	exec_bin(t_token *token, char **envp, t_shell *shell);
void	exec_bin_next(t_token *token, t_utils *utils);
// src/executer/exec_main_utils.c //
int		check_pipe(t_token *token);
void	verif_in(t_token *token, int i);
// src/executer/exec_pipe.c //
void	pipex_simple(t_token *token, t_shell *shell);
void	parent_buildcharloop(t_utils *u, t_token *token);
void	inter_step_pipe(int fd[2]);
void	child_join_char(t_utils *utils, t_token *token);
// src/executer/exec_pipe_file.c //
void	parent_file_4(t_utils *utils, t_token *token);
void	parent_file_40(t_utils *utils, t_token *token);
void	parent_file_5(t_utils *utils, t_token *token);
void	parent_file_mngt(t_utils *u, t_token *token);
void	child_process_fd(char *file_in);
// src/executer/exec_pipe_subproc.c //
void	child_process(int fd[2], t_token *tok, char *file_in, t_shell *shell);
void	child_process_menu(t_shell *shell, t_token *token, char **cmd_exec);
void	parent_process(int fd[2], t_token *token, t_shell *shell);
void	parent_menu(t_utils *u, t_token *token,
			t_shell *shell, char **cmd_exec);
void	parent_inter_step(int fd[2]);
// src/executer/exec_multi_pipe.c //
void	pipex_multi(t_token *token, t_shell *shell);
void	joining_command(t_utils *utils, t_token *token, t_shell *shell);
// src/executer/exec_multi_file.c //
void	last_step_4(t_token *token, int i);
void	last_step_40(t_token *token, int i);
void	command_exec_4(t_shell *shell, t_token *token);
void	command_exec_5(t_shell *shell, t_token *token);
void	command_exec_40(t_shell *shell, t_token *token);
// src/executer/exec_multi_process.c //
void	sub_process(t_shell *shell, t_token *token, pid_t pid);
void	createprocessus(pid_t pid, t_shell *shell, t_token *token);
void	wait_execution(int nb_cmd);
void	command_execution(t_token *token, t_shell *shell);
void	command_execution_next(t_shell *shell, t_token *token,
			char **cmd_exec, int i_copy);
// src/executer/exec_multi_step.c //
void	to_nb_cmd(t_shell *shell);
void	from_nb_cmd(t_shell *shell);
void	step_1_next(t_token *token, t_shell *shell, char **cmd_exec);
void	step_1(pid_t pid, t_token *token, t_shell *shell);
void	last_step(t_shell *shell, t_token *token, pid_t pid);

// -- Builins -- // 
void	echo(t_token *token, int j);
void	pwd(void);
void	cd(char *path);
void	export(t_shell *shell, t_token *token, int j);
void	env(t_shell *shell);
void	unset(t_shell *shell, t_token *token, int j);
void	ft_exit(t_token *token, int j);
char	*build_cmp(char *str);
int		in_out(t_token *token, int j);

// -- Micro lib -- //
// src/micro_lib/utils.c //
int		ft_strlen(char *str);
int		str_cmp(char *cmd, char *cmp_cmd);
int		str_cmp_quotes(char *cmd, char *cmp_cmd);
void	free_array(char **arr);
int		ft_isalnum(int alph);
// src/micro_lib/ft_split.c //
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*word_dup_special(char *str, int start, int finish);
// src/micro_lib/ft_split_utils.c //
int		init_struct_split(t_split *split, char *s);
int		word_dup_len(t_split *sp, int finish, char *str);
int		copy_words(t_split *sp, char **split, char *s);
// src/micro_lib/ft_split_quote.c //
void	cw_scenario_1(t_split *sp, char *s, char c, int *x);
void	change_for_0(t_split *sp, char *s, int *x);
void	change_for_1(t_split *sp, char *s, int *x);
// src/micro_lib/split_basic.c //
char	**ft_split_basic(char *s, char c);
// src/micro_lib/get_next_line.c //
char	*get_next_line(int fd);
// src/micro_lib/put_nbr.c 
void	ft_putnbr(int n);
// src/micro_lib/ft_itoa.c // 
char	*ft_itoa(int n);
// src/micro_lib/init_struct.c //
void	init_var_utils(t_utils *utils);
// src/micro_lib/utils_next.c //
char	*clean_name(char *src);
char	*ft_strdup(char *src);
void	ft_putchar_fd(char c, int fd);

// -- End of declaration -- //
#endif