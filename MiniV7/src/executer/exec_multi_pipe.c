/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:52:11 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 21:06:26 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	joining_command(t_utils *utils, t_token *token, t_shell *shell)
{
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, token[shell->index].str);
	utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, " ");
	shell->index++;
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
