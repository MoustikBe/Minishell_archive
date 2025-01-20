#include "../../minishell.h"


int pars_dolar(char **pars_cmd)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 0;
	while(pars_cmd[i])
	{
		j = 0;
		if(pars_cmd[i][j] != '$')
		{
			// Checker si il s'agit d'une commande dans l'index d'avant
			if(check_cmd_quotes(pars_cmd[i]) == 0)
			{
				if(str_cmp(pars_cmd[i], "|") == 1)
				{
					if(i > 1 && str_cmp(pars_cmd[i - 1], "|") == 1) 
						return(0);
					i++;
				}
				else
					return(0);
			}
			else
				i++;
		}
		else
		{
			while(pars_cmd[i][j])
			{
				if(pars_cmd[i][j] == '$' || pars_cmd[i][j] == '|')
					j++;
				else if(((pars_cmd[i][j] >= 48) && (pars_cmd[i][j] <= 57)) || ((pars_cmd[i][j] >= 65) && (pars_cmd[i][j] <= 90)) || ((pars_cmd[i][j] >= 97) && (pars_cmd[i][j] <= 122)) || pars_cmd[i][j] == '_' || pars_cmd[i][j] == '?')
					j++;
				else
					return(0);    
			}
			i++;
		}
	}
	return(1);
}
