/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:55:32 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 09:19:54 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	next_echo(t_token *token, int j, int i)
{
	while (token[j].id != 6 && token[j].str)
	{
		if (token[j].str[0] == 0)
			break ;
		if (str_cmp(token[j].str, "\"") == 1)
			j++;
		else if (token[j].id == 4 || token[j].id == 40 || token[j].id == 5)
			j++;
		else
		{
			i = 0;
			while (token[j].str[i])
			{
				ft_putchar_fd(token[j].str[i], 1);
				i++;
			}
			ft_putchar_fd(' ', 1);
			j++;
		}
	}
	return ;
}

void	echo(t_token *token, int j)
{
	int	i;
	int	flag;

	flag = 0;
	j++;
	while (token[j].id == 2)
	{
		i = 1;
		if (token[j].str[0] == '-')
		{
			while (token[j].str[i] && token[j].str[i] == 'n')
				i++;
			if (token[j].str[i] == 0)
			{
				j++;
				flag = 1;
			}
			else
				break ;
		}
	}
	next_echo(token, j, i);
	if (flag == 0)
		printf("\n");
}
