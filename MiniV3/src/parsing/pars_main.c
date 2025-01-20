#include "../../minishell.h"


int pars_except(char *cmd)
{
	int i;

	i = 0;
	if(cmd[0] == '\0')
		return(0);
	while(cmd[i] == ' ')
		i++;
	if(cmd[i] == '\0')
		return(0);
	return(1);
}


int parsing_main(char *cmd)
{
	// Savoir si il s'agit d'une commande écrite au début ou alors ou <, > ou <<, >> et $VARIABLE. Seul ses
	char **pars_cmd;
	int ret_val;
	/*
	if(check_quotes(shell->cmd) == 1)
	{
		if(quotes_mod(shell) == 0)
			return(0);
	}
	*/

	// Il faut encore gerer le cas de /bin/ls directement //
	if(pars_except(cmd) == 0)
		return(0);
	pars_cmd = ft_split(cmd, ' ');
	//Effectuer une verif stricte sur la commande mnt 

	/*
	int i = 0;
	while(pars_cmd[i])
	{
		printf("pars_cmd %d -> |%s|\n", i, pars_cmd[i]);
		i++;
	}
	*/
	if(pars_cmd[0] == NULL) // Fix Valgrind, segfault in the case of ''
	{
		free_array(pars_cmd);
		return(-1);
	}
	ret_val = check_cmd_quotes(pars_cmd[0]); 
	// Le parsing est seulement extremement important dans le cas des builtins. //
	// Dans le cas d'un chemin binaire le parsing s'execute avec le excve //
	if(ret_val == 1)
	{
		// /bin/cmd -> pas besoin de + de parsing // 
		free_array(pars_cmd);
		return(1);
	}
	else if(ret_val > 1)
    {
		// echo		-> pas besoin de parsing // -> pas sure, gerer les pipes
		// pwd		-> pas besoin de parsing // 
		// unset	-> pas besoin de parsing // 
		// env		-> pas besoin de parsing // 
		// bin		-> pas besoin de parsing //
		// exit		-> pas besoin de parsing // -> pas sure 

		//  -- Verifier les autres element -- // 
		/*  -- Parsing de cd -- */
		if(ret_val == 3)
		{	
			if(pars_cd(pars_cmd) == 0)
			{
				free_array(pars_cmd);
				return(0);
			}
			free_array(pars_cmd);
			return(1);
		}
		/*  -- Parsing d'export -- */
		if(ret_val == 5)
		{	
			if(pars_export(pars_cmd) == 0)
			{
				free_array(pars_cmd);
				return(0);
			}
			free_array(pars_cmd);
			return(1);
		}
		/*  -- Parsing de syntax -- */
		if(ret_val == 9)
		{	
			if(pars_syntax(pars_cmd) == 0)
			{
				free_array(pars_cmd);
				return(0);
			}
			free_array(pars_cmd);
			return(1);
		}
		/*  -- Parsing de dollar -- */
		if(ret_val == 10)
		{	
			if(pars_dolar(pars_cmd) == 0)
			{
				free_array(pars_cmd);
				return(0);
			}
			free_array(pars_cmd);
			return(1);
		}
		// SI tout est bon, pas oublier de free et de return(1);
		free_array(pars_cmd);
		return(1);
    }
	
    // Verif_cmd V Verif_input X Verif_$ X
	// 0 = parsing non valide //
	free_array(pars_cmd);
	return(0);
}


// REMODIFIER LE SPLIT POUR QUE UNE FOIS DANS LE CAS OU ON A cmd|cmd //  
// Il doit considerer le pipe comme un separateur de mot //
