/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:33:52 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/20 12:46:20 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_cmp(char *cmd, char *cmp_cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] != cmp_cmd[i])
			return (0);
		i++;
	}
	if (ft_strlen(cmp_cmd) == i)
		return (1);
	return (0);
}

int	str_cmp_quotes(char *cmd, char *cmp_cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != cmp_cmd[i])
			return (0);
		i++;
	}
	if (ft_strlen(cmp_cmd) == i)
		return (1);
	return (0);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_isalnum(int alph)
{
	if (((alph >= 65) && (alph <= 90)) || ((alph >= 97) && (alph <= 122)))
		return (1);
	else if ((alph >= 48) && (alph <= 57))
		return (1);
	else
		return (0);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		length;
	int		count;

	length = ft_strlen(src);
	count = 0;
	dest = malloc((length + 1) * sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	while (src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

static int	detect_synt(char *src)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == '>' || src[i] == '<')
			count++;
		i++;
	}
	return (count);
}

char	*clean_name(char *src)
{
	int		length;
	int		count;
	int		i;
	char	*dest;

	length = ft_strlen(src);
	count = 0;
	i = 0;
	if (detect_synt(src))
		dest = malloc((length) + 1 - detect_synt(src) * sizeof(char));
	else
		dest = malloc((length) + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (src[count] != '\0')
	{
		if (src[count] == '>' || src[count] == '<')
			count++;
		else
			dest[i++] = src[count++];
	}
	dest[i] = '\0';
	free(src);
	return (dest);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
