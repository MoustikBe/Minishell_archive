/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:57:48 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 17:57:54 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env != NULL)
	{
		printf("%s\n", env->env_var);
		env = env->next;
	}
}
