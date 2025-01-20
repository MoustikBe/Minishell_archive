#include "../../minishell.h"

void env(t_shell *shell)
{
	t_env *env;

	env = shell->env;
	while (env != NULL)
	{
		printf("%s\n", env->env_var);
		env = env->next;
	}
}
