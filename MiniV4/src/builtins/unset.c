/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:07:57 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 18:12:39 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*build_cmp(char *str)
{
	int		i;
	char	*cmp_cmd;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (NULL);
	cmp_cmd = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		cmp_cmd[i] = str[i];
		i++;
	}
	cmp_cmd[i] = '\0';
	return (cmp_cmd);
}

void	unset(t_shell *shell, t_token *token, int j)
{
	t_env	*env_v;
	t_env	*prev;
	t_env	*temp;
	char	*cmp_cmd;

	j++;
	prev = NULL;
	env_v = shell->env;
	while (token[j].str)
	{
		if (token[j].str[0] == 0)
			break ;
		env_v = shell->env;
		prev = NULL;
		cmp_cmd = build_cmp(env_v->env_var);
		if (env_v && str_cmp(cmp_cmd, token[j].str) == 1)
		{
			shell->env = env_v->next;
			free(env_v->env_var);
			free(env_v);
			j++;
			continue ;
		}
		free(cmp_cmd);
		while (env_v && env_v->next)
		{
			cmp_cmd = build_cmp(env_v->next->env_var);
			if (str_cmp(cmp_cmd, token[j].str) == 1)
			{
				temp = env_v->next;
				env_v->next = temp->next;
				free(cmp_cmd);
				free(temp->env_var);
				free(temp);
				break ;
			}
			free(cmp_cmd);
			env_v = env_v->next;
		}
		j++;
	}
}
