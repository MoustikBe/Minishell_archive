/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:38:00 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/20 12:35:56 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cw_scenario_1(t_split *sp, char *s, char c, int *x)
{
	*x = 0;
	sp->word++;
	if (s[sp->count + 1] == c)
		sp->word++;
}

void	change_for_0(t_split *sp, char *s, int *x)
{
	while (s[sp->i] != ' ' && s[sp->i] != '\0')
		sp->i++;
	*x = 0;
}

void	change_for_1(t_split *sp, char *s, int *x)
{
	if (sp->i > 0)
	{
		if (s[sp->i - 1] == ' ')
			sp->index = sp->i;
	}
	*x = 1;
}
