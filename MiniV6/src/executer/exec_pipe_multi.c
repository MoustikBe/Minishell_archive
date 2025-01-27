/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:52:11 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/20 10:02:13 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	step_1_next(t_token *token, t_shell *shell, char **cmd_exec)
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
		ft_exit();
	exit(0);
}

void	step_1(pid_t pid, t_token *token, t_shell *shell)
{
	char	*path;
	char	*cmd_join;
	char	**cmd_exec;

	if (pid == 0)
	{
		dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd[0]);
		close(shell->fd[1]);
		shell->index = 0;
		cmd_join = calloc(1, 1);
		while (token[shell->index].id != 6)
		{
			cmd_join = ft_strjoin(cmd_join, token[shell->index].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			shell->index++;
		}
		cmd_exec = ft_split(cmd_join, ' ');
		if (check_cmd_quotes(cmd_exec[0]) > 1)
			step_1_next(token, shell, cmd_exec);
		path = make_path(cmd_exec[0], shell);
		execve(path, cmd_exec, NULL);
		exit(2);
	}
}

void	to_nb_cmd(t_shell *shell)
{
	close(shell->fd[1]);
	shell->fd_temp = shell->fd[0];
	pipe(shell->fd);
}

void static	command_exec_4(t_shell *shell, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[shell->index].str);
	file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
	shell->index++;
}

static void	command_exec_5(t_shell *shell, t_token *token)
{
	char	*fd_mngt;

	fd_mngt = clean_name(token[shell->index].str);
	if (access(fd_mngt, O_RDONLY) != 0)
	{
		write(2, "Minishell : No such file or directory\n", 7);
		free(fd_mngt);
		shell->last_exit_status = 1;
		exit(1);
	}
	free(fd_mngt);
	shell->index++;
}

static void	command_exec_40(t_shell *shell, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[shell->index].str);
	file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
	shell->index++;
}

static void	command_execution_next(t_shell *shell, t_token *token,
char **cmd_exec, int i_copy)
{
	if (check_cmd_quotes(cmd_exec[0]) == 2)
		echo(token, i_copy);
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
		ft_exit();
	exit(0);
}

static void	joining_command(t_utils *utils, t_token *token, t_shell *shell)
{
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, token[shell->index].str);
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, " ");
	shell->index++;
}

void	command_execution(t_token *token, t_shell *shell)
{
	char	*path;
	char	**cmd_exec;
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	u->cmp_cmd_1 = calloc(1, 1);
	u->i_copy = shell->index;
	while (token[shell->index].id != 6 && token[shell->index].str)
	{
		if (token[shell->index].id == 4)
			command_exec_4(shell, token);
		else if (token[shell->index].id == 5 && str_cmp(token[u->i_copy].str,
				"cat") == 0 && str_cmp(token[u->i_copy].str, "/bin/cat") == 0)
			command_exec_5(shell, token);
		else if (token[shell->index].id == 40)
			command_exec_40(shell, token);
		else
			joining_command(u, token, shell);
	}
	cmd_exec = ft_split(u->cmp_cmd_1, ' ');
	if (check_cmd_quotes(cmd_exec[0]) > 1)
		command_execution_next(shell, token, cmd_exec, u->i_copy);
	path = make_path(cmd_exec[0], shell);
	execve(path, cmd_exec, NULL);
}

void	createprocessus(pid_t pid, t_shell *shell, t_token *token)
{
	if (pid == 0)
	{
		close(shell->fd[0]);
		dup2(shell->fd_temp, STDIN_FILENO);
		dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd_temp);
		close(shell->fd[1]);
		command_execution(token, shell);
	}
	if (shell->nb_cmd > 1)
	{
		close(shell->fd_temp);
		close(shell->fd[1]);
		shell->fd_temp = shell->fd[0];
		pipe(shell->fd);
	}
	shell->nb_cmd--;
	while (token[shell->index].id != 6)
		shell->index++;
	shell->index++;
}

void	sub_process(t_shell *shell, t_token *token, pid_t pid)
{
	if (shell->index == 0)
	{
		while (token[shell->index].id != 6)
			shell->index++;
	}
	shell->index++;
	while (shell->nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			exit(2);
		if (token[shell->index].id == 6)
			shell->index++;
		createprocessus(pid, shell, token);
	}
}

void	from_nb_cmd(t_shell *shell)
{
	close(shell->fd_temp);
	close(shell->fd[1]);
	shell->fd_temp = shell->fd[0];
}

static void	last_step_4(t_token *token, int i)
{
	int		file;
	char	*fd_mngt;

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

static void	last_step_40(t_token *token, int i)
{
	int		file;
	char	*fd_mngt;

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

void	last_step(t_shell *shell, t_token *token, pid_t pid)
{
	int		i;

	i = shell->index;
	if (pid == 0)
	{
		dup2(shell->fd[0], STDIN_FILENO);
		close(shell->fd[1]);
		close(shell->fd[0]);
		while (token[i].str)
		{
			if (token[i].id == 4)
				last_step_4(token, i);
			else if (token[i].id == 40)
				last_step_40(token, i);
			i++;
		}
		command_execution(token, shell);
		exit(0);
	}
	close(shell->fd[0]);
}

void	wait_execution(int nb_cmd)
{
	int	status;

	while (nb_cmd--)
	{
		waitpid(-1, &status, 0);
	}
}

static int	len_array(t_shell *shell)
{
	int		i;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split(shell->cmd, '|');
	while (split_cmd[i])
	{
		free(split_cmd[i]);
		i++;
	}
	free(split_cmd);
	return (i);
}

void	pipex_multi(t_token *token, t_shell *shell)
{
	int		i;
	pid_t	pid;

	shell->index = 0;
	i = len_array(shell);
	shell->nb_cmd = i - 2;
	pipe(shell->fd);
	pid = fork();
	if (pid == -1)
		printf("ERROR\n");
	step_1(pid, token, shell);
	close(shell->fd[1]);
	to_nb_cmd(shell);
	sub_process(shell, token, pid);
	from_nb_cmd(shell);
	pid = fork();
	if (pid == -1)
		exit(2);
	last_step(shell, token, pid);
	wait_execution(shell->nb_cmd + 3);
	close(shell->fd_temp);
	return ;
}
