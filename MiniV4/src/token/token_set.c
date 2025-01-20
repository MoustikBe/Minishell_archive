/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:31 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:32 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	token_id(t_token *token, int i)
{
	if (is_cmd(token, i) == 1)
		return ;
	else if (is_flag(token, i) == 1)
		return ;
	else if (is_outfile_append(token, i) == 1)
		return ;
	else if (is_outfile(token, i) == 1)
		return ;
	else if (is_infile(token, i) == 1)
		return ;
	else if (is_pipe(token, i) == 1)
		return ;
	else if (is_char(token, i) == 1)
		return ;
	else if (is_var(token, i) == 1)
		return ;
	return ;
}
