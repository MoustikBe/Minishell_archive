/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:17:12 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/23 20:22:23 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*make_path(char *token, t_shell *shell)
{
	int		i;
	int		j;
	char	*bin;
	char	*path;

	i = 0;
	j = 0;
	bin = "/usr/bin/";
	if (check_path(shell) == 0 && direct_bin(token) == 0)
	{
		printf("\033[0;31mMinishell : bad environment\033[00m\n");
		exit(0);
	}
	if (direct_bin(token))
		return (token);
	path = malloc(sizeof(char) * (ft_strlen(bin) + ft_strlen(token) + 1));
	if (!path)
		return (NULL);
	while (bin[i])
		path[j++] = bin[i++];
	i = 0;
	while (token[i])
		path[j++] = token[i++];
	path[j] = '\0';
	return (path);
}

int	check_path(t_shell *shell)
{
	int		i;
	char	**split_path;
	t_env	*env;

	i = 0;
	env = shell->env;
	while (env)
	{
		if (env->env_var[0] == 'P' && env->env_var[1] == 'A'
			&& env->env_var[2] == 'T' && env->env_var[3] == 'H')
		{
			split_path = ft_split(env->env_var, ':');
			while (split_path[i])
			{
				if (str_cmp(split_path[i], "/usr/local/bin") == 1
					|| str_cmp(split_path[i], "/bin") == 1)
					return (free_array(split_path), 1);
				i++;
			}
			free_array(split_path);
		}
		env = env->next;
	}
	return (0);
}

void	binary_option(t_shell *shell, t_token *token, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_bin(token, envp, shell);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit_status = 128 + WTERMSIG(status);
	}
}

void	exec_bin(t_token *token, char **envp, t_shell *shell)
{
	char	*path;
	char	**exec_cmd;
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	init_var_utils(utils);
	path = make_path(token[0].str, shell);
	if (!path)
		return ;
	utils->cmp_cmd_1 = calloc(1, 1);
	exec_bin_next(token, utils);
	exec_cmd = ft_split(utils->cmp_cmd_1, ' ');
	free(utils->cmp_cmd_1);
	execve(path, exec_cmd, envp);
	free(path);
	free_array(exec_cmd);
	printf("\033[0;31mMinishell : command invalid \033[00m\n");
	exit(2);
}

void	exec_bin_next(t_token *token, t_utils *utils)
{
	while (token[utils->i].str)
	{
		if (token[utils->i].id == 4 || (token[utils->i].id == 5
				&& str_cmp(token[0].str, "cat") == 0
				&& str_cmp(token[0].str, "/bin/cat") == 0)
			|| token[utils->i].id == 40)
		{
			if (token[utils->i].id == 5)
				verif_in(token, utils->i);
			utils->i++;
		}
		else
		{
			utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1,
					token[utils->i].str);
			utils->cmp_cmd_1 = ft_strjoin(utils->cmp_cmd_1, " ");
			utils->i++;
		}
	}
}
