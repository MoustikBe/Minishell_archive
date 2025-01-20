/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:38:00 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:38:10 by aude-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_memory(char **split, int j)
{
	while (--j >= 0)
		free(split[j]);
	free(split);
}

static int	count_words(char *s, char c)
{
	int	count;
	int	word;
	int	in_quotes;
	int	in_quote;

	in_quotes = 0;
	in_quote = 0;
	word = 0;
	count = 0;
	while (s[count])
	{
		if (s[count] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if (s[count] == '"' && in_quotes == 1)
		{
			in_quotes = 0;
			word++;
			if (s[count + 1] == '"')
				word++;
		}
		else if (s[count] == '\'' && in_quote == 0)
			in_quote = 1;
		else if (s[count] == '\'' && in_quote == 1)
		{
			in_quote = 0;
			word++;
			if (s[count + 1] == '\'')
				word++;
		}
		else if (s[count] != c && in_quotes == 0 && in_quote == 0)
		{
			word++;
			while (s[count] && s[count] != c
				&& s[count] != '"' && s[count] != '\'')
				count++;
			count--;
		}
		count++;
	}
	return (word);
}

static char	*word_dup(char *str, int start, int finish)
{
	char	*word;
	int		s_start;
	int		new_alloc;
	int		i;
	int		inside;

	s_start = start;
	new_alloc = 0;
	inside = 0;
	i = 0;
	while (s_start < finish)
	{
		if (s_start == finish - 1 && str[s_start] == '"'
			|| s_start == finish - 1 && str[s_start] == '\'')
			s_start++;
		else if (str[s_start] == '"' && inside == 0
			|| str[s_start] == '\'' && inside == 0)
		{
			inside = 1;
			s_start++;
		}
		else
		{
			s_start++;
			new_alloc++;
		}
	}
	word = malloc((new_alloc + 1) * sizeof(char));
	if (!word)
		return (NULL);
	inside = 0;
	while (start < finish)
	{
		if (start == finish - 1 && str[start] == '"'
			|| start == finish - 1 && str[start] == '\'')
			start++;
		else if (str[start] == '"' && inside == 0
			|| str[start] == '\'' && inside == 0)
		{
			inside = 1;
			start++;
		}
		else
			word[i++] = str[start++];
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	int		in_quotes;
	int		in_quote;
	char	**split;

	in_quotes = 0;
	in_quote = 0;
	split = malloc((count_words(s, c) + 2) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = -1;
	j = 0;
	index = -1;
	while (++i <= ft_strlen(s))
	{
		if (in_quotes == 2)
		{
			while (s[i] != ' ' && s[i] != '\0')
				i++;
			in_quotes = 0;
		}
		else if (in_quote == 2)
		{
			while (s[i] != ' ' && s[i] != '\0')
				i++;
			in_quote = 0;
		}
		if (s[i] == '"' && in_quotes == 0 && s[i] && in_quote == 0)
		{
			if (i > 0)
			{
				if (s[i - 1] == ' ')
					index = i;
			}
			in_quotes = 1;
		}
		else if (s[i] == '\'' && in_quote == 0 && s[i] && in_quotes == 0)
		{
			if (i > 0)
			{
				if (s[i - 1] == ' ')
					index = i;
			}
			in_quote = 1;
		}
		else if (s[i] == '"' && in_quotes == 1)
			in_quotes = 2;
		else if (s[i] == '\'' && in_quote == 1)
			in_quote = 2;
		else if ((s[i] != c && s[i] != '"' && index < 0)
			|| (s[i] != c && s[i] != '\'' && index < 0))
			index = i;
		else if (((s[i] == c && in_quotes == 0 || i == ft_strlen(s)
					|| s[i] == '"' && in_quotes == 1)
				&& index >= 0 && in_quote == 0)
			|| ((s[i] == c && in_quote == 0 || i == ft_strlen(s)
					|| s[i] == '\'' && in_quote == 1)
				&& index >= 0 && in_quotes == 0))
		{
			split[j++] = word_dup(s, index, i);
			if (!split[j - 1])
				return (free_memory(split, j), NULL);
			index = -1;
		}
	}
	split[j] = NULL;
	return (split);
}
