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

static int	pars_export_not_equal(t_utils *u, char **pars_cmd)
{
	u->j_copy = u->j - 1;
	while (u->j_copy >= 0)
	{
		if (ft_isalnum(pars_cmd[u->i][u->j_copy]) == 0)
			return (0);
		u->j_copy--;
	}
	u->flag = 1;
	return (1);
}

static int	pars_export_is_equal(t_utils *u, char **pars_cmd)
{
	u->quot_flag = 1;
	if (pars_cmd[u->i][u->j - 1] == ' ' || !pars_cmd[u->i][u->j - 1]
		|| pars_cmd[u->i][u->j + 1] == ' '
		|| !pars_cmd[u->i][u->j + 1])
		return (0);
	return (1);
}

int	pars_export(char **pars_cmd)
{
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	while (pars_cmd[u->i])
	{
		u->j = 0;
		u->quot_flag = 0;
		u->flag = 0;
		while (pars_cmd[u->i][u->j])
		{
			if (pars_cmd[u->i][u->j] == '=' && u->quot_flag == 0)
				if (pars_export_is_equal(u, pars_cmd) == 0)
					return (0);
			if (u->quot_flag == 1 && u->flag == 0)
				if (pars_export_not_equal(u, pars_cmd) == 0)
					return (0);
			u->j++;
		}
		u->i++;
	}
	free(u);
	return (1);
}
