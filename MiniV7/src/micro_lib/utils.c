/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:33:52 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:20 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_cmp(char *cmd, char *cmp_cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] != cmp_cmd[i])
			return (0);
		i++;
	}
	if (ft_strlen(cmp_cmd) == i)
		return (1);
	return (0);
}

int	str_cmp_quotes(char *cmd, char *cmp_cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != cmp_cmd[i])
			return (0);
		i++;
	}
	if (ft_strlen(cmp_cmd) == i)
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_isalnum(int alph)
{
	if (((alph >= 65) && (alph <= 90)) || ((alph >= 97) && (alph <= 122)))
		return (1);
	else if ((alph >= 48) && (alph <= 57))
		return (1);
	else
		return (0);
}
