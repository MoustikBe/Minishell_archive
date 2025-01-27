/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 14:30:47 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cal_len_heredoc(t_shell *shell, t_utils *utils)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<')
		{
			utils->i = utils->i + 2;
			if (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] != ' ')
				utils->i++;
		}
		else
		{
			utils->len++;
			utils->i++;
		}
	}
}

void	copy_heredoc(t_shell *shell, t_utils *utils,
char *new_cmd, char *tmp_file)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<')
		{
			new_cmd[utils->len] = shell->cmd[utils->i];
			utils->len++;
			utils->i = utils->i + 2;
			if (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] != ' ')
				utils->i++;
			while (tmp_file[utils->j])
			{
				new_cmd[utils->len] = tmp_file[utils->j];
				utils->len++;
				utils->j++;
			}
		}
		else
		{
			new_cmd[utils->len] = shell->cmd[utils->i];
			utils->len++;
			utils->i++;
		}
	}
}

int	check_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
