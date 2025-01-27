/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:14:41 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:14:01 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_in_env(t_shell *shell, char *cmp_cmd)
{
	int		len;
	t_env	*env_v;
	char	*cmp_cmd_2;

	env_v = shell->env;
	while (env_v)
	{
		cmp_cmd_2 = build_cmp(env_v->env_var);
		if (str_cmp(cmp_cmd, cmp_cmd_2) == 1)
		{
			len = ft_strlen(cmp_cmd_2);
			free(cmp_cmd_2);
			return (ft_strlen(env_v->env_var) - len);
		}
		free(cmp_cmd_2);
		env_v = env_v->next;
	}
	return (0);
}

int	exit_val_mngt(t_shell *shell, t_utils *utils, int j_copy)
{
	char	*exit_val;
	int		i_exit_save;

	exit_val = ft_itoa(shell->last_exit_status);
	while (exit_val[utils->i_exit])
	{
		shell->env_cmd[j_copy] = exit_val[utils->i_exit];
		utils->i_exit++;
		j_copy++;
	}
	free (exit_val);
	i_exit_save = utils->i_exit;
	free(utils);
	return (i_exit_save);
}

void	dolar_expansion(t_shell *shell, t_utils *utils)
{
	char	*char_itoa;

	char_itoa = NULL;
	utils->flag = 1;
	utils->i++;
	utils->i_copy = utils->i;
	while ((shell->cmd[utils->i] && (ft_isalnum(shell->cmd[utils->i])))
		|| shell->cmd[utils->i] == '_' || shell->cmd[utils->i] == '?')
	{
		utils->i++;
		utils->j++;
	}
	utils->cmp_cmd_1 = malloc(sizeof(char) * utils->j + 1);
	utils->j = 0;
	copy_for_expansion(shell, utils, utils->cmp_cmd_1);
	utils->cmp_cmd_1[utils->j] = '\0';
	if (str_cmp(utils->cmp_cmd_1, "?") == 1)
	{
		char_itoa = ft_itoa(shell->last_exit_status);
		utils->len = utils->len + ft_strlen(char_itoa);
		free(char_itoa);
	}
	else
		utils->len = utils->len + search_in_env(shell, utils->cmp_cmd_1);
	free(utils->cmp_cmd_1);
}

void	check_len_expans(t_shell *shell, t_utils *utils)
{
	if (shell->cmd[utils->i] == '\'' && utils->quot_flag == 0)
		utils->quot_flag = 1;
	else if (shell->cmd[utils->i] == '\'' && utils->quot_flag == 1)
		utils->quot_flag = 0;
	utils->len++;
	utils->i++;
}

void	expansion(t_shell *shell)
{
	t_utils		*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '$' && utils->quot_flag == 0)
			dolar_expansion(shell, utils);
		else
			check_len_expans(shell, utils);
	}
	if (utils->flag != 1)
	{
		free(utils);
		return ;
	}
	utils_inter_step(utils, shell);
	copy_in_expansion(shell, utils);
	shell->env_cmd[utils->j] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(shell->env_cmd);
	free(shell->env_cmd);
	free(utils);
}
