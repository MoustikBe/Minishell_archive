/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:23 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 09:15:03 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_var(t_token *token, int i)
{
	if (str_cmp("$?", token[i].str) == 1)
	{
		token[i].id = 9;
		return (1);
	}
	if (token[i].str[0] == '$')
	{
		token[i].id = 8;
		return (1);
	}
	return (0);
}

int	is_char(t_token *token, int i)
{
	int	len;

	len = ft_strlen(token[i].str);
	if ((token[i].str[0] == '"' && token[i].str[len - 1] == '"')
		|| (token[i].str[0] == '\'' && token[i].str[len - 1] == '\''))
	{
		token[i].id = 7;
		return (1);
	}
	return (0);
}

int	is_pipe(t_token *token, int i)
{
	int	j;

	j = 0;
	while (token[i].str[j])
	{
		if (token[i].str[j] == '|')
		{
			if (j > 0)
			{
				if (token[i].str[j - 1] != '\'' && token[i].str[j - 1] != '"')
				{
					token[i].id = 6;
					return (1);
				}
			}
			else
			{
				token[i].id = 6;
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	is_infile(t_token *token, int i, t_shell *shell)
{
	if (shell->flag == 1)
		return (0);
	if (i > 0 && token[i - 1].str[0] == '<' && token[i - 1].str[1] != '<')
		token[i].id = 5;
	else if (token[i].str[0] == '<' && token[i].str[1] != '<')
		token[i].id = 5;
	if (token[i].id == 5)
	{
		token[i].str = clean_name(token[i].str);
		return (1);
	}
	return (0);
}
