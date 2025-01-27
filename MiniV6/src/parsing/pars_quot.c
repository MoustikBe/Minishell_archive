/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:00:45 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:01:04 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_bin_path(char *command, char *bin)
{
	char	*bin_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	bin_path = malloc(sizeof(char) * ft_strlen(command) + ft_strlen(bin) + 1);
	bin_path[ft_strlen(command) + ft_strlen(bin)] = '\0';
	while (bin[i])
	{
		bin_path[i] = bin[i];
		i++;
	}
	while (command[j])
	{
		bin_path[i] = command[j];
		i++;
		j++;
	}
	bin_path[i] = '\0';
	return (bin_path);
}

int	check_bin_quotes(char *command)
{
	int		return_val;
	char	*bin_path;

	if (command[0] == '\0')
		return (0);
	else if (str_cmp(command, "/") || str_cmp(command, ".")
		|| str_cmp(command, ".."))
		return (0);
	bin_path = get_bin_path(command, "/usr/bin/");
	return_val = open(bin_path, O_RDONLY);
	if (return_val > 0)
		return (free(bin_path), close(return_val), 1);
	return (free(bin_path), 0);
}
