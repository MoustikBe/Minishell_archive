#include "../../minishell.h"
/*
static int menu_token_verif(t_token *token, int i)
{
	// RETURN 0 == probleme
	if(token[i].id == 5)
	{
		// NEED TO DO A CUSTOM FUNCTION FOR SUB_PARSING //
	}
}
*/


char *make_to_pars(t_shell *shell, int i)
{
	char *to_pars;
	int j;
	int k;
	int k_save;

	k = 0;
	j = 0;
	k_save = 0;
	while(j != i && shell->cmd[k])
	{
		if(shell->cmd[k] == ' ')
		{
			j++;
			while (shell->cmd[k] == ' ')
				k++;
		}
		else 
			k++;
	}
	//On arrive pixel la ou le pipe est.
	j = 0;
	if(shell->cmd[k] != '\0')
		k++;
	k_save = k;
	while (shell->cmd[k] && shell->cmd[k] != '|')
	{	
		j++;
		k++;
	}
	to_pars = malloc(sizeof(char) * j + 1);
	j = 0;
	k = k_save;
	while (shell->cmd[k] && shell->cmd[k] != '|')
	{
		to_pars[j] = shell->cmd[k];
		j++;
		k++;
	}
	to_pars[j] = '\0';
	return(to_pars);
}

void token_parser(t_token *token, t_shell *shell, int len)
{
	char *to_pars;
	int return_val;
	int i;

	i = 0;
	return_val = 0;
	while(i < len)
	{
			// + Simple si c'est un pipe, decouper la commande et l'envoyer a verif de pipe 1 a prochain pipe, ou jusque rien
		if(token[i].id == 6)
		{
			// Function that cut the part that we need to pars after a pipe //
			to_pars = make_to_pars(shell, i);
			return_val = parsing_main(to_pars);
			free(to_pars);
			if (return_val == 0)
				shell->error = 1;
			// i est l'equivalent au nombre d'espace trouver entre chaque partie de la commande.
			// par exemple, echo -n wdawdawd
			// 				0     1   	2
			// La regle pour creer la commande pourrait alors être
			// Prendre shell->cmd en entier, et tant que j != i avancer, il bougera l'index jusque au bon char
			// ensuite tant que shell->cmd a l'index trouver n'est pas egal a | ou '\0' avancer et copier
			i++;
		}
		i++;
	}
	
	// Parcourir toute l'array de token, checker si l'id du pipe n'est pas répèter
	return ; // -> in case of error
}
