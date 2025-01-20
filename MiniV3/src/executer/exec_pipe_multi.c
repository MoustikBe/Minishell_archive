#include "../../minishell.h"


void	step_1(pid_t pid, t_token *token, t_shell *shell)
{
	int	fd_in;
	char *path;
	char *cmd_join;
	char **cmd_exec;

	if (pid == 0)
	{
		//fprintf(stderr,"TEST_STEP_1\n");
		dup2(shell->fd[1], STDOUT_FILENO);
   		close(shell->fd[0]);
    	close(shell->fd[1]);
		// EXECUTION DE LA COMMANDE
		shell->index = 0;
		cmd_join = calloc(1, 1);
		while(token[shell->index].id != 6)
		{	
			cmd_join = ft_strjoin(cmd_join, token[shell->index].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			shell->index++;
		}
		cmd_exec = ft_split(cmd_join, ' ');
		//fprintf(stderr, "step 1 | cmd_exec -> %s\n", cmd_exec[0]);
		if(check_cmd_quotes(cmd_exec[0]) > 1)
		{
			//printf("BUILTIN DETECTED\n");
			if(check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, shell, 0);
			else if(check_cmd_quotes(cmd_exec[0]) == 3)
				cd(token[1].str);
			else if(check_cmd_quotes(cmd_exec[0]) == 4)
				pwd();
			else if(check_cmd_quotes(cmd_exec[0]) == 5)
				export(shell, token, 0);
			else if(check_cmd_quotes(cmd_exec[0]) == 6)
				unset(shell, token, 0);
			else if(check_cmd_quotes(cmd_exec[0]) == 7)
				env(shell);
			else if(check_cmd_quotes(cmd_exec[0]) == 8)
				ft_exit();
			exit(0);
		}
		path = make_path(cmd_exec[0], shell);
		//fprintf(stderr, "step 1 | path -> %s\n", path);
    	execve(path, cmd_exec, NULL);
		exit(2);
	}
}

void	to_nb_cmd(t_shell *shell)
{
	close(shell->fd[1]);
	shell->fd_temp = shell->fd[0];
	pipe(shell->fd);
}

void	command_execution(t_token *token, t_shell *shell)
{
	char *cmd_join;
	char *path;
	char *fd_mngt;
	int file;
	char **cmd_exec;
	int i_copy;

	cmd_join = calloc(1, 1);
	i_copy = shell->index;
	while(token[shell->index].id != 6 && token[shell->index].str)
	{	
		//fprintf(stderr, "cmd join -> %s\n", token[shell->index].str);
		if(token[shell->index].id == 4)
		{
			fd_mngt = ft_strdup(token[shell->index].str);
			file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (file == -1) 
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
			free(fd_mngt);
			shell->index++;
		}
		else if(token[shell->index].id == 5 && str_cmp(token[i_copy].str, "cat") == 0 && str_cmp(token[i_copy].str, "/bin/cat") == 0)
		{
			fd_mngt = clean_name(token[shell->index].str);
			if(access(fd_mngt, O_RDONLY) != 0)
			{
				write(2, "Minishell : No such file or directory\n", 7);
				free(fd_mngt);
				shell->last_exit_status = 1;
				exit(1);
			}
			free(fd_mngt);
			shell->index++;
		}
		else if(token[shell->index].id == 40)
		{
			fd_mngt = ft_strdup(token[shell->index].str);
			file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (file == -1) 
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(file, STDOUT_FILENO);
			close(file);
			free(fd_mngt);
			shell->index++;
		}
		else 
		{
			cmd_join = ft_strjoin(cmd_join, token[shell->index].str);
			cmd_join = ft_strjoin(cmd_join, " ");
			shell->index++;
		}
	}
	cmd_exec = ft_split(cmd_join, ' ');
	//fprintf(stderr, "cmd join 2.0 -> %s\n", token[shell->index].str);
	/*
	int count = 0;
	while (cmd_exec[count])
	{
		fprintf(stderr, "cmd_exec -> %s\n", cmd_exec[count]);
		count++;
	}
	fprintf(stderr, "FIN D'UNE EXEC\n");
	*/
	//fprintf(stderr, "mid step | cmd_exec -> %s\n", cmd_exec[0]);
	if(check_cmd_quotes(cmd_exec[0]) > 1)
	{
		//printf("BUILTIN DETECTED\n");
		if(check_cmd_quotes(cmd_exec[0]) == 2)
			echo(token, shell, i_copy);
		else if(check_cmd_quotes(cmd_exec[0]) == 3)
			cd(token[1].str);
		else if(check_cmd_quotes(cmd_exec[0]) == 4)
			pwd();
		else if(check_cmd_quotes(cmd_exec[0]) == 5)
			export(shell, token, i_copy);
		else if(check_cmd_quotes(cmd_exec[0]) == 6)
			unset(shell, token, i_copy);
		else if(check_cmd_quotes(cmd_exec[0]) == 7)
			env(shell);
		else if(check_cmd_quotes(cmd_exec[0]) == 8)
			ft_exit();
		exit(0);
	}
	path = make_path(cmd_exec[0], shell);
	execve(path, cmd_exec, NULL);
	// On pourrait donner un index dans la structure, 
	// Une fois a cette index, on dit que jusque au prochain pipe on avance et join les mots 
	// Donc avec sa on arrive a la methode de d'habitude et apres on update l'index.
}


void	createprocessus(pid_t pid, t_shell *shell, t_token *token)
{
	if (pid == 0)
	{
		close(shell->fd[0]);
		dup2(shell->fd_temp, STDIN_FILENO);
		dup2(shell->fd[1], STDOUT_FILENO);
		close(shell->fd_temp);
		close(shell->fd[1]);
		command_execution(token, shell);
	}
	if (shell->nb_cmd > 1)
	{
		close(shell->fd_temp);
		close(shell->fd[1]);
		shell->fd_temp = shell->fd[0];
		pipe(shell->fd);
	}
	shell->nb_cmd--;
	//fprintf(stderr, "shell.index %d | token.str -> %s\n", shell->index, token[shell->index].str);
	while (token[shell->index].id != 6)
		shell->index++;
	shell->index++;
}

void	sub_process(t_shell *shell, t_token *token, pid_t pid)
{
	if(shell->index == 0)
	{
		while(token[shell->index].id != 6)
			shell->index++;
	}
	shell->index++;
	while (shell->nb_cmd)
	{
		pid = fork();
		if (pid == -1)
			exit(2);
		if(token[shell->index].id == 6)
			shell->index++;
		createprocessus(pid, shell, token);
	}
}

void	from_nb_cmd(t_shell *shell)
{
	close(shell->fd_temp);
	close(shell->fd[1]);
	shell->fd_temp = shell->fd[0];
}

void last_step(t_shell *shell, t_token *token, pid_t pid)
{
	int i;
	int file;
	char *fd_mngt;

	i = shell->index;
    if (pid == 0)
    {
		//fprintf(stderr, "STARFOULA_3\n");
        dup2(shell->fd[0], STDIN_FILENO);
        close(shell->fd[1]);
        close(shell->fd[0]); // Fermez après duplication pour éviter les fuites
		while (token[i].str)
		{
			if(token[i].id == 4)
			{
				fd_mngt = ft_strdup(token[i].str);
				file = open(fd_mngt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        		if (file == -1) 
				{
        		    perror("open");
        		    exit(EXIT_FAILURE);
        		}
        		dup2(file, STDOUT_FILENO);
        		close(file);
				free(fd_mngt);
			}
			else if(token[i].id == 40)
			{
				fd_mngt = ft_strdup(token[i].str);
				file = open(fd_mngt, O_WRONLY | O_APPEND | O_CREAT, 0644);
        		if (file == -1) 
				{
        		    perror("open");
        		    exit(EXIT_FAILURE);
        		}
        		dup2(file, STDOUT_FILENO);
        		close(file);
				free(fd_mngt);
			}
			i++;
		}
		//fprintf(stderr, "STARFOULA_4\n");
        command_execution(token, shell);
        exit(0);
    }
	//fprintf(stderr, "STARFOULA_5\n");
    close(shell->fd[0]); // Fermez l'extrémité lecture dans le parent
}

void wait_execution(int nb_cmd)
{
	int status;

	while(nb_cmd--)
	{
		//fprintf(stderr , "waiting\n");		
		waitpid(-1, &status, 0);
	}
}

void pipex_multi(t_token *token, t_shell *shell)
{
    int i;
    char **split_cmd;
    pid_t pid;

	shell->index = 0;
    i = 0;
    split_cmd = ft_split(shell->cmd, '|');
    while (split_cmd[i])
	{
		free(split_cmd[i]);
        i++;
    }
	free(split_cmd);
	shell->nb_cmd = i - 2;
    pipe(shell->fd);
    pid = fork();
    if (pid == -1)
        printf("ERROR\n");

    step_1(pid, token, shell);
	//fprintf(stderr, "step1 -> shell.index %d | token.str -> %s\n", shell->index, token[shell->index].str);
	close(shell->fd[1]);  // Fermez l'extrémité écriture après step_1 dans le parent
    to_nb_cmd(shell);
    sub_process(shell, token, pid);
	//fprintf(stderr, "sub_process -> shell.index %d | token.str -> %s\n", shell->index, token[shell->index].str);
    from_nb_cmd(shell);
	//fprintf(stderr, "STARFOULA_1\n");
    pid = fork();
    if (pid == -1)
        exit(2);
	//fprintf(stderr, "STARFOULA_2\n");
    last_step(shell, token, pid);
    wait_execution(shell->nb_cmd + 3);
    close(shell->fd_temp);  // Fermez l'extrémité temporaire
	return ;
}




/*
void	last_step(pid_t pid, t_shell *shell, t_token *token)
{
	if (pid == 0)
	{
		dup2(shell->fd_temp, STDIN_FILENO);
		close(shell->fd_temp);
		command_execution(token, shell);
	}
	close(shell->fd[0]);
}
*/

// PROBLEME AVEC GREP 