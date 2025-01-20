/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:54:47 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 17:55:20 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(char *path)
{
	int	return_val;

	return_val = chdir(path);
	if (return_val < 0)
		printf("ERROR :/ \n");
	return ;
}
