/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:28 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:29 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	make_to_pars_len(t_utils *u, t_shell *shell, int i)
{
	while (u->j != i && shell->cmd[u->len])
	{
		if (shell->cmd[u->len] == ' ')
		{
			u->j++;
			while (shell->cmd[u->len] == ' ')
				u->len++;
		}
		else
			u->len++;
	}
	u->j = 0;
	if (shell->cmd[u->len] != '\0')
		u->len++;
	u->i_copy = u->len;
	while (shell->cmd[u->len] && shell->cmd[u->len] != '|')
	{
		u->j++;
		u->len++;
	}
}

char	*make_to_pars(t_shell *shell, int i)
{
	char	*to_pars;
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	make_to_pars_len(u, shell, i);
	to_pars = malloc(sizeof(char) * u->j + 1);
	u->j = 0;
	u->len = u->i_copy;
	while (shell->cmd[u->len] && shell->cmd[u->len] != '|')
	{
		to_pars[u->j] = shell->cmd[u->len];
		u->j++;
		u->len++;
	}
	to_pars[u->j] = '\0';
	free(u);
	return (to_pars);
}

void	token_parser(t_token *token, t_shell *shell, int len)
{
	char	*to_pars;
	int		return_val;
	int		i;

	i = 0;
	return_val = 0;
	while (i < len)
	{
		if (token[i].id == 6)
		{
			to_pars = make_to_pars(shell, i);
			return_val = parsing_main(to_pars);
			free(to_pars);
			if (return_val == 0)
				shell->error = 1;
			i++;
		}
		i++;
	}
	return ;
}
