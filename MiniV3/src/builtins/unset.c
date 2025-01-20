#include "../../minishell.h"


char *build_cmp(char *str)
{
	int i = 0;
	char *cmp_cmd;

	while (str[i] && str[i] != '=')
		i++;
	if(str[i] != '=')
		return(NULL);
	cmp_cmd = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		cmp_cmd[i] = str[i];
		i++;
	}
	cmp_cmd[i] = '\0'; // Ajout du character manquant sa provoquait une erreur de unitilize val avec valgrind
	return(cmp_cmd);
}

void unset(t_shell *shell, t_token *token, int j)
{
	t_env *env_v = shell->env;
	t_env *prev = NULL;
	t_env *temp;
	char *cmp_cmd;
	
	j++;
    while (token[j].str)
    {
		if(token[j].str[0] == 0)
			break;
		env_v = shell->env;
		prev = NULL;
		// CHANGER LA VALEUR DE env_v->env_var -> puis la  //
		cmp_cmd = build_cmp(env_v->env_var);	
        if (env_v && str_cmp(cmp_cmd, token[j].str) == 1)
        {
            shell->env = env_v->next;
            free(env_v->env_var);
            free(env_v);
            j++;
            continue;
        }
		free(cmp_cmd);
        
		while (env_v && env_v->next)
        {
			cmp_cmd = build_cmp(env_v->next->env_var);
            if (str_cmp(cmp_cmd, token[j].str) == 1)
            {
               	temp = env_v->next;
                env_v->next = temp->next;
				free(cmp_cmd); // Leaks FIX
                free(temp->env_var);
                free(temp);
                break; 
            }
			free(cmp_cmd);
            env_v = env_v->next;
        }
        j++;
    }
}
