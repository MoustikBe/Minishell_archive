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

void	cmd_cleaner_len(t_utils *u, t_shell *shell)
{
	while (shell->cmd[u->i])
	{
		quote_management(shell, u);
		if ((shell->cmd[u->i] == '<' && shell->cmd[u->i + 1] == ' '
				&& u->in_quotes == 0 && u->in_quote == 0)
			|| (shell->cmd[u->i] == '>' && shell->cmd[u->i + 1] == ' '
				&& u->in_quotes == 0 && u->in_quote == 0))
		{
			u->i++;
			while (shell->cmd[u->i] == ' ')
				u->i++;
		}
		else if (shell->cmd[u->i] == '|' && u->in_quotes == 0
			&& u->in_quote == 0)
		{
			if (shell->cmd[u->i - 1] != ' ')
				u->len++;
			if (shell->cmd[u->i + 1] != ' ')
				u->len++;
			u->len++;
			u->i++;
		}
		else
			cmd_len_else(u);
	}
}

void	cmd_cleaner_cutils(t_utils *u, t_shell *shell, char *pipe_cmd)
{
	pipe_cmd[u->j] = shell->cmd[u->i];
	u->j++;
	u->i++;
	while (shell->cmd[u->i] == ' ')
		u->i++;
}

void	cmd_cleaner_copy(t_utils *u, t_shell *shell, char *pipe_cmd)
{
	while (shell->cmd[u->i])
	{
		quote_management(shell, u);
		if ((shell->cmd[u->i] == '<' && shell->cmd[u->i + 1] == ' '
				&& u->in_quotes == 0 && u->in_quote == 0)
			|| (shell->cmd[u->i] == '>' && shell->cmd[u->i + 1] == ' '
				&& u->in_quotes == 0 && u->in_quote == 0))
			cmd_cleaner_cutils(u, shell, pipe_cmd);
		else if (shell->cmd[u->i] == '|' && u->in_quote == 0
			&& u->in_quotes == 0)
		{
			if (shell->cmd[u->i - 1] == ' ')
				pipe_cmd[u->j++] = '|';
			else
				cmd_copy_else(u, pipe_cmd);
			if (shell->cmd[u->i + 1] != ' ')
				pipe_cmd[u->j++] = ' ';
			u->i++;
		}
		else
			pipe_cmd[u->j++] = shell->cmd[u->i++];
	}
}

void	quote_management(t_shell *shell, t_utils *u)
{
	if (shell->cmd[u->i] == '"' && u->in_quotes == 0)
		u->in_quotes = 1;
	else if (shell->cmd[u->i] == '\'' && u->in_quote == 0)
		u->in_quote = 1;
	else if (shell->cmd[u->i] == '"' && u->in_quotes == 1)
		u->in_quotes = 0;
	else if (shell->cmd[u->i] == '\'' && u->in_quote == 1)
		u->in_quote = 0;
}
