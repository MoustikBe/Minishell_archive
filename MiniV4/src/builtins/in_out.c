/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:04:34 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 18:07:12 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	in_out(t_token *token, int j)
{
	int		file;
	int		terminal_copy;
	char	*fd_mngt;

	terminal_copy = dup(STDOUT_FILENO);
	while (token[j].id != 6 && token[j].str)
	{
		if (token[j].id == 4 || token[j].id == 40 || token[j].id == 5)
		{
			if (token[j].id == 4)
			{
				fd_mngt = ft_strdup(token[j].str);
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
			else if (token[j].id == 40)
			{
				fd_mngt = ft_strdup(token[j].str);
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
		}
		j++;
	}
	return (terminal_copy);
}
