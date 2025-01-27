/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:34:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:28:08 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	alloc_j(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*new_cmd(char *str)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(sizeof(char) * alloc_j(str) + 1);
	j = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		else
		{
			new_cmd[j] = str[i];
			i++;
			j++;
		}
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

static void	exec_main_next(t_shell *shell, t_token *token, char **envp)
{
	int		terminal;

	terminal = 0;
	terminal = in_out(token, 0);
	if (token[0].id == 10)
		binary_option(shell, token, envp);
	else if (token[0].id == 11)
		echo(token, 0);
	else if (token[0].id == 12)
		cd(token[1].str);
	else if (token[0].id == 13)
		pwd();
	else if (token[0].id == 14)
		export(shell, token, 0);
	else if (token[0].id == 15)
		unset(shell, token, 0);
	else if (token[0].id == 16)
		env(shell);
	else if (token[0].id == 17)
		ft_exit(token, 0);
	if (terminal)
		dup2(terminal, STDOUT_FILENO);
	if (token[0].id > 10)
		shell->last_exit_status = 0;
}

static void	simple_pipe_exec(t_shell *shell, t_token *token)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		pipex_simple(token, shell);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit_status = 128 + WTERMSIG(status);
	}
}

void	exec_main(t_token *token, char **envp, t_shell *shell)
{
	int		status;
	pid_t	pid;

	if (check_pipe(token) == 1)
		simple_pipe_exec(shell, token);
	else if (check_pipe(token) == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			pipex_multi(token, shell);
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
	}
	else
		exec_main_next(shell, token, envp);
	return ;
}
