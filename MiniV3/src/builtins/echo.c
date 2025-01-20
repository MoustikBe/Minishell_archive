#include "../../minishell.h"
// ont a besoin du nombre de i dans l'array de struct 
void	echo(t_token *token, t_shell *shell, int j)
{
	int i;
	int flag = 0;
	int terminal;
	/*	LES REGLES DU BULTIN ECHO */
	// ECHO peut recevoir n'importe quoi en parametre, 
	// premiere choses a faire est de voir si il y'a un flag au debut -> V
	// SI il y'a un flag appliquer le flag -> V
	// SI pas de flag continuer et ecrire les char -> V  
	// Il est aussi possible que le token soit un infile ou outfile,
	// SI c'est le cas faire simplement le necessaire pour ne pas  
	// TRES BON POINT A NOTER !!!!!, echo <<test >out.txt n'est pas a prendre ne fonctionne pas sur bash 
	
	// Echo is identify now we go direct to the second part of the commmand
	j++;
	while(token[j].id == 2)
	{
		// CHECKER SI LE FLAG est bien -n 
		i = 1;
		if(token[j].str[0] == '-')
		{
			while (token[j].str[i] && token[j].str[i] == 'n')
				i++;
			//printf("%c", token[j].str[i]);
			if(token[j].str[i] == 0)
			{	
				j++;
				flag = 1;
			}
			else
				break;
		}
	}
	//fprintf(stderr, "j -> %d\n", j);
	while(token[j].id != 6 && token[j].str)
	{
		if(token[j].str[0] == 0)
			break;
		if(str_cmp(token[j].str, "\"") == 1)
			j++;
		/*
		printf("looping, %d\n",token[j].str[k]);
		while (token[j].str[k])
		{
			printf("char -> %c\n", token[j].str[k]);
			k++;
		}
		
		if(str_cmp(token[j].str, " ") == 1)
			j++;
		*/
		else if(token[j].id == 4 || token[j].id == 40 || token[j].id == 5)
			j++;
		/*
		else if(str_cmp(token[j].str, "$?"))
		{
			ft_putnbr(shell->last_exit_status);
			j++;
		}
		*/
		else
		{
			i = 0;
			while (token[j].str[i])
			{
				ft_putchar_fd(token[j].str[i], 1);
				i++;
			}
			ft_putchar_fd(' ', 1);
			j++;
		}
	}
	if(flag == 0)
		printf("\n");
}
