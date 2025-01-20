/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:48:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:53:04 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cmd_cleaner(t_shell *shell)
{
	int		i;
	int		j;
	int		mem;
	char	*pipe_cmd;

	i = 0;
	j = 0;
	mem = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<' && shell->cmd[i + 1] == ' '
			|| shell->cmd[i] == '>' && shell->cmd[i + 1] == ' ')
		{
			i++;
			while (shell->cmd[i] == ' ')
				i++;
		}
		else if (shell->cmd[i] == '|')
		{
			if (shell->cmd[i - 1] != ' ')
				mem++;
			if (shell->cmd[i + 1] != ' ')
				mem++;
			mem++;
			i++;
		}
		else
		{
			i++;
			mem++;
		}
	}
	if (shell->cmd[i - 1] != ' ')
		mem++;
	pipe_cmd = malloc(sizeof(char) * mem + 3);
	i = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<' && shell->cmd[i + 1] == ' '
			|| shell->cmd[i] == '>' && shell->cmd[i + 1] == ' ')
		{
			pipe_cmd[j] = shell->cmd[i];
			j++;
			while (shell->cmd[i] == ' ')
				i++;
		}
		else if (shell->cmd[i] == '|')
		{
			if (shell->cmd[i - 1] == ' ')
			{
				pipe_cmd[j] = '|';
				j++;
			}
			else
			{
				pipe_cmd[j] = ' ';
				pipe_cmd[j + 1] = '|';
				j = j + 2;
			}
			if (shell->cmd[i + 1] != ' ')
			{
				pipe_cmd[j] = ' ';
				j++;
			}
			i++;
		}
		else
		{
			pipe_cmd[j] = shell->cmd[i];
			i++;
			j++;
		}
	}
	if (shell->cmd[i - 1] != ' ')
	{
		pipe_cmd[j] = ' ';
		j++;
	}
	pipe_cmd[j] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(pipe_cmd);
	free(pipe_cmd);
}

int	verif_quotes(char *cmd)
{
	int	i;
	int	quote_s;
	int	quote_d;

	i = 0;
	quote_s = 0;
	quote_d = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			quote_d++;
		else if (cmd[i] == '\'')
			quote_s++;
		i++;
	}
	if (quote_d % 2 == 0 && quote_s % 2 == 0)
		return (0);
	return (1);
}
