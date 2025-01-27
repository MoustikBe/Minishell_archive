/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:04:59 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/21 10:25:01 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_var_utils(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->len = 0;
	utils->flag = 0;
	utils->i_copy = 0;
	utils->i_exit = 0;
	utils->ret_val = 0;
	utils->temp_fd = 0;
	utils->quot_flag = 0;
	utils->in_quotes = 0;
	utils->in_quote = 0;
	utils->cmp_cmd_1 = NULL;
}
