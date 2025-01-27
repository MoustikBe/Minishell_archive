/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_dolar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:22:36 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/14 09:24:17 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	dolar_not_detected(t_utils *u, char **pars_cmd)
{
	if (check_cmd_quotes(pars_cmd[u->i]) == 0)
	{
		if (str_cmp(pars_cmd[u->i], "|") == 1)
		{
			if (u->i > 1 && str_cmp(pars_cmd[u->i - 1], "|") == 1)
				return (0);
			u->i++;
		}
		else
			return (0);
	}
	else
		u->i++;
	return (1);
}

static int	dolar_detected(t_utils *u, char **pars_cmd)
{
	if (pars_cmd[u->i][u->j] == '$' || pars_cmd[u->i][u->j] == '|')
		u->j++;
	else if (((pars_cmd[u->i][u->j] >= 48) && (pars_cmd[u->i][u->j]
		<= 57)) || ((pars_cmd[u->i][u->j] >= 65)
			&& (pars_cmd[u->i][u->j] <= 90)) || ((pars_cmd[u->i][u->j]
		>= 97) && (pars_cmd[u->i][u->j] <= 122))
			|| pars_cmd[u->i][u->j] == '_' || pars_cmd[u->i][u->j]
		== '?')
		u->j++;
	else
		return (0);
	return (1);
}

int	pars_dolar(char **pars_cmd)
{
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	while (pars_cmd[u->i])
	{
		u->j = 0;
		if (pars_cmd[u->i][u->j] != '$')
		{
			if (dolar_not_detected(u, pars_cmd) == 0)
				return (0);
		}
		else
		{
			while (pars_cmd[u->i][u->j])
			{
				if (dolar_detected(u, pars_cmd) == 0)
					return (0);
			}
			u->i++;
		}
	}
	free(u);
	return (1);
}
