#include "../../minishell.h"

void cmd_cleaner(t_shell *shell)
{
	int i; 
	int mem;
	int j;
	char *pipe_cmd;


	i = 0;
	j = 0;
	mem = 0;
	// RECONNAITRE SI LA COMMANDE EST pwd| pwd pour transfo en pwd | pwd
	// OU ENCORE SI C'EST pwd|pwd pour transfo en pwd | pwd

	// RECOPIER LA COMMANDE A L'IDENTIQUE ET A CHAQUE FOIS QUE UN PIPE EST DETECTER 
	// AJOUTER UN ESPACE DEVANT ET UN DERRIERE
	// DONC POUR CHAQUE PIPE FAIRE + 2 EN ALLOC DE MEMOIRE.

	while(shell->cmd[i])
	{
		if(shell->cmd[i] == '<' && shell->cmd[i + 1] == ' ' || shell->cmd[i] == '>' && shell->cmd[i + 1] == ' ')
		{
			i++;
			while(shell->cmd[i] == ' ')
				i++;
		}
		else if(shell->cmd[i] == '|')
		{
			if(shell->cmd[i  - 1] != ' ')
				mem++;
			if(shell->cmd[i + 1] != ' ')
				mem++;
			mem++;
			i++;
		}
		else
		{
			i++;
			mem++;
		}
	}
	if(shell->cmd[i - 1] != ' ')
		mem++;
	pipe_cmd = malloc(sizeof(char) * mem + 3);
	i = 0; 
	while(shell->cmd[i])
	{
		if(shell->cmd[i] == '<' && shell->cmd[i + 1] == ' ' || shell->cmd[i] == '>' && shell->cmd[i + 1] == ' ')
		{
			pipe_cmd[j] = shell->cmd[i];
			j++;
			while(shell->cmd[++i] == ' ');
		}
		else if(shell->cmd[i] == '|')
		{
			if(shell->cmd[i  - 1] == ' ')
			{
				pipe_cmd[j] = '|';
				j++;
			}
			else 
			{
				pipe_cmd[j] = ' ';
				pipe_cmd[j + 1] = '|';
				j = j + 2;
			}
			if(shell->cmd[i + 1] != ' ')
			{
				pipe_cmd[j] = ' ';
				j++;
			}
			i++;
		}
		else
		{
			pipe_cmd[j] = shell->cmd[i];
			i++;
			j++;
		}
	}
	if(shell->cmd[i - 1] != ' ')
	{
		pipe_cmd[j] = ' ';
		j++;
	}
	pipe_cmd[j] = '\0';
	//printf("%s\n", pipe_cmd);
	free(shell->cmd); // Fixing leaks
	shell->cmd = ft_strdup(pipe_cmd);
	free(pipe_cmd);
}

int verif_quotes(char *cmd)
{
	int i;
	int quote_s;
	int quote_d;

	quote_s = 0;
	quote_d = 0;
	i = 0;
	while (cmd[i])
	{
		
		if(cmd[i] == '"')
			quote_d++;
		else if(cmd[i] == '\'')
			quote_s++; 
		i++;

	}
	//printf("quote_d -> %d\nquote_s -> %d\n", quote_d, quote_s);
	if(quote_d % 2 == 0 && quote_s % 2 == 0)
		return(0);
	return(1);
}