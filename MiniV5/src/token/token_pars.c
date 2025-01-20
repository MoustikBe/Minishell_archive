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

char	*make_to_pars(t_shell *shell, int i)
{
	char	*to_pars;
	int		j;
	int		k;
	int		k_save;

	k = 0;
	j = 0;
	k_save = 0;
	while (j != i && shell->cmd[k])
	{
		if (shell->cmd[k] == ' ')
		{
			j++;
			while (shell->cmd[k] == ' ')
				k++;
		}
		else
			k++;
	}
	j = 0;
	if (shell->cmd[k] != '\0')
		k++;
	k_save = k;
	while (shell->cmd[k] && shell->cmd[k] != '|')
	{
		j++;
		k++;
	}
	to_pars = malloc(sizeof(char) * j + 1);
	j = 0;
	k = k_save;
	while (shell->cmd[k] && shell->cmd[k] != '|')
	{
		to_pars[j] = shell->cmd[k];
		j++;
		k++;
	}
	to_pars[j] = '\0';
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
