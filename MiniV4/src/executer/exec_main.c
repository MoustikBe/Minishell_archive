/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:34:08 by misaac-c          #+#    #+#             */
/*   Updated: 2025/01/10 23:31:04 by aude-la-         ###   ########.fr       */
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
				{
					free_array(split_path);
					return (1);
				}
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
		printf("\033[0;31mMinishell : bad environement \033[00m\n");
		exit(0);
	}
	if (direct_bin(token))
		return (token);
	path = malloc(sizeof(char) * ft_strlen(bin) + ft_strlen(token) + 1);
	if (!path)
		return (NULL);
	while (bin[i])
	{
		path[j] = bin[i];
		i++;
		j++;
	}
	i = 0;
	while (token[i])
	{
		path[j] = token[i];
		i++;
		j++;
	}
	path[j] = '\0';
	return (path);
}

char	*new_cmd(char *str)
{
	int		i;
	int		j;
	char	*new_cmd;

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
	i = 0;
	new_cmd = malloc(sizeof(char) * j + 1);
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

void	exec_bin(t_token *token, char **envp, t_shell *shell)
{
	int		i;
	char	*path;
	char	*command;
	char	*try_in;
	char	**exec_cmd;

	path = make_path(token[0].str, shell);
	if (!path)
		return ;
	i = 0;
	command = calloc(1, 1);
	while (token[i].str)
	{
		if (token[i].id == 4 || (token[i].id == 5
				&& str_cmp(token[0].str, "cat") == 0
				&& str_cmp(token[0].str, "/bin/cat") == 0) || token[i].id == 40)
		{
			if (token[i].id == 5)
			{
				try_in = clean_name(token[i].str);
				if (access(try_in, O_RDONLY) != 0)
				{
					printf("bash: %s: No such file or directory\n", try_in);
					free(try_in);
					exit(1);
				}
				free(try_in);
			}
			i++;
		}
		else
		{
			command = ft_strjoin(command, token[i].str);
			command = ft_strjoin(command, " ");
			i++;
		}
	}
	exec_cmd = ft_split(command, ' ');
	free(command);
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

void	exec_main(t_token *token, char **envp, t_shell *shell)
{
	int		terminal;
	int		status;
	pid_t	pid;

	terminal = 0;
	if (check_pipe(token) == 1)
	{
		pid = fork();
		if (pid == 0)
			pipex_simple(token, shell);
		else
		{
			waitpid(pid, &status, 0);
			shell->last_exit_status = status;
		}
	}
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
	{
		terminal = in_out(token, 0);
		if (token[0].id == 10)
		{
			pid = fork();
			if (pid == 0)
				exec_bin(token, envp, shell);
			else
			{
				waitpid(pid, &status, 0);
				shell->last_exit_status = status;
			}
		}
		else if (token[0].id == 11)
			echo(token, shell, 0);
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
	return ;
}
