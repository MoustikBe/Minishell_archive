/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:52:33 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:57:32 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	wait_execution(int nb_cmd)
{
	int	status;

	while (nb_cmd--)
	{
		waitpid(-1, &status, 0);
	}
}

void	command_execution_next(t_shell *shell, t_token *token,
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
		ft_exit(token, i_copy);
	exit(0);
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
