#include "../../minishell.h"

int pars_export(char **pars_cmd)
{
	int i;
	int j;
	int j_copy = 0;
	int equal = 0;
	int flag = 0;

	i = 1;
	while(pars_cmd[i])
	{
		j = 0;
		equal = 0;
		flag = 0;
		while(pars_cmd[i][j])
		{
			if(pars_cmd[i][j] == '=' && equal == 0)
			{
				equal = 1;
				if(pars_cmd[i][j - 1] == ' ' || !pars_cmd[i][j - 1] || pars_cmd[i][j + 1] == ' ' || !pars_cmd[i][j + 1])
					return(0);
			}
			if(equal == 1 && flag == 0)
			{
				j_copy = j - 1;
				while (j_copy >= 0) // Fix Valgrind, condtion change from pars_cmd[i][j_copy] -> checking the 
				{
					if(ft_isalnum(pars_cmd[i][j_copy]) == 0)
					{
						//printf("char -> %c, index -> %d\n", pars_cmd[i][j_copy], j_copy);
						return(0);
					}
					j_copy--;	
				}
				flag = 1;
			}
			j++;
		}
		i++;
	}
	return(1);
}
// Probablement un parsing pas complet, mais ok pour le moment.