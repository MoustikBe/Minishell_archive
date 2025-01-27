/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:27:18 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 09:12:35 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*heredoc_expansion_next(t_utils *utils,
char *gnl_val, char *cmp_cmd)
{
	utils->flag = 1;
	utils->i++;
	utils->i_copy = utils->i;
	while (gnl_val[utils->i] && gnl_val[utils->i] != ' '
		&& gnl_val[utils->i_copy] != '\n')
	{
		utils->i++;
		utils->j++;
	}
	cmp_cmd = malloc(sizeof(char) * utils->j + 1);
	utils->j = 0;
	while (gnl_val[utils->i_copy] && gnl_val[utils->i_copy] != ' '
		&& gnl_val[utils->i_copy] != '\n')
	{
		cmp_cmd[utils->j] = gnl_val[utils->i_copy];
		utils->j++;
		utils->i_copy++;
	}
	cmp_cmd[utils->j] = '\0';
	return (cmp_cmd);
}

void	heredoc_expansion(t_shell *shell, char *gnl_val, int temp_fd)
{
	char	*cmp_cmd;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	while (gnl_val[utils->i])
	{
		if (gnl_val[utils->i] == '$')
		{
			if (gnl_val[utils->i + 1] == '?' && gnl_val[utils->i + 2] == ' ')
				return ;
			cmp_cmd = heredoc_expansion_next(utils, gnl_val, cmp_cmd);
			utils->len = utils->len
				+ search_in_env_writed(shell, cmp_cmd, temp_fd);
		}
		else
		{
			ft_putchar_fd(gnl_val[utils->i], temp_fd);
			utils->len++;
			utils->i++;
		}
	}
	ft_putchar_fd('\n', temp_fd);
	free(utils);
	free(cmp_cmd);
}
