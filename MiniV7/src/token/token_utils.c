/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:14 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/21 10:40:16 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	len_token_utils(t_utils *u, char *cmd)
{
	while (cmd[u->i] == ' ')
	{
		if (u->i == 0)
			u->len--;
		u->i++;
	}
	u->len++;
}

int	len_token(char *cmd)
{
	t_utils	*u;
	int		save_val;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	while (cmd[u->i])
	{
		if (cmd[u->i] == '"' && u->quot_flag == 0)
			u->quot_flag = 1;
		else if (cmd[u->i] == '"' && u->quot_flag == 1)
			u->quot_flag = 0;
		else if (cmd[u->i] == '\'' && u->flag == 0)
			u->flag = 1;
		else if (cmd[u->i] == '\'' && u->flag == 1)
			u->flag = 0;
		if (cmd[u->i] == ' ' && u->quot_flag == 0 && u->flag == 0)
			len_token_utils(u, cmd);
		else
			u->i++;
	}
	save_val = u->len + 1;
	free(u);
	return (save_val);
}

static void	token_copy_flag(t_utils *u, int *j, int *x)
{
	(*j)++;
	*x = 1;
	u->flag = 1;
}

static void	toke_reset_quot(int *j, int *x)
{
	(*j)++;
	*x = 0;
}

int	token_copy(t_token *token, char *cmd, int i, int j)
{
	t_utils	*u;
	int		save_val;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	while (cmd[j] == ' ')
		j++;
	while (cmd[j])
	{
		if (cmd[j] == ' ' && u->in_quotes == 0 && u->in_quote == 0)
			break ;
		else if (cmd[j] == '"' && u->in_quotes == 0)
			token_copy_flag(u, &j, &u->in_quotes);
		else if (cmd[j] == '"' && u->in_quotes == 1)
			toke_reset_quot(&j, &u->in_quotes);
		else if (cmd[j] == '\'' && u->in_quote == 0)
			token_copy_flag(u, &j, &u->in_quote);
		else if (cmd[j] == '\'' && u->in_quote == 1)
			toke_reset_quot(&j, &u->in_quote);
		else
			token[i].str[u->len++] = cmd[j++];
	}
	token[i].str[u->len] = '\0';
	save_val = u->flag;
	return (free(u), save_val);
}
