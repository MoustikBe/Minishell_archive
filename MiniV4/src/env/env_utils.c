/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:31:04 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 18:32:09 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	search_in_env_writed(t_shell *shell, char *cmp_cmd, int temp_fd)
{
	int		i;
	char	*cmp_cmd_2;
	t_env	*env_v;

	i = 0;
	env_v = shell->env;
	while (env_v)
	{
		cmp_cmd_2 = build_cmp(env_v->env_var);
		if (str_cmp(cmp_cmd, cmp_cmd_2) == 1)
		{
			while (env_v->env_var[i] != '=')
				i++;
			i++;
			while (env_v->env_var[i])
			{
				ft_putchar_fd(env_v->env_var[i], temp_fd);
				i++;
			}
			return (ft_strlen(env_v->env_var) - ft_strlen(cmp_cmd_2));
		}
		free(cmp_cmd_2);
		env_v = env_v->next;
	}
	return (0);
}
