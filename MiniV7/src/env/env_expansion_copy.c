/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:02:53 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:12:32 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	copy_env_cmd(int j_copy, int i, t_shell *shell)
{
	char	*cmp_cmd_2;
	t_env	*env_v;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	if (shell->cmd[i + 1] == '?' && shell->cmd[i + 2] == ' ')
		return (exit_val_mngt(shell, utils, j_copy));
	env_v = shell->env;
	while (env_v)
	{
		building_cmp_cmd(utils, shell, &i);
		inter_step_expansion(utils, &i);
		cmp_cmd_2 = build_cmp(env_v->env_var);
		if (str_cmp(utils->cmp_cmd_1, cmp_cmd_2) == 1)
		{
			loop_utils(env_v, utils);
			copy_in_envcmd(env_v, utils, shell, j_copy);
			return (if_possibility(utils, utils->cmp_cmd_1, cmp_cmd_2));
		}
		else
			else_possibility(utils->cmp_cmd_1, cmp_cmd_2);
		env_v = env_v->next;
	}
	return (free(utils), 0);
}

void	copy_for_expansion(t_shell *shell, t_utils *utils, char *cmp_cmd)
{
	while ((shell->cmd[utils->i_copy]
			&& (ft_isalnum(shell->cmd[utils->i_copy])))
		|| shell->cmd[utils->i_copy] == '_'
		|| shell->cmd[utils->i_copy] == '?')
	{
		cmp_cmd[utils->j] = shell->cmd[utils->i_copy];
		utils->j++;
		utils->i_copy++;
	}
}

void	copy_in_expansion(t_shell *shell, t_utils *utils)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '$' && utils->quot_flag == 0)
		{
			utils->i_copy = utils->i;
			utils->j_copy = utils->j;
			while (shell->cmd[utils->i] && shell->cmd[utils->i] != ' '
				&& shell->cmd[utils->i] != '"')
				utils->i++;
			utils->j = utils->j
				+ copy_env_cmd(utils->j_copy, utils->i_copy, shell);
		}
		else
		{
			if (shell->cmd[utils->i] == '\'' && utils->quot_flag == 0)
				utils->quot_flag = 1;
			else if (shell->cmd[utils->i] == '\'' && utils->quot_flag == 1)
				utils->quot_flag = 0;
			shell->env_cmd[utils->j] = shell->cmd[utils->i];
			utils->j++;
			utils->i++;
		}
	}
}

void	copy_in_envcmd(t_env *env_v, t_utils *utils,
t_shell *shell, int j_copy)
{
	while (env_v->env_var[utils->len])
	{
		shell->env_cmd[j_copy] = env_v->env_var[utils->len];
		j_copy++;
		utils->j++;
		utils->len++;
	}
}

void	building_cmp_cmd(t_utils *utils, t_shell *shell, int *i)
{
	utils->j = *i;
	while (shell->cmd[*i] && shell->cmd[*i] != ' ' && shell->cmd[*i] != '"')
	{
		utils->len++;
		(*i)++;
	}
	*i = utils->j;
	utils->cmp_cmd_1 = malloc(sizeof(char) * utils->len + 1);
	utils->len = 0;
	(*i)++;
	while (shell->cmd[*i] && shell->cmd[*i] != ' ' && shell->cmd[*i] != '"')
	{
		utils->cmp_cmd_1[utils->len] = shell->cmd[*i];
		utils->len++;
		(*i)++;
	}
}
