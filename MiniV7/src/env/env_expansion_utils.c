/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:08:31 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:12:01 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	loop_utils(t_env *env_v, t_utils *utils)
{
	while (env_v->env_var[utils->len] != '=')
		utils->len++;
	utils->len++;
}

int	if_possibility(t_utils *utils, char *cmp_cmd_1, char *cmp_cmd_2)
{
	int	save_nb;

	save_nb = utils->j;
	free(cmp_cmd_1);
	free(cmp_cmd_2);
	free(utils);
	return (save_nb);
}

void	else_possibility(char *cmp_cmd_1, char *cmp_cmd_2)
{
	free(cmp_cmd_1);
	free(cmp_cmd_2);
	return ;
}

void	inter_step_expansion(t_utils *utils, int *i)
{
	utils->cmp_cmd_1[utils->len] = '\0';
	*i = utils->j;
	utils->j = 0;
	utils->len = 0;
}

void	utils_inter_step(t_utils *utils, t_shell *shell)
{
	shell->env_cmd = malloc(sizeof(char) * (utils->len + 2));
	utils->i = 0;
	utils->i_copy = 0;
	utils->j = 0;
	utils->quot_flag = 0;
}
