/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:27:18 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:45:07 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_expansion(t_shell *shell, char *gnl_val, int temp_fd)
{
	int		i;
	int		j;
	int		i_copy;
	int		len;
	int		ret_val;
	int		flag;
	char	*cmp_cmd;

	i = 0;
	j = 0;
	len = 0;
	flag = 0;
	i_copy = 0;
	ret_val = 0;
	while (gnl_val[i])
	{
		if (gnl_val[i] == '$')
		{
			if (gnl_val[i + 1] == '?' && gnl_val[i + 2] == ' ')
				return ;
			flag = 1;
			i++;
			i_copy = i;
			while (gnl_val[i] && gnl_val[i] != ' ' && gnl_val[i_copy] != '\n')
			{
				i++;
				j++;
			}
			cmp_cmd = malloc(sizeof(char) * j + 1);
			j = 0;
			while (gnl_val[i_copy] && gnl_val[i_copy] != ' '
				&& gnl_val[i_copy] != '\n')
			{
				cmp_cmd[j] = gnl_val[i_copy];
				j++;
				i_copy++;
			}
			cmp_cmd[j] = '\0';
			len = len + search_in_env_writed(shell, cmp_cmd, temp_fd);
		}
		else
		{
			ft_putchar_fd(gnl_val[i], temp_fd);
			len++;
			i++;
		}
	}
	ft_putchar_fd('\n', temp_fd);
}
