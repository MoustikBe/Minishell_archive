/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:06:06 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 16:06:13 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_process_menu(t_shell *shell, t_token *token, char **cmd_exec)
{
	if (check_cmd_quotes(cmd_exec[0]) == 2)
		echo(token, 0);
	else if (check_cmd_quotes(cmd_exec[0]) == 3)
		cd(token[1].str);
	else if (check_cmd_quotes(cmd_exec[0]) == 4)
		pwd();
	else if (check_cmd_quotes(cmd_exec[0]) == 5)
		export(shell, token, 0);
	else if (check_cmd_quotes(cmd_exec[0]) == 6)
		unset(shell, token, 0);
	else if (check_cmd_quotes(cmd_exec[0]) == 7)
		env(shell);
	else if (check_cmd_quotes(cmd_exec[0]) == 8)
		exit(0);
	exit(0);
}

static void	child_process_fd(char *file_in)
{
	int	fd_in;

	fd_in = open(file_in, O_RDONLY);
	if (fd_in < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

static void	child_join_char(t_utils *utils, t_token *token)
{
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, token[utils->i].str);
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, " ");
	utils->i++;
}

static void	inter_step(int fd[2])
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	child_process(int fd[2], t_token *tok, char *file_in, t_shell *shell)
{
	char	*path;
	char	**cmd_exec;
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	if (file_in)
		child_process_fd(file_in);
	inter_step(fd);
	u->cmp_cmd_1 = calloc(1, 1);
	while (tok[u->i].id != 6)
	{
		if (tok[u->i].id == 4 || (tok[u->i].id == 5
				&& str_cmp(tok[0].str, "cat") == 0
				&& str_cmp(tok[0].str, "/bin/cat") == 0) || tok[u->i].id == 40)
			u->i++;
		else
			child_join_char(u, tok);
	}
	cmd_exec = ft_split(u->cmp_cmd_1, ' ');
	free(u->cmp_cmd_1);
	if (check_cmd_quotes(cmd_exec[0]) > 1)
		child_process_menu(shell, tok, cmd_exec);
	path = make_path(cmd_exec[0], shell);
	execve(path, cmd_exec, NULL);
}

static void	parent_join_char(t_utils *utils, t_token *token)
{
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, token[utils->i].str);
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, " ");
	utils->i++;
}

static void	parent_inter_step(int fd[2])
{
	wait(0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

static void	parent_file_4(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
	file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
}

static void	parent_file_40(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
	file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
}

static void	parent_file_5(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
	file = open(fd_mngt, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	free(fd_mngt);
}

static void	parent_menu(t_utils *u, t_token *token,
t_shell *shell, char **cmd_exec)
{
	if (check_cmd_quotes(cmd_exec[0]) == 2)
		echo(token, u->i_copy);
	else if (check_cmd_quotes(cmd_exec[0]) == 3)
		cd(token[1].str);
	else if (check_cmd_quotes(cmd_exec[0]) == 4)
		pwd();
	else if (check_cmd_quotes(cmd_exec[0]) == 5)
		export(shell, token, u->i_copy);
	else if (check_cmd_quotes(cmd_exec[0]) == 6)
		unset(shell, token, u->i_copy);
	else if (check_cmd_quotes(cmd_exec[0]) == 7)
		env(shell);
	else if (check_cmd_quotes(cmd_exec[0]) == 8)
		exit(0);
	free(u->cmp_cmd_1);
	exit(0);
}

static void	parent_file_mngt(t_utils *u, t_token *token)
{
	while (token[u->i].str)
	{
		if (token[u->i].id == 4)
			parent_file_4(u, token);
		else if (token[u->i].id == 40)
			parent_file_40(u, token);
		else if (token[u->i].id == 5)
			parent_file_5(u, token);
		u->i++;
	}
}

static void	parent_buildcharloop(t_utils *u, t_token *token)
{
	while (token[u->i].str)
	{
		if (token[u->i].id == 4 || (token[u->i].id == 5
				&& str_cmp(token[u->i_copy].str, "cat") == 0
				&& str_cmp(token[u->i_copy].str, "/bin/cat") == 0)
			|| token[u->i].id == 40)
			u->i++;
		else
			parent_join_char(u, token);
	}
}

void	parent_process(int fd[2], t_token *token, t_shell *shell)
{
	t_utils	*u;
	char	**cmd_exec;
	char	*path;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	u->cmp_cmd_1 = calloc(1, 1);
	while (token[u->i].id != 6)
		u->i++;
	u->i++;
	u->i_copy = u->i;
	parent_buildcharloop(u, token);
	parent_inter_step(fd);
	u->i = u->i_copy;
	parent_file_mngt(u, token);
	cmd_exec = ft_split(u->cmp_cmd_1, ' ');
	if (check_cmd_quotes(cmd_exec[0]) > 1)
		parent_menu(u, token, shell, cmd_exec);
	path = make_path(cmd_exec[0], shell);
	execve(path, cmd_exec, NULL);
}

void	pipex_simple(t_token *token, t_shell *shell)
{
	int		i;
	int		fd[2];
	char	*fd_in;
	char	*fd_out;
	pid_t	pid;

	i = 0;
	fd_in = NULL;
	fd_out = NULL;
	while (token[i].str)
	{
		if (token[i].id == 5)
			fd_in = ft_strdup(token[i].str);
		else if (token[i].id == 4)
			fd_out = ft_strdup(token[i].str);
		i++;
	}
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		child_process(fd, token, fd_in, shell);
	else
		parent_process(fd, token, shell);
}
