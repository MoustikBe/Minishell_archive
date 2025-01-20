#include "../../minishell.h"

int in_out(t_token *token, int j)
{
	char *fd_mngt;
	int file;
	int terminal_copy;

	terminal_copy = dup(STDOUT_FILENO);
	while (token[j].id != 6 && token[j].str)
	{
		if(token[j].id == 4 || token[j].id == 40 || token[j].id == 5)
		{
			// OUTFILE
			if(token[j].id == 4)
			{
				fd_mngt = ft_strdup(token[j].str);
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
			// OUTFILE -> APPEND
			else if(token[j].id == 40)
			{
				fd_mngt = ft_strdup(token[j].str);
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
		}
		j++;
	}
	return(terminal_copy);
}