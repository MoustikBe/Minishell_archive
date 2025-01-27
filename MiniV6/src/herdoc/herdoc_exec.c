/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:20:40 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 14:30:47 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	len_delimiter(t_shell *shell, t_utils *utils)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<' && shell->cmd[utils->i + 1] == '<')
		{
			utils->i = utils->i + 2;
			while (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] && shell->cmd[utils->i] != ' ')
			{
				utils->len++;
				utils->i++;
			}
			break ;
		}
		utils->i++;
	}
}

static void	copy_delimiter(t_shell *shell, t_utils *utils, char *delemiter)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<' && shell->cmd[utils->i + 1] == '<')
		{
			utils->i = utils->i + 2;
			while (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] && shell->cmd[utils->i] != ' ')
			{
				delemiter[utils->len] = shell->cmd[utils->i];
				utils->len++;
				utils->i++;
			}
			break ;
		}
		utils->i++;
	}
}

static void	gnl_exec_herdoc(t_shell *shell, t_utils *utils,
char *gnl_val, char *delemiter)
{
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
			heredoc_expansion(shell, gnl_val, utils->temp_fd);
			write(0, "> ", 2);
		}
		else
		{
			write(utils->temp_fd, gnl_val, ft_strlen(gnl_val));
			write(0, "> ", 2);
		}
		free(gnl_val);
	}
	free(delemiter);
	free(gnl_val);
	return ;
}

void	exec_herdoc(t_shell *shell)
{
	char	*gnl_val;
	char	*delemiter;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	len_delimiter(shell, utils);
	delemiter = malloc(sizeof(char) * utils->len + 2);
	utils->i = 0;
	utils->len = 0;
	copy_delimiter(shell, utils, delemiter);
	delemiter[utils->len] = '\n';
	delemiter[utils->len + 1] = '\0';
	utils->temp_fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (utils->temp_fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(0, "> ", 2);
	gnl_val = NULL;
	gnl_exec_herdoc(shell, utils, gnl_val, delemiter);
	free(utils);
}

static void	cal_len_heredoc(t_shell *shell, t_utils *utils)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<')
		{
			utils->i = utils->i + 2;
			if (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] != ' ')
				utils->i++;
		}
		else
		{
			utils->len++;
			utils->i++;
		}
	}
}

static void	copy_heredoc(t_shell *shell, t_utils *utils,
char *new_cmd, char *tmp_file)
{
	while (shell->cmd[utils->i])
	{
		if (shell->cmd[utils->i] == '<')
		{
			new_cmd[utils->len] = shell->cmd[utils->i];
			utils->len++;
			utils->i = utils->i + 2;
			if (shell->cmd[utils->i] == ' ')
				utils->i++;
			while (shell->cmd[utils->i] != ' ')
				utils->i++;
			while (tmp_file[utils->j])
			{
				new_cmd[utils->len] = tmp_file[utils->j];
				utils->len++;
				utils->j++;
			}
		}
		else
		{
			new_cmd[utils->len] = shell->cmd[utils->i];
			utils->len++;
			utils->i++;
		}
	}
}

void	replace_heredoc(t_shell *shell)
{
	char	*new_cmd;
	char	*tmp_file;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	tmp_file = ft_strdup("/tmp/.heredoc");
	cal_len_heredoc(shell, utils);
	new_cmd = malloc(sizeof(char) * utils->len
			+ ft_strlen("/tmp/.heredoc") + 2);
	utils->len = 0;
	utils->i = 0;
	copy_heredoc(shell, utils, new_cmd, tmp_file);
	free(tmp_file);
	new_cmd[utils->len] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(new_cmd);
	free(new_cmd);
	free(utils);
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
