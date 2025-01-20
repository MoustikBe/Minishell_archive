/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:14:41 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:50:07 by aude-la-         ###   ########.fr       */
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

int	copy_env_cmd(int j_copy, int i, t_shell *shell)
{
	int		j;
	int		len;
	int		i_exit;
	char	*exit_val;
	char	*cmp_cmd_1;
	char	*cmp_cmd_2;
	t_env	*env_v;

	j = 0;
	i_exit = 0;
	len = 0;
	if (shell->cmd[i + 1] == '?' && shell->cmd[i + 2] == ' ')
	{
		exit_val = ft_itoa(shell->last_exit_status);
		while (exit_val[i_exit])
		{
			shell->env_cmd[j_copy] = exit_val[i_exit];
			j_copy++;
			i_exit++;
		}
		free (exit_val);
		return (i_exit);
	}
	env_v = shell->env;
	while (env_v)
	{
		j = i;
		while (shell->cmd[i] && shell->cmd[i] != ' ' && shell->cmd[i] != '"')
		{
			len++;
			i++;
		}
		i = j;
		cmp_cmd_1 = malloc(sizeof(char) * len + 1);
		len = 0;
		i++;
		while (shell->cmd[i] && shell->cmd[i] != ' ' && shell->cmd[i] != '"')
		{
			cmp_cmd_1[len] = shell->cmd[i];
			len++;
			i++;
		}
		cmp_cmd_1[len] = '\0';
		i = j;
		j = 0;
		len = 0;
		cmp_cmd_2 = build_cmp(env_v->env_var);
		if (str_cmp(cmp_cmd_1, cmp_cmd_2) == 1)
		{
			while (env_v->env_var[len] != '=')
				len++;
			len++;
			while (env_v->env_var[len])
			{
				shell->env_cmd[j_copy] = env_v->env_var[len];
				j_copy++;
				j++;
				len++;
			}
			free(cmp_cmd_1);
			free(cmp_cmd_2);
			return (j);
		}
		else
		{
			free(cmp_cmd_1);
			free(cmp_cmd_2);
			env_v = env_v->next;
		}
	}
	return (0);
}

void	expansion(t_shell *shell)
{
	int		quot_flag;
	int		i;
	int		i_copy;
	int		j;
	int		len;
	int		ret_val;
	int		flag;
	int		j_copy;
	char	*cmp_cmd;
	char	*char_itoa;

	quot_flag = 0;
	i = 0;
	i_copy = 0;
	j = 0;
	len = 0;
	ret_val = 0;
	flag = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '$' && quot_flag == 0)
		{
			flag = 1;
			i++;
			i_copy = i;
			while (shell->cmd[i] && (ft_isalnum(shell->cmd[i])
					|| shell->cmd[i] == '_') || shell->cmd[i] == '?')
			{
				i++;
				j++;
			}
			cmp_cmd = malloc(sizeof(char) * j + 1);
			j = 0;
			while (shell->cmd[i_copy] && (ft_isalnum(shell->cmd[i_copy])
					|| shell->cmd[i_copy] == '_') || shell->cmd[i_copy] == '?')
			{
				cmp_cmd[j] = shell->cmd[i_copy];
				j++;
				i_copy++;
			}
			cmp_cmd[j] = '\0';
			if (str_cmp(cmp_cmd, "?") == 1)
			{
				char_itoa = ft_itoa(shell->last_exit_status);
				len = len + ft_strlen(char_itoa);
				free(char_itoa);
			}
			else
				len = len + search_in_env(shell, cmp_cmd);
			free(cmp_cmd);
		}
		else
		{
			if (shell->cmd[i] == '\'' && quot_flag == 0)
				quot_flag = 1;
			else if (shell->cmd[i] == '\'' && quot_flag == 1)
				quot_flag = 0;
			len++;
			i++;
		}
	}
	if (flag != 1)
		return ;
	shell->env_cmd = malloc(sizeof(char) * (len + 2));
	i = 0;
	i_copy = 0;
	j = 0;
	quot_flag = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '$' && quot_flag == 0)
		{
			i_copy = i;
			j_copy = j;
			while (shell->cmd[i] && shell->cmd[i] != ' '
				&& shell->cmd[i] != '"')
				i++;
			j = j + copy_env_cmd(j_copy, i_copy, shell);
		}
		else
		{
			if (shell->cmd[i] == '\'' && quot_flag == 0)
				quot_flag = 1;
			else if (shell->cmd[i] == '\'' && quot_flag == 1)
				quot_flag = 0;
			shell->env_cmd[j] = shell->cmd[i];
			j++;
			i++;
		}
	}
	shell->env_cmd[j] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(shell->env_cmd);
	free(shell->env_cmd);
}
