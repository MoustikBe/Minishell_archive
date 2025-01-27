/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:02:26 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/21 13:31:29 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	token_main_next(t_token *token, t_utils *u, char *cmd)
{
	if (token[0].id == 11 && token[u->i].id
		> 2 && u->flag == 1 && u->i > 0)
		token[u->i].id = 0;
	u->j = u->j + u->len;
	while (cmd[u->j] != '\0' && cmd[u->j] == ' ')
		u->j++;
	u->i++;
}

static void	skip_space(t_utils *u, char *cmd)
{
	while (cmd[u->j] == ' ')
		u->j++;
}

t_token	*token_main(char *cmd, t_token *token, t_shell *shell)
{
	t_utils	*u;

	u = malloc(sizeof(t_utils));
	init_var_utils(u);
	token = malloc(sizeof(t_token) * len_token(cmd));
	skip_space(u, cmd);
	while (u->i < len_token(cmd) - 1)
	{
		token[u->i].id = 0;
		u->len = len_for_token(cmd, u->j);
		token[u->i].str = malloc(sizeof(char) * u->len + 1);
		u->flag = token_copy(token, cmd, u->i, u->j);
		if (token[u->i].str[0] == 0)
		{
			free(token[u->i].str);
			token[u->i].str = ft_strdup("\"");
		}
		token_id(token, u->i, shell);
		token_main_next(token, u, cmd);
	}
	token[u->i].str = NULL;
	token[u->i].id = 0;
	token_parser(token, shell, len_token(cmd));
	shell->len_token = len_token(cmd);
	return (free(u), token);
}
