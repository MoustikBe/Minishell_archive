/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 19:26:56 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_herdoc(t_shell *shell)
{
	int		i;
	int		l;
	int		temp_fd;
	char	*gnl_val;
	char	*delemiter;

	i = 0;
	l = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<' && shell->cmd[i + 1] == '<')
		{
			i = i + 2;
			while (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] && shell->cmd[i] != ' ')
			{
				l++;
				i++;
			}
			break ;
		}
		i++;
	}
	delemiter = malloc(sizeof(char) * l + 2);
	i = 0;
	l = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<' && shell->cmd[i + 1] == '<')
		{
			i = i + 2;
			while (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] && shell->cmd[i] != ' ')
			{
				delemiter[l] = shell->cmd[i];
				l++;
				i++;
			}
			break ;
		}
		i++;
	}
	delemiter[l] = '\n';
	delemiter[l + 1] = '\0';
	temp_fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(0, "> ", 2);
	while (1)
	{
		gnl_val = get_next_line(0);
		if (gnl_val == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (str_cmp(gnl_val, delemiter) == 1)
			break ;
		if (check_env_var(gnl_val) == 1)
		{
			heredoc_expansion(shell, gnl_val, temp_fd);
			write(0, "> ", 2);
		}
		else
		{
			write(temp_fd, gnl_val, ft_strlen(gnl_val));
			write(0, "> ", 2);
		}
		free(gnl_val);
	}
	free(delemiter);
	free(gnl_val);
}

void	replace_heredoc(t_shell *shell)
{
	int		i;
	int		j;
	int		len;
	char	*new_cmd;
	char	*tmp_file;

	i = 0;
	j = 0;
	len = 0;
	tmp_file = ft_strdup("/tmp/.heredoc");
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<')
		{
			i = i + 2;
			if (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] != ' ')
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	new_cmd = malloc(sizeof(char) * len + ft_strlen("/tmp/.heredoc") + 2);
	len = 0;
	i = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<')
		{
			new_cmd[len] = shell->cmd[i];
			len++;
			i = i + 2;
			if (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] != ' ')
				i++;
			while (tmp_file[j])
			{
				new_cmd[len] = tmp_file[j];
				len++;
				j++;
			}
		}
		else
		{
			new_cmd[len] = shell->cmd[i];
			len++;
			i++;
		}
	}
	free(tmp_file);
	new_cmd[len] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(new_cmd);
	free(new_cmd);
}

int	check_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
