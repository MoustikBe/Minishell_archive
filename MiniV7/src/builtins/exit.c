/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:58:07 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 17:58:14 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_token *token, int j)
{
	int	i;

	j++;
	while (token[j].id != 6 && token[j].str)
	{
		i = 0;
		while (token[j].str[i])
		{
			if (!isdigit(token[j].str[i]))
			{
				printf("exit\n");
				printf("numeric argument required\n");
				exit(0);
			}
			i++;
		}
		j++;
	}
	printf("exit\n");
	exit(0);
}
