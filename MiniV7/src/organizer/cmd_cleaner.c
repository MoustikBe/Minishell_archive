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

void	cmd_len_else(t_utils *u)
{
	u->i++;
	u->len++;
}

void	cmd_copy_else(t_utils *u, char *pipe_cmd)
{
	pipe_cmd[u->j] = ' ';
	pipe_cmd[u->j + 1] = '|';
	u->j = u->j + 2;
}

static void	quot_file_checker(t_shell *shell)
{
	int	i;

	i = 0;
	shell->flag = 0;
	while (shell->cmd[i])
	{
		if (i > 0)
			if ((shell->cmd[i] == '<' && shell->cmd[i - 1] == '"')
				|| (shell->cmd[i] == '<' && shell->cmd[i - 1] == '\'')
				|| (shell->cmd[i] == '>' && shell->cmd[i - 1] == '"')
				|| (shell->cmd[i] == '>' && shell->cmd[i - 1] == '\''))
				shell->flag = 1;
		i++;
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
	u->in_quote = 0;
	u->in_quotes = 0;
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
	quot_file_checker(shell);
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
