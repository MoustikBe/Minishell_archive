/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:34:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/16 15:56:43 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
				if (str_cmp(split_path[i], "/usr/local/bin") == 1)
					return (free_array(split_path), 1);
				i++;
			}
			free_array(split_path);
		}
		env = env->next;
	}
	return (0);
}

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

static int	alloc_j(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*new_cmd(char *str)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(sizeof(char) * alloc_j(str) + 1);
	j = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
		else
		{
			new_cmd[j] = str[i];
			i++;
			j++;
		}
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}

static void	verif_in(t_token *token, int i)
{
	char	*try_in;

	try_in = clean_name(token[i].str);
	if (access(try_in, O_RDONLY) != 0)
	{
		printf("bash: %s: No such file or directory\n", try_in);
		free(try_in);
		exit(1);
	}
	free(try_in);
}

static void	exec_bin_next(t_token *token, t_utils *utils)
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

int	check_pipe(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i].str)
	{
		if (token[i].id == 6)
			count++;
		i++;
	}
	if (count == 1)
		return (1);
	else if (count > 1)
		return (2);
	return (0);
}

static void	binary_option(t_shell *shell, t_token *token, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_bin(token, envp, shell);
	else
	{
		waitpid(pid, &status, 0);
		shell->last_exit_status = status;
	}
}

static void	exec_main_next(t_shell *shell, t_token *token, char **envp)
{
	int		terminal;

	terminal = 0;
	terminal = in_out(token, 0);
	if (token[0].id == 10)
		binary_option(shell, token, envp);
	else if (token[0].id == 11)
		echo(token, 0);
	else if (token[0].id == 12)
		cd(token[1].str);
	else if (token[0].id == 13)
		pwd();
	else if (token[0].id == 14)
		export(shell, token, 0);
	else if (token[0].id == 15)
		unset(shell, token, 0);
	else if (token[0].id == 16)
		env(shell);
	else if (token[0].id == 17)
		ft_exit();
	if (terminal)
		dup2(terminal, STDOUT_FILENO);
	if (token[0].id > 10)
		shell->last_exit_status = 0;
}

static void	simple_pipe_exec(t_shell *shell, t_token *token)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		pipex_simple(token, shell);
	else
	{
		waitpid(pid, &status, 0);
		shell->last_exit_status = status;
	}
}

void	exec_main(t_token *token, char **envp, t_shell *shell)
{
	int		status;
	pid_t	pid;

	if (check_pipe(token) == 1)
		simple_pipe_exec(shell, token);
	else if (check_pipe(token) == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			pipex_multi(token, shell);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			shell->last_exit_status = status;
		}
	}
	else
		exec_main_next(shell, token, envp);
	return ;
}
