/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:58:19 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 09:23:09 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_cmd(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=' || i == 0 || str[i + 1] == '\0')
		return (0);
	return (1);
}

void	add_to_env(t_shell *shell, char *str)
{
	t_env	*env_v;
	t_env	*new;

	if (check_cmd(str) == 0)
		return ;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->env_var = ft_strdup(str);
	new->next = NULL;
	env_v = shell->env;
	while (env_v->next)
		env_v = env_v->next;
	env_v->next = new;
}

char	*equal_cmd(char *str)
{
	int		i;
	int		j;
	char	*equal;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	equal = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		equal[j] = str[i];
		i++;
		j++;
	}
	equal[j] = '\0';
	return (equal);
}

void	next_export(t_token *token, t_shell *shell, int j, char *equal)
{
	while (token[j].str && token[j].id != 6)
	{
		if (token[j].str[0] == 0)
			break ;
		else
			equal = equal_cmd(token[j].str);
		if (search_in_env(shell, equal))
		{
			add_to_env(shell, token[j].str);
			free(token[j].str);
			token[j].str = ft_strdup(equal);
			unset(shell, token, j - 1);
			j++;
		}
		else
		{
			add_to_env(shell, token[j].str);
			j++;
		}
		free(equal);
	}
}

void	export(t_shell *shell, t_token *token, int j)
{
	char	*equal;
	t_env	*env;

	equal = NULL;
	j++;
	if (!token[j].str)
	{
		env = shell->env;
		while (env != NULL)
		{
			printf("declare -x ");
			printf("%s\n", env->env_var);
			env = env->next;
		}
	}
	next_export(token, shell, j, equal);
	return ;
}
