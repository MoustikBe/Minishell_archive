/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:00:23 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:58:01 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	verify_access(char *pars_cmd)
{
	if (opendir(pars_cmd) == NULL)
		return (0);
	return (1);
}

int	pars_cd(char **pars_cmd)
{
	int	i;

	i = 1;
	while (pars_cmd[i])
	{
		if (i == 2 && str_cmp(pars_cmd[i], "|") == 1)
			return (1);
		else if (i > 2 || (i == 2 && str_cmp(pars_cmd[i], "|") != 1))
			return (0);
		else if (i == 1)
		{
			if (verify_access(pars_cmd[i]) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
