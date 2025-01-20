/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:06:06 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 23:32:31 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(int fd[2], t_token *token, char *file_in, t_shell *shell)
{
	int		fd_in;
	int		i;
	char	**cmd_exec;
	char	*path;
	char	*cmd_join;

	i = 0;
	if (file_in)
	{
		fd_in = open(file_in, O_RDONLY);
		if (fd_in < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	i = 0;
	cmd_join = calloc(1, 1);
	while (token[i].id != 6)
	{
		if (token[i].id == 4 || (token[i].id == 5
				&& str_cmp(token[0].str, "cat") == 0
				&& str_cmp(token[0].str, "/bin/cat") == 0) || token[i].id == 40)
			i++;
		else
		{
			cmd_join = ft_strjoin(cmd_join, token[i].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			i++;
		}
	}
	cmd_exec = ft_split(cmd_join, ' ');
	free(cmd_join);
	if (check_cmd_quotes(cmd_exec[0]) > 1)
	{
		if (check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, shell, 0);
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
	path = make_path(cmd_exec[0], shell);
	execve(path, cmd_exec, NULL);
}

void	parent_process(int fd[2], t_token *token, t_shell *shell)
{
	int		i;
	int		file;
	int		i_copy;
	char	**cmd_exec;
	char	*path;
	char	*cmd_join;
	char	*fd_mngt;

	i = 0;
	cmd_join = NULL;
	cmd_join = calloc(1, 1);
	while (token[i].id != 6)
		i++;
	i++;
	i_copy = i;
	while (token[i].str)
	{
		if (token[i].id == 4 || (token[i].id == 5
				&& str_cmp(token[i_copy].str, "cat") == 0
				&& str_cmp(token[i_copy].str, "/bin/cat") == 0)
			|| token[i].id == 40)
			i++;
		else
		{
			cmd_join = ft_strjoin(cmd_join, token[i].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			i++;
		}
	}
	wait(0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	i = i_copy;
	while (token[i].str)
	{
		if (token[i].id == 4)
		{
			fd_mngt = ft_strdup(token[i].str);
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
		else if (token[i].id == 40)
		{
			fd_mngt = ft_strdup(token[i].str);
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
		else if (token[i].id == 5)
		{
			fd_mngt = ft_strdup(token[i].str);
			file = open(fd_mngt, O_RDONLY);
			if (file == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			free(fd_mngt);
		}
		i++;
	}
	cmd_exec = ft_split(cmd_join, ' ');
	if (check_cmd_quotes(cmd_exec[0]) > 1)
	{
		if (check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, shell, i_copy);
		else if (check_cmd_quotes(cmd_exec[0]) == 3)
			cd(token[1].str);
		else if (check_cmd_quotes(cmd_exec[0]) == 4)
			pwd();
		else if (check_cmd_quotes(cmd_exec[0]) == 5)
			export(shell, token, i_copy);
		else if (check_cmd_quotes(cmd_exec[0]) == 6)
			unset(shell, token, i_copy);
		else if (check_cmd_quotes(cmd_exec[0]) == 7)
			env(shell);
		else if (check_cmd_quotes(cmd_exec[0]) == 8)
			exit(0);
		free(cmd_join);
		exit(0);
	}
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
	(void)fd_out;
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
		child_process(fd, token, fd_in, shell);
	else
		parent_process(fd, token, shell);
}
