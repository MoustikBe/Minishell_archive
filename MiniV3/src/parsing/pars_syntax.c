#include "../../minishell.h"

static int len_array(char **pars_cmd)
{
	int i;

	i = 0;
	while(pars_cmd[i])
		i++;
	return(i);
}


static char *create_path(char **pars_cmd)
{
	char *tiny_path;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	if(pars_cmd[i][1] != '\0')
	{
		// Dans le cas ou c'est <main.c
		i = 1;
		tiny_path = malloc(sizeof(char) * ft_strlen(pars_cmd[0]));
		while(pars_cmd[0][i])
		{
			tiny_path[j] = pars_cmd[0][i];
			j++;
			i++;
		}
		tiny_path[j] = '\0';
		return(tiny_path);
	}
	else
	{
		i = 0;
		tiny_path = malloc(sizeof(char) * ft_strlen(pars_cmd[1]) + 1);
		while(pars_cmd[1][i])
		{
			tiny_path[j] = pars_cmd[1][i];
			j++;
			i++;
		}
		tiny_path[j] = '\0';
		return(tiny_path);
	}
	return(tiny_path);
}


int pars_syntax(char **pars_cmd)
{
	int i;
	int j;
	int len;

	len = len_array(pars_cmd);
	i = 1;
	if(pars_cmd[0][0] == '<')
	{ 
		if(pars_cmd[0][i] != '<')
		{
			// Make a tiny path // 
			char *tiny_path;
			tiny_path = create_path(pars_cmd);
			if(access(tiny_path ,F_OK) < 0)
			{
				free(tiny_path);
				printf("\033[0;31mMinishell : no such file or directory \033[00m\n");
				return(0);
			}
			free(tiny_path);
		}
	}
	return(1);
}