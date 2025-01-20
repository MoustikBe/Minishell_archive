#include "../../minishell.h"

/*
char *expanding_cmd(t_shell *shell)
{
	int i = 0;
	int i_copy = 0;
	int j = 0;
	int len = 0;
	char *cmp_cmd;

	// CONNAITRE la len de la nouvelle commande. donc
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '$')
		{
			i++;
			i_copy = i;
			while (shell->cmd[i] && shell->cmd[i] != ' ')
			{
				i++;
				j++;
			}
			cmp_cmd = malloc(sizeof(char) * j + 1);
			j = 0;
			while (shell->cmd[i_copy] && shell->cmd[i_copy] != ' ')
			{
				cmp_cmd[j] = shell->cmd[i_copy];
				j++;
				i_copy++;
			}
			printf("cmp_cmd -> %s\n", cmp_cmd);
		}
		i++;
	}
}
*/


int search_in_env(t_shell *shell, char *cmp_cmd)
{
	t_env *env_v;
	int len; // Fixing leaks, len store the len of the cmp_cmd before the free
	char *cmp_cmd_2;

	env_v = shell->env;
	while (env_v)
	{
		cmp_cmd_2 = build_cmp(env_v->env_var);
		//printf("cmp_1 -> %s cmp_2 -> %s\n", cmp_cmd, cmp_cmd_2);
		if(str_cmp(cmp_cmd, cmp_cmd_2) == 1)
		{
			//printf("MATCH\n");
			len = ft_strlen(cmp_cmd_2);
			free(cmp_cmd_2);  // Fixing leaks, value not free at the start.
			return(ft_strlen(env_v->env_var) - len); // Fix valgrind, bad assembly of the value for cmp_cmd with quote.
			
		}
		free(cmp_cmd_2);
		env_v = env_v->next;
	}
	return(0);
}

int copy_env_cmd(int j_copy, int i, t_shell *shell)
{
	//printf("i -> %d\n", i);
	t_env *env_v;
	char *exit_val;
	char *cmp_cmd_1;
	char *cmp_cmd_2;
	int j = 0;
	int i_exit = 0;
	int len = 0;

	if(shell->cmd[i + 1] == '?' && shell->cmd[i + 2] == ' ')
	{
		// RETURN LA LEN DE L'ITOA DE LAST_EXIT_VALUE
		// SHELL->env_cmd = copier dans l'index correcte la valeur de l'ITOA DE LAST_EXIT_VALUE  
		exit_val = ft_itoa(shell->last_exit_status);
		//printf("%s\n", exit_val);
		while(exit_val[i_exit])
		{
			shell->env_cmd[j_copy] = exit_val[i_exit];
			//printf("cmd env_cmd... |%c| index -> %d\n", shell->env_cmd[j_copy], j_copy);
			j_copy++;
			i_exit++;
			//printf("looping\n");
		}
		free(exit_val);
		return(i_exit);
	}
	env_v = shell->env;
	while (env_v)
	{
		//BUILDING OTHER
		j = i;
		while (shell->cmd[i] && shell->cmd[i] != ' ' && shell->cmd[i] != '"')
		{
			len++;
			i++;
		}
		i = j;
		cmp_cmd_1 = malloc(sizeof(char) * len + 1);
		len = 0;
		i++;
		while (shell->cmd[i] && shell->cmd[i] != ' ' && shell->cmd[i] != '"')
		{
			cmp_cmd_1[len] = shell->cmd[i];
			len++;
			i++;
		}
		cmp_cmd_1[len] = '\0';
		i = j;
		j = 0;
		len = 0;
		cmp_cmd_2 = build_cmp(env_v->env_var);
		//printf("cmd_1 %s\n", cmp_cmd_1);
		//printf("cmp_1_V -> %s cmp_2_V -> %s\n", cmp_cmd_1, cmp_cmd_2);
		if(str_cmp(cmp_cmd_1, cmp_cmd_2) == 1)
		{
		//	printf("MATCH_V\n");
			while(env_v->env_var[len] != '=')
				len++;
			len++;
			while (env_v->env_var[len])
			{	
				shell->env_cmd[j_copy] = env_v->env_var[len];
				j_copy++;
				j++;
				len++;
			}
			free(cmp_cmd_1);
			free(cmp_cmd_2); // Fix leaks, (not sure add by me to prevent possible leaks)
			return (j);
		}
		else
		{
			free(cmp_cmd_1);
			free(cmp_cmd_2);
			env_v = env_v->next;
		}
	}
	return(0);
}


