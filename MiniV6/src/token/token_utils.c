/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:14 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:15 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_token(char *cmd)
{
	int	in_quotes;
	int	in_quote;
	int	space;
	int	i;

	in_quotes = 0;
	in_quote = 0;
	space = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if (cmd[i] == '"' && in_quotes == 1)
			in_quotes = 0;
		else if (cmd[i] == '\'' && in_quote == 0)
			in_quote = 1;
		else if (cmd[i] == '\'' && in_quote == 1)
			in_quote = 0;
		if (cmd[i] == ' ' && in_quotes == 0 && in_quote == 0)
		{
			while (cmd[i] == ' ')
				i++;
			space++;
		}
		else
			i++;
	}
	return (space + 1);
}

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

int	token_copy(t_token *token, char *cmd, int i, int j)
{
	int	in_quotes;
	int	in_quote;
	int	flag;
	int	k;

	k = 0;
	flag = 0;
	in_quotes = 0;
	in_quote = 0;
	while (cmd[j] == ' ')
		j++;
	while (cmd[j])
	{
		if (cmd[j] == ' ' && in_quotes == 0 && in_quote == 0)
			break ;
		else if (cmd[j] == '"' && in_quotes == 0)
		{
			j++;
			in_quotes = 1;
			flag = 1;
		}
		else if (cmd[j] == '"' && in_quotes == 1)
		{
			j++;
			in_quotes = 0;
		}
		else if (cmd[j] == '\'' && in_quote == 0)
		{
			j++;
			in_quote = 1;
			flag = 1;
		}
		else if (cmd[j] == '\'' && in_quote == 1)
		{
			j++;
			in_quote = 0;
		}
		else
		{
			token[i].str[k] = cmd[j];
			k++;
			j++;
		}
	}
	token[i].str[k] = '\0';
	return (flag);
}
