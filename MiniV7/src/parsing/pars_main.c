/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:00:42 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:00:43 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pars_except(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '\0')
		return (0);
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (0);
	return (1);
}

int	handle_ret_val(int ret_val, char **pars_cmd)
{
	if (ret_val == 3)
	{
		if (pars_cd(pars_cmd) == 0)
			return (free_array(pars_cmd), 0);
		return (free_array(pars_cmd), 1);
	}
	if (ret_val == 5)
	{
		if (pars_export(pars_cmd) == 0)
			return (free_array(pars_cmd), 0);
		return (free_array(pars_cmd), 1);
	}
	if (ret_val == 9)
	{
		if (pars_syntax(pars_cmd) == 0)
			return (free_array(pars_cmd), 0);
		return (free_array(pars_cmd), 1);
	}
	if (ret_val == 10)
	{
		if (pars_dolar(pars_cmd) == 0)
			return (free_array(pars_cmd), 0);
		return (free_array(pars_cmd), 1);
	}
	return (free_array(pars_cmd), 1);
}

int	parsing_main(char *cmd)
{
	char	**pars_cmd;
	int		ret_val;

	if (pars_except(cmd) == 0)
		return (0);
	pars_cmd = ft_split(cmd, ' ');
	if (pars_cmd[0] == NULL)
		return (free_array(pars_cmd), -1);
	ret_val = check_cmd_quotes(pars_cmd[0]);
	if (ret_val == 1)
		return (free_array(pars_cmd), 1);
	else if (ret_val > 1)
		return (handle_ret_val(ret_val, pars_cmd));
	return (free_array(pars_cmd), 0);
}
