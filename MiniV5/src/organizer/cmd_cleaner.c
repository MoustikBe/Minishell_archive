/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:48:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/20 13:30:58 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cmd_cleaner_len(t_utils *u, t_shell *shell)
{
	while (shell->cmd[u->i])
	{
		if ((shell->cmd[u->i] == '<' && shell->cmd[u->i + 1] == ' ')
			|| (shell->cmd[u->i] == '>' && shell->cmd[u->i + 1] == ' '))
		{
			u->i++;
			while (shell->cmd[u->i] == ' ')
				u->i++;
		}
		else if (shell->cmd[u->i] == '|')
		{
			if (shell->cmd[u->i - 1] != ' ')
				u->len++;
			if (shell->cmd[u->i + 1] != ' ')
				u->len++;
			u->len++;
			u->i++;
		}
		else
		{
			u->i++;
			u->len++;
		}
	}
}

static void	cmd_cleaner_cutils(t_utils *u, t_shell *shell, char *pipe_cmd)
{
	pipe_cmd[u->j] = shell->cmd[u->i];
	u->j++;
	while (shell->cmd[u->i] == ' ')
		u->i++;
}

static void	cmd_cleaner_copy(t_utils *u, t_shell *shell, char *pipe_cmd)
{
	while (shell->cmd[u->i])
	{
		if ((shell->cmd[u->i] == '<' && shell->cmd[u->i + 1] == ' ')
			|| (shell->cmd[u->i] == '>' && shell->cmd[u->i + 1] == ' '))
			cmd_cleaner_cutils(u, shell, pipe_cmd);
		else if (shell->cmd[u->i] == '|')
		{
			if (shell->cmd[u->i - 1] == ' ')
				pipe_cmd[u->j++] = '|';
			else
			{
				pipe_cmd[u->j] = ' ';
				pipe_cmd[u->j + 1] = '|';
				u->j = u->j + 2;
			}
			if (shell->cmd[u->i + 1] != ' ')
				pipe_cmd[u->j++] = ' ';
			u->i++;
		}
		else
			pipe_cmd[u->j++] = shell->cmd[u->i++];
	}
}

void	cmd_cleaner(t_shell *shell)
{
	char	*pipe_cmd;
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	cmd_cleaner_len(u, shell);
	if (shell->cmd[u->i - 1] != ' ')
		u->len++;
	pipe_cmd = malloc(sizeof(char) * u->len + 3);
	u->i = 0;
	cmd_cleaner_copy(u, shell, pipe_cmd);
	if (shell->cmd[u->i - 1] != ' ')
	{
		pipe_cmd[u->j] = ' ';
		u->j++;
	}
	pipe_cmd[u->j] = '\0';
	free(u);
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
