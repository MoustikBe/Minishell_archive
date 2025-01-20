#include "../../minishell.h"

// Toute la memoire a été correctement liberer et une commande valide a été trouver // 
t_token *token_main(char *cmd, t_token *token, t_shell *shell)
{
	int i;
	int j;
	int len_space;

	// WORK IN PROGRESS // 
	i = 0;
	j = 0;
	//printf("Valeur d'allocation -> %d\n", len_token(cmd));
	token = malloc(sizeof(t_token) * len_token(cmd));
//	if(!token)
//		return(0);
	while(i < len_token(cmd) - 1) // VUS QUE LES VERITABLES AFFECTATION VONT DE 0 a -> len_token - 1 car len_token = NULL CORRECTION VALGRIND BTW.
	{
		token[i].id = 0;
		len_space = len_for_token(cmd, j);
		// alloc de la memoire pour le char de la strucute // 
		token[i].str = malloc(sizeof(char) * len_space + 1);
//		if(!token[i].str)
//			return(0);
		token_copy(token, cmd, i, j);
		//printf("len_for_token -> %d\n", len_space);
		//printf("\033[0;31mtoken[i].str -> %s\033[00m\n", token[i].str); 
		if(token[i].str[0] == 0)
		{
			free(token[i].str);
			token[i].str = ft_strdup("\"");
		}
		token_id(token, i);
		//printf("\033[0;33mtoken[i].id  -> %d\033[00m\n", token[i].id);
		j = j + len_space; // valgrind -> avant = j = j + len_space + 1; Depassement de 1 byte 
		while(cmd[j] != '\0' && cmd[j] == ' ')
			j++;
		i++;
	}
	token[i].str = NULL; // AJOUT D'UNE VALEUR NULL POUR IDENTIFIER LA FIN DE LA LIST.
	token[i].id = 0; // AJOUT D'UNE VALEUR DE 0 POUR NE PAS DECLENCHER D'OPERATION DANS L'EXECUTEUR.
	// TO_PARSER FOR THE TOKEN // 
	token_parser(token, shell, len_token(cmd));
	shell->len_token = len_token(cmd);

	return(token);
} 

