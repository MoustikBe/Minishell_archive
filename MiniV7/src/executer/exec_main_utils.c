/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:26:59 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:28:13 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i].str)
	{
		if (token[i].id == 6)
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	else if (count > 1)
		return (2);
	return (0);
}

void	verif_in(t_token *token, int i)
{
	char	*try_in;

	try_in = clean_name(token[i].str);
	if (access(try_in, O_RDONLY) != 0)
	{
		printf("bash: %s: No such file or directory\n", try_in);
		free(try_in);
		exit(1);
	}
	free(try_in);
}
