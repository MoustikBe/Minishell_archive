#include "../../minishell.h"

static int 	verify_access(char *pars_cmd)
{
	if(opendir(pars_cmd) == NULL)
		return(0);
	return(1);
	// 0 = echec // 
}

int pars_cd(char **pars_cmd)
{
	int i;

	i = 1;
	while(pars_cmd[i])
	{
		if(i == 2 && str_cmp(pars_cmd[i], "|") == 1)
			return(1);
		else if(i > 2 || i == 2 && str_cmp(pars_cmd[i], "|") != 1)
			return(0);
		else if(i == 1)
		{
			if(verify_access(pars_cmd[i]) == 0)
				return(0);
		}
		i++;
	}
	return(1);
	// 0 = echec 
}