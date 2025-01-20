/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:53:43 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 14:51:47 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_shell *shell)
{
	t_env	*tmp;
	t_env	*current;

	current = shell->env;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp->env_var);
		free(tmp);
	}
	shell->env = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	int		ret_val;
	char	*cpy_cmd;
	t_token	*token;
	t_shell	*shell;

	if(argc > 1)
		return(printf("ERROR, verify the entry -> %s\n", argv[0]));
	cpy_cmd = NULL;
	shell = malloc(sizeof(t_shell));
	copy_env(envp, shell);
	shell->len_token = 0;
	shell->last_exit_status = 0;
	while (1)
	{
		manage_signals();
		shell->error = 0;
		shell->cmd = readline("\033[34;01mMinishell : \033[00m");
		add_history(shell->cmd);
		if (shell->cmd == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (shell->cmd[0] == '\0' || verif_quotes(shell->cmd))
			ret_val = -1;
		else
		{
			cmd_cleaner(shell);
			expansion(shell);
			here_doc(shell);
			ret_val = parsing_main(shell->cmd);
		}
		if (ret_val == -1)
			shell->last_exit_status = 127;
		else if (ret_val == 0)
		{
			printf("\033[0;31mMinishell : command invalid \033[00m\n");
			shell->last_exit_status = 127;
		}
		else if (ret_val == 1)
		{
			token = token_main(shell->cmd, token, shell);
			if (shell->error == 1)
			{
				printf("\033[0;31mMinishell : command invalid \033[00m\n");
				shell->last_exit_status = 127;
			}
			else
				exec_main(token, envp, shell);
			free_all_token(token);
		}
		free(shell->cmd);
	}
	unlink("/tmp/.heredoc");
	free_env(shell);
	free(shell->cmd);
	if (cpy_cmd)
		free(cpy_cmd);
	free(shell);
	return (0);
}
