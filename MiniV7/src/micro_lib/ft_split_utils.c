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

static void	free_memory(char **split, int j)
{
	while (--j >= 0)
		free(split[j]);
	free(split);
}

int	init_struct_split(t_split *split, char *s)
{
	split->i = -1;
	split->j = 0;
	split->index = -1;
	split->i_qs = 0;
	split->i_q = 0;
	split->in_quotes = 0;
	split->in_quote = 0;
	split->word = 0;
	split->count = 0;
	split->new_alloc = 0;
	split->inside = 0;
	split->i_wd = 0;
	if (!split || !s)
		return (1);
	return (0);
}

int	word_dup_len(t_split *sp, int finish, char *str)
{
	while (sp->s_start < finish)
	{
		if ((sp->s_start == finish - 1 && str[sp->s_start] == '"' )
			|| (sp->s_start == finish - 1 && str[sp->s_start] == '\''))
			sp->s_start++;
		else if ((str[sp->s_start] == '"' && sp->inside == 0)
			|| (str[sp->s_start] == '\'' && sp->inside == 0))
		{
			sp->inside = 1;
			sp->s_start++;
		}
		else
		{
			sp->s_start++;
			sp->new_alloc++;
		}
	}
	return (sp->new_alloc + 1);
}

int	copy_words(t_split *sp, char **split, char *s)
{
	split[sp->j++] = word_dup_special(s, sp->index, sp->i);
	if (!split[sp->j - 1])
		return (free_memory(split, sp->j), 1);
	sp->index = -1;
	return (0);
}
