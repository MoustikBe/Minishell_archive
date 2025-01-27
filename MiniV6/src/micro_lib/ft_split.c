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

static int	init_struct_split(t_split *split, char *s)
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

static void	free_memory(char **split, int j)
{
	while (--j >= 0)
		free(split[j]);
	free(split);
}

static void	cw_scenario_1(t_split *sp, char *s, char c, int *x)
{
	*x = 0;
	sp->word++;
	if (s[sp->count + 1] == c)
		sp->word++;
}

static int	count_words(t_split *sp, char *s, char c)
{
	while (s[sp->count])
	{
		if (s[sp->count] == '"' && sp->in_quotes == 0)
			sp->in_quotes = 1;
		else if (s[sp->count] == '"' && sp->in_quotes == 1)
			cw_scenario_1(sp, s, '"', &(sp->in_quotes));
		else if (s[sp->count] == '\'' && sp->in_quote == 0)
			sp->in_quote = 1;
		else if (s[sp->count] == '\'' && sp->in_quote == 1)
			cw_scenario_1(sp, s, '\'', &(sp->in_quote));
		else if (s[sp->count] != c && sp->in_quotes == 0 && sp->in_quote == 0)
		{
			sp->word++;
			while (s[sp->count] && s[sp->count] != c
				&& s[sp->count] != '"' && s[sp->count] != '\'')
				sp->count++;
			sp->count--;
		}
		sp->count++;
	}
	return (sp->word);
}

static int	word_dup_len(t_split *sp, int finish, char *str)
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

static char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	t_split	*sp;

	sp = malloc(sizeof(t_split));
	init_struct_split(sp, str);
	sp->s_start = start;
	word = malloc((word_dup_len(sp, finish, str)) * sizeof(char));
	sp->inside = 0;
	while (start < finish)
	{
		if ((start == finish - 1 && str[start] == '"')
			|| (start == finish - 1 && str[start] == '\''))
			start++;
		else if ((str[start] == '"' && sp->inside == 0)
			|| (str[start] == '\'' && sp->inside == 0))
		{
			sp->inside = 1;
			start++;
		}
		else
			word[sp->i_wd++] = str[start++];
	}
	word[sp->i_wd] = '\0';
	free(sp);
	return (word);
}

static void	change_for_0(t_split *sp, char *s, int *x)
{
	while (s[sp->i] != ' ' && s[sp->i] != '\0')
		sp->i++;
	*x = 0;
}

static void	change_for_1(t_split *sp, char *s, int *x)
{
	if (sp->i > 0)
	{
		if (s[sp->i - 1] == ' ')
			sp->index = sp->i;
	}
	*x = 1;
}

static int	copy_words(t_split *sp, char **split, char *s)
{
	split[sp->j++] = word_dup(s, sp->index, sp->i);
	if (!split[sp->j - 1])
		return (free_memory(split, sp->j), 1);
	sp->index = -1;
	return (0);
}

static int	condition_loop(t_split *sp, char **split, char *s, char c)
{
	if (sp->i_qs == 2)
		change_for_0(sp, s, &(sp->i_qs));
	else if (sp->i_q == 2)
		change_for_0(sp, s, &(sp->i_q));
	if (s[sp->i] == '"' && sp->i_qs == 0 && s[sp->i] && sp->i_q == 0)
		change_for_1(sp, s, &(sp->i_qs));
	else if (s[sp->i] == '\'' && sp->i_q == 0 && s[sp->i] && sp->i_qs == 0)
		change_for_1(sp, s, &(sp->i_q));
	else if (s[sp->i] == '"' && sp->i_qs == 1)
		sp->i_qs = 2;
	else if (s[sp->i] == '\'' && sp->i_q == 1)
		sp->i_q = 2;
	else if ((s[sp->i] != c && s[sp->i] != '"' && sp->index < 0)
		|| (s[sp->i] != c && s[sp->i] != '\'' && sp->index < 0))
		sp->index = sp->i;
	else if ((((s[sp->i] == c && sp->i_qs == 0)
				|| sp->i == ft_strlen(s) || (s[sp->i] == '"'
					&& sp->i_qs == 1)) && sp->index >= 0
			&& sp->i_q == 0) || (((s[sp->i] == c && sp->i_q == 0)
				|| sp->i == ft_strlen(s) || (s[sp->i] == '\''
					&& sp->i_q == 1)) && sp->index >= 0
			&& sp->i_qs == 0))
		if (copy_words(sp, split, s))
			return (1);
	return (0);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	t_split	*sp;

	sp = malloc(sizeof(t_split));
	if (init_struct_split(sp, s))
		return (NULL);
	split = malloc((count_words(sp, s, c) + 2) * sizeof(char *));
	while (++(sp->i) <= ft_strlen(s))
	{
		if (condition_loop(sp, split, s, c))
			return (free(sp), NULL);
	}
	split[sp->j] = NULL;
	free(sp);
	return (split);
}
