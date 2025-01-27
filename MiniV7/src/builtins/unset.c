/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:07:57 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/27 10:42:45 by misaac-c         ###   ########.fr       */
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

static void	next_unset(t_env *env_v, t_token *token, char *cmp_cmd, int j)
{
	t_env	*temp;

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
}

void	unset(t_shell *shell, t_token *token, int j)
{
	t_env	*env_v;
	char	*cmp_cmd;

	j++;
	env_v = shell->env;
	while (token[j].str)
	{
		if (token[j].str[0] == 0)
			break ;
		env_v = shell->env;
		cmp_cmd = build_cmp(env_v->env_var);
		if (env_v && str_cmp(cmp_cmd, token[j].str) == 1)
		{
			shell->env = env_v->next;
			free(env_v->env_var);
			free(env_v);
			free(cmp_cmd);
			j++;
			continue ;
		}
		next_unset(env_v, token, cmp_cmd, j);
		free(cmp_cmd);
		j++;
	}
}
