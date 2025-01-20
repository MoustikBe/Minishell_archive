/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:00:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:00:41 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pars_export(char **pars_cmd)
{
	int	i;
	int	j;
	int	j_copy;
	int	equal;
	int	flag;

	j_copy = 0;
	equal = 0;
	flag = 0;
	i = 1;
	while (pars_cmd[i])
	{
		j = 0;
		equal = 0;
		flag = 0;
		while (pars_cmd[i][j])
		{
			if (pars_cmd[i][j] == '=' && equal == 0)
			{
				equal = 1;
				if (pars_cmd[i][j - 1] == ' ' || !pars_cmd[i][j - 1]
					|| pars_cmd[i][j + 1] == ' ' || !pars_cmd[i][j + 1])
					return (0);
			}
			if (equal == 1 && flag == 0)
			{
				j_copy = j - 1;
				while (j_copy >= 0)
				{
					if (ft_isalnum(pars_cmd[i][j_copy]) == 0)
						return (0);
					j_copy--;
				}
				flag = 1;
			}
			j++;
		}
		i++;
	}
	return (1);
}
