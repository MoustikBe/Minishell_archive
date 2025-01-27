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

int	len_for_token(char *cmd, int i)
{
	int	j;
	int	in_quotes;
	int	in_quote;

	in_quotes = 0;
	in_quote = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && in_quotes == 0 && in_quote == 0)
			break ;
		else if (cmd[i] == '"' && in_quotes == 0 && in_quote == 0)
			in_quotes = 1;
		else if (cmd[i] == '"' && in_quotes == 1 && in_quote == 0)
			in_quotes = 0;
		else if (cmd[i] == '\'' && in_quote == 0 && in_quotes == 0)
			in_quote = 1;
		else if (cmd[i] == '\'' && in_quote == 1 && in_quotes == 0)
			in_quote = 0;
		i++;
		j++;
	}
	return (j);
}

void	free_all_token(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].str)
	{
		free(token[i].str);
		i++;
	}
	free(token);
}
