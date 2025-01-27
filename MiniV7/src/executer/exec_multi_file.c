/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:47:55 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:51:01 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	last_step_4(t_token *token, int i)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[i].str);
	file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
}

void	last_step_40(t_token *token, int i)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[i].str);
	file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
}

void	command_exec_4(t_shell *shell, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[shell->index].str);
	file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
	shell->index++;
}

void	command_exec_5(t_shell *shell, t_token *token)
{
	char	*fd_mngt;

	fd_mngt = clean_name(token[shell->index].str);
	if (access(fd_mngt, O_RDONLY) != 0)
	{
		write(2, "Minishell : No such file or directory\n", 7);
		free(fd_mngt);
		shell->last_exit_status = 1;
		exit(1);
	}
	free(fd_mngt);
	shell->index++;
}

void	command_exec_40(t_shell *shell, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[shell->index].str);
	file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	free(fd_mngt);
	shell->index++;
}
