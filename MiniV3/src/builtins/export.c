#include "../../minishell.h"


int check_cmd(char *str)
{
	char *env_str;
	int i;
	int i_copy;
	int j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	 if (str[i] != '=' || i == 0 || str[i + 1] == '\0')
		return(0);
	return(1);
}


void add_to_env(t_shell *shell, char *str)
{
	t_env *env_v;
	t_env *new;

	if(check_cmd(str) == 0)
		return ;
	new = malloc(sizeof(t_env));
	if(!new)
		return ;
	new->env_var = ft_strdup(str);
	new->next = NULL;
	env_v = shell->env;
	while (env_v->next)
		env_v = env_v->next;
	env_v->next = new;
}
/*
	t_env *env_v;
	t_env *new;
	int i;

	env_v = shell->env;
	i = 0;
	// TANT QUE envp a du contenu // 
	while (envp[i])
	{
		// CREER UN NODE ET Y AJOUTER LA VALEUR ACTUEL // 
		new = malloc(sizeof(t_env));
		new->env_var = ft_strdup(envp[i]);
		new->next = NULL;
		if (shell->env == NULL) 
        {
            shell->env = new;
            env_v = shell->env;
        }
        else
        {
            env_v->next = new;
            env_v = env_v->next;
        }
		i++;
	}

*/

char *equal_cmd(char *str)
{
	int i;
	int j;
	char *equal;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	equal = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		equal[j] = str[i];
		i++;
		j++;
	}
	equal[j] = '\0';
	//printf("Equal -> %s\n", equal);
	return(equal);
}




void export(t_shell *shell, t_token *token, int j)
{
	char *equal;

	j++;
	if(!token[j].str)
	{
		t_env *env;

		env = shell->env;
		while (env != NULL)
		{
			printf("declare -x ");
			printf("%s\n", env->env_var);
			env = env->next;
		}
	}
	while(token[j].str && token[j].id != 6)
	{
		
		// ADDING IN THE ENV // 
		//printf("Adding -> %d\n", token[j].str);
		if(token[j].str[0] == 0)
			break;
		else
			equal = equal_cmd(token[j].str); // Fixing leaks, allocation in variable for better managaement. Adding condition as well.
		if(search_in_env(shell, equal))
		{
			// THE MOST STRANGE BUG, when I debug with g3 fsanitize, export replace dont work more // 
			// ADD THE VALUE AT THE END OF THE LIST
			add_to_env(shell, token[j].str);
			// REMOVE  THE OLDER VAL
			free(token[j].str);
			token[j].str = ft_strdup(equal); // Fixing leaks, allocation on a variable free at the end of the loop turn
			unset(shell, token, j - 1);
			j++;
		}
		else
		{
			add_to_env(shell, token[j].str);
			j++;
		}
		free(equal); // Fixing leaks
	}
	return ;
}

// Faire un parsing correcte sur le export !! 

// Petit bug sur l'export, il faut ajouter que SI
// Il y'a deja l'identifiant de la valeur changer seulement la valeur,
// Et garder l'identifiant mais en changer la valeur 
