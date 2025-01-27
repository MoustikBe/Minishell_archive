/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:30:34 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:34:54 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parent_file_4(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
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

void	parent_file_5(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
	file = open(fd_mngt, O_RDONLY);
	if (file == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	free(fd_mngt);
}

void	parent_file_40(t_utils *utils, t_token *token)
{
	int		file;
	char	*fd_mngt;

	fd_mngt = ft_strdup(token[utils->i].str);
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

void	parent_file_mngt(t_utils *u, t_token *token)
{
	while (token[u->i].str)
	{
		if (token[u->i].id == 4)
			parent_file_4(u, token);
		else if (token[u->i].id == 40)
			parent_file_40(u, token);
		else if (token[u->i].id == 5)
			parent_file_5(u, token);
		u->i++;
	}
}

void	child_process_fd(char *file_in)
{
	int	fd_in;

	fd_in = open(file_in, O_RDONLY);
	if (fd_in < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}
