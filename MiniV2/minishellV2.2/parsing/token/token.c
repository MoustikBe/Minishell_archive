#include "../../minishell.h"

static int len_space(char *command, int i)
{
	int j = 0;
	while(command[i] == ' ')
		i++;
	while(command[i] && command[i] != ' ')
	{
		i++;
		j++;
	}
	return(j);
}

static int len_token(char *command, int i)
{
	int j = 0;
	while(command[i])
	{
		if(command[i] == ' ')
		{
			j++;
			i++;
		}
		else
			i++;
	}
	return(j);
}


void    token(char *command, t_shell *shell)
{
  	t_token *token;
	int i = 0;
	int c;
	int j = 0; // Reference pour la len de la commande
	int len_spc; // Stock la valeur de len_spc
	int a; // Reference pour la copie char par char dans token[index]
	int b; // Copie du nombre de len_spc pour copier a rebour
	int d; // Copie du nombre de i pour ne pas perdre la valeur de i incorecte

	j = len_token(command, i);
	token = malloc(sizeof(t_token) * j + 1);
	i = 0;
	c = 0;
    while(c <= j)
    {
        len_spc = len_space(command, i);
    	token[c].str = malloc(sizeof(char) * len_spc + 1);
        a = 0;
        b = len_spc;
        d = i;
        while(b)
        {
          token[c].str[a] = command[d];
          a++;
		  d++;
		  b--;
        }
        token[c].str[a] = '\0';
    	i = i + len_spc + 1;
        c++;
    }
    // Maintenant j'ai l'array de structure //
	// Maintenant il faut passer a la partie d'identification du token //
	set_id(token, j);
}