/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:38:14 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/07 10:39:02 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd(char *path)
{
	int	return_val;

	return_val = chdir(path);
	if (return_val < 0)
		printf ("ERROR :/ \n");
	return ;
}
