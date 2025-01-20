#include "../../minishell.h"

// ETAPE 1, au lancement du programme copier tout le contenu de char **env dans la liste chainer t_env


void copy_env(char **envp, t_shell *shell)
{
	// FOR each element of the array envp -> do copy in a node and pass to the next one // 
	t_env *env_v;
	t_env *new;
	int i;

	shell->env = NULL;
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
	//env(shell);
	//printf("SUCCESS v\n");
}


