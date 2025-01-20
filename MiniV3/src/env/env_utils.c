#include "../../minishell.h"

int search_in_env_writed(t_shell *shell, char *cmp_cmd, int temp_fd)
{
	t_env *env_v;
	char *cmp_cmd_2;
	int i = 0;

	env_v = shell->env;
	while (env_v)
	{
		cmp_cmd_2 = build_cmp(env_v->env_var);
		//printf("cmp_1 -> %s cmp_2 -> %s\n", cmp_cmd, cmp_cmd_2);
		if(str_cmp(cmp_cmd, cmp_cmd_2) == 1)
		{
			while (env_v->env_var[i] != '=')
				i++;
			i++;
			while (env_v->env_var[i])
			{
			
				ft_putchar_fd(env_v->env_var[i], temp_fd);
				i++;
			}
			return(ft_strlen(env_v->env_var) - ft_strlen(cmp_cmd_2));
		}
		free(cmp_cmd_2);
		env_v = env_v->next;
	}
	return(0);
}