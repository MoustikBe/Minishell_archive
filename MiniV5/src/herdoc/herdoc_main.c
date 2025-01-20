/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:30:14 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 19:30:46 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		if (shell->cmd[i] == '<' && shell->cmd[i + 1]
			== '<' && shell->cmd[i + 2] != '\0' && shell->cmd[i + 2] != '<')
		{
			exec_herdoc(shell);
			replace_heredoc(shell);
		}
		i++;
	}
}
