/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:26 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 20:02:27 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*token_main(char *cmd, t_token *token, t_shell *shell)
{
	int	i;
	int	j;
	int	len_space;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	token = malloc(sizeof(t_token) * len_token(cmd));
	while (i < len_token(cmd) - 1)
	{
		token[i].id = 0;
		len_space = len_for_token(cmd, j);
		token[i].str = malloc(sizeof(char) * len_space + 1);
		flag = token_copy(token, cmd, i, j);
		if (token[i].str[0] == 0)
		{
			free(token[i].str);
			token[i].str = ft_strdup("\"");
		}
		token_id(token, i);
		if (token[0].id == 11 && token[i].id > 2 && flag == 1 && i > 0)
			token[i].id = 0;
		j = j + len_space;
		while (cmd[j] != '\0' && cmd[j] == ' ')
			j++;
		i++;
	}
	token[i].str = NULL;
	token[i].id = 0;
	token_parser(token, shell, len_token(cmd));
	shell->len_token = len_token(cmd);
	return (token);
}