void expansion(t_shell *shell)
{
	// IL FAUT PARCOURIR LA shell->cmd ET detecter si jamais il y'a une variable d'env.
	// SA detecte les dolars si on envois un char * -> check_cmd_quotes();
	// FAIRE UN SPLIT de la cmd. Si la fonction renvois 10. -> il faut changer la commande. 
	
	// TENTATIVE // 
	int quot_flag = 0;
	int i = 0;
	int i_copy = 0;
	int j = 0;
	int len = 0;
	int ret_val = 0;
	int flag = 0;
	int j_copy;
	char *cmp_cmd;
	char *char_itoa; // Fix leaks, issue because not set in a var that we can free 

	// CONNAITRE la len de la nouvelle commande. donc
	while (shell->cmd[i])
	{
		//printf("Crossing this char -> %c\n", shell->cmd[i]);
		// TROUVER UN MOYEN DE SAVOIR SI IL S'AGIT DE $?
		if(shell->cmd[i] == '$' && quot_flag == 0)
		{
			flag = 1;
			i++;
			i_copy = i;
			while (shell->cmd[i] && (ft_isalnum(shell->cmd[i]) || shell->cmd[i] == '_') || shell->cmd[i] == '?')
			{
				i++;
				j++;
			}
			cmp_cmd = malloc(sizeof(char) * j + 1);
			j = 0;
			while (shell->cmd[i_copy] && (ft_isalnum(shell->cmd[i_copy]) || shell->cmd[i_copy] == '_') || shell->cmd[i_copy] == '?')
			{
				cmp_cmd[j] = shell->cmd[i_copy];
				j++;
				i_copy++;
			}
			cmp_cmd[j] = '\0';
			// PARFAITE CMP_CMD DECOUPER 
			// MNT essaye de trouver une correspondance et si il y'a une correspondance 
			// RENVOYER 1 SI PAS 0
			if(str_cmp(cmp_cmd, "?") == 1)
			{
				char_itoa = ft_itoa(shell->last_exit_status); // Fix leaks, management of the memory for ft_itoa
				len = len + ft_strlen(char_itoa);
				free(char_itoa);
			}
			else 
				len = len + search_in_env(shell, cmp_cmd); 
			free(cmp_cmd); // Fix leaks, memory free after stop using it
			//printf(" len_search -> %d\n", search_in_env(shell, cmp_cmd));
		}
		else
		{
		//	printf("char -> %c\n", shell->cmd[i]);
			if(shell->cmd[i] == '\'' && quot_flag == 0)
				quot_flag = 1;
			else if(shell->cmd[i] == '\'' && quot_flag == 1)
				quot_flag = 0;
			len++;
			i++;
		}
	}
//	printf(" len -> %d\n", len);
	if(flag != 1)
		return ;
	shell->env_cmd = malloc(sizeof(char) * (len + 2));
	// CORRECTE LEN TROUVER// 
	// COPIE MNT //
	i = 0;
	i_copy = 0;
	j = 0;
	quot_flag = 0;
	while (shell->cmd[i])
	{
		if(shell->cmd[i] == '$' && quot_flag == 0)
		{
			i_copy = i;
			j_copy = j;
			while (shell->cmd[i] && shell->cmd[i] != ' ' && shell->cmd[i] != '"')
				i++;
			j = j + copy_env_cmd(j_copy, i_copy, shell);
		//	printf("cmd var... |%c| index -> %d\n", shell->cmd[i], i);
		}
		else
		{
		//	printf("cmd normal... |%c| index -> %d\n", shell->cmd[i], i);
			if(shell->cmd[i] == '\'' && quot_flag == 0)
				quot_flag = 1;
			else if(shell->cmd[i] == '\'' && quot_flag == 1)
				quot_flag = 0;
			shell->env_cmd[j] = shell->cmd[i];
			j++;
			i++;
		}
	}
	shell->env_cmd[j] = '\0';
	free(shell->cmd);
	shell->cmd = ft_strdup(shell->env_cmd);
	free(shell->env_cmd);
}

// echo hello word "$USER"