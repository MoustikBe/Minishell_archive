/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:29:11 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 18:30:52 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_env(char **envp, t_shell *shell)
{
	int		i;
	t_env	*env_v;
	t_env	*new;

	shell->env = NULL;
	env_v = shell->env;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		new->env_var = ft_strdup(envp[i]);
		new->next = NULL;
		if (shell->env == NULL)
		{
			shell->env = new;
			env_v = shell->env;
		}
		else
		{
			env_v->next = new;
			env_v = env_v->next;
		}
		i++;
	}
}
