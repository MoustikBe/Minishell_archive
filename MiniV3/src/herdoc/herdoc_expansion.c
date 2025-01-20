#include "../../minishell.h"

void heredoc_expansion(t_shell *shell, char *gnl_val, int temp_fd)
{
	// IL FAUT PARCOURIR LA shell->cmd ET detecter si jamais il y'a une variable d'env.
	// SA detecte les dolars si on envois un char * -> check_cmd_quotes();
	// FAIRE UN SPLIT de la cmd. Si la fonction renvois 10. -> il faut changer la commande. 
	
	// TENTATIVE // 
	int i = 0;
	int i_copy = 0;
	int j = 0;
	int len = 0;
	int ret_val = 0;
	int flag = 0;
	char *cmp_cmd;

	// CONNAITRE la len de la nouvelle commande. donc
	while (gnl_val[i])
	{
		// TROUVER UN MOYEN DE SAVOIR SI IL S'AGIT DE $?
		if(gnl_val[i] == '$')
		{
			if(gnl_val[i + 1] == '?' && gnl_val[i + 2] == ' ')
				return ;
			flag = 1;
			i++;
			i_copy = i;
			while (gnl_val[i] && gnl_val[i] != ' ' && gnl_val[i_copy] != '\n')
			{
				i++;
				j++;
			}
			cmp_cmd = malloc(sizeof(char) * j + 1);
			j = 0;
			while (gnl_val[i_copy] && gnl_val[i_copy] != ' ' && gnl_val[i_copy] != '\n')  
			{
				cmp_cmd[j] = gnl_val[i_copy];
				j++;
				i_copy++;
			}
			cmp_cmd[j] = '\0';
			// PARFAITE CMP_CMD DECOUPER 
			// MNT essaye de trouver une correspondance et si il y'a une correspondance 
			// RENVOYER 1 SI PAS 0
			//printf("cmp_cmd -> %s\n", cmp_cmd);
			len = len + search_in_env_writed(shell, cmp_cmd, temp_fd);
			//printf(" len_search -> %d\n", search_in_env(shell, cmp_cmd));
		}
		else
		{
		//	printf("char -> %c\n", shell->cmd[i]);
			ft_putchar_fd(gnl_val[i], temp_fd);
			len++;
			i++;
		}
	}
	ft_putchar_fd('\n', temp_fd);
}