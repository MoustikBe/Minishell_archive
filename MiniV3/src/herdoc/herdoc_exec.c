#include "../../minishell.h"

void exec_herdoc(t_shell *shell)
{
	// Stocker le delimiter
	char *gnl_val;
	char *delemiter;
	int i;
	int l;
	int temp_fd;

	i = 0;
	l = 0;
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '<' && shell->cmd[i + 1] == '<')
		{
			i = i + 2;
			while (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] && shell->cmd[i] != ' ')
			{
				l++;
				i++;
			}
			break;
		}
		i++;
	}
	
	delemiter = malloc(sizeof(char) * l + 2);
	i = 0;
	l = 0;
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '<' && shell->cmd[i + 1] == '<')
		{
			i = i + 2;
			while (shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] && shell->cmd[i] != ' ')
			{
				delemiter[l] = shell->cmd[i];
				l++;
				i++;
			}
			break;
		}
		i++;
	}
	delemiter[l] = '\n';
	delemiter[l + 1] = '\0';
	//printf("Delimitator -> %s\n", delemiter); //Done V //
	// Comparer la valeur transmise avec la valeur du delimiter
	temp_fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (temp_fd < 0)
	{
        perror("open");
        exit(EXIT_FAILURE);
    }
	write(0, "> ", 2);
	while (1)
	{
		gnl_val = get_next_line(0);
		if (gnl_val == NULL) //IRIS I used NULL instead of \0 because "cmd[0]" produces a SEGFAULT
		{
			printf("exit\n");
			break;
		}
		// SI valeur == -> STOP
		/* FAIRE UNE SORTE DE MINI EXPANSION DE VARIABLE AFIN DE CHANGER LES VALEUR */
		if(str_cmp(gnl_val, delemiter) == 1)
			break;
		// Il faut expand la variable d'env si il y'en a 
		// Fonction qui detecte si il y'en a 
		if(check_env_var(gnl_val) == 1)
		{
			heredoc_expansion(shell, gnl_val, temp_fd);
			write(0, "> ", 2);
		}
		//	gnl_val = expand_var(shell, gnl_val);
		// Fonction qui change la valeur de gnl_val -> pour gnl_val modifier avec la var
		else
		{
			write(temp_fd, gnl_val, ft_strlen(gnl_val));
			write(0, "> ", 2);
		}
		// SI valeur differentes -> sauvegarder et continuer
		free(gnl_val);
	}
	free(delemiter); // Fixing leaks
	free(gnl_val); // Fixing leaks
}


void replace_heredoc(t_shell *shell)
{
	int i = 0;
	int j = 0;
	int len = 0;
	char *new_cmd;
	char *tmp_file;

	tmp_file = ft_strdup("/tmp/.heredoc");
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '<')
		{
			i = i + 2;
			// ICI je dois faire gaffe que tant que c'est egal a un truc different de espace 
			if(shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] != ' ')
				i++;
			//printf("char -> %c\n", shell->cmd[i]);
		}	
		else
		{
			len++;
			i++;
		}
	}

	new_cmd = malloc(sizeof(char) * len + ft_strlen("/tmp/.heredoc") + 2); // Fix Valgrind write error, allocation memeroy was missing 1 bytes. 
	len = 0;
	i = 0;
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '<')
		{
			new_cmd[len] = shell->cmd[i];
			len++;
			i = i + 2;
			// ICI je dois faire gaffe que tant que c'est egal a un truc different de espace 
			if(shell->cmd[i] == ' ')
				i++;
			while (shell->cmd[i] != ' ')
				i++;
			while (tmp_file[j])
			{
				new_cmd[len] = tmp_file[j];
				len++;
				j++;
			}
		}	
		else
		{
			new_cmd[len] = shell->cmd[i];
			len++;
			i++;
		}
	}
	free(tmp_file); // Fixing leaks
	new_cmd[len] = '\0';
	free(shell->cmd); // Fixing leaks
	shell->cmd = ft_strdup(new_cmd);
	free(new_cmd); // Fixing leaks
}

int check_env_var(char *str)
{
	int i;

	i = 0; // Fix Valgrind, value not set at 0 to start to cross.
	while (str[i])
	{
		if(str[i] == '$')
			return(1);
		i++;
	}
	return(0);
}