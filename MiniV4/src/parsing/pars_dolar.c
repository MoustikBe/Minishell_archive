/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dolar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:00:32 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:59:38 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_varname(char **pars_cmd, int *i, int *j)
{
	while (pars_cmd[*i][*j])
	{
		if (pars_cmd[*i][*j] == '$' || pars_cmd[*i][*j] == '|')
			(*j)++;
		else if (((pars_cmd[*i][*j] >= 48) && (pars_cmd[*i][*j] <= 57))
			|| ((pars_cmd[*i][*j] >= 65) && (pars_cmd[*i][*j] <= 90))
			|| ((pars_cmd[*i][*j] >= 97) && (pars_cmd[*i][*j] <= 122))
			|| pars_cmd[*i][*j] == '_' || pars_cmd[*i][*j] == '?')
			(*j)++;
		else
			return (0);
	}
	(*i)++;
	return (1);
}

int	pars_dolar(char **pars_cmd)
{
	int	i;
	int	j;

	i = 0;
	while (pars_cmd[i])
	{
		j = 0;
		if (pars_cmd[i][j] != '$')
		{
			if (check_cmd_quotes(pars_cmd[i]) == 0)
			{
				if (str_cmp(pars_cmd[i], "|") == 1)
				{
					if (i > 1 && str_cmp(pars_cmd[i - 1], "|") == 1)
						return (0);
					i++;
				}
				else
					return (0);
			}
			else
				i++;
		}
		else
			if (!handle_varname(pars_cmd, &i, &j))
				return (0);
	}
	return (1);
}
