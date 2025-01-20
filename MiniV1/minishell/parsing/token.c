#include "../minishell.h"

static int len_space(char *command, int i)
{
	int j = 0;
	while(command[i] == 32)
		i++;
	while(command[i] && command[i] != ' ')
	{
		i++;
		j++;
	}
	return(j);
}


static void ft_copy(char *command, char *token, int i, int len_space)
{
	int j = 0;

	while(j < len_space)
	{
		token[j] = command[i];
		i++;
		j++;
	}
	token[len_space] = '\0';
}

void    token(char *command, t_shell *shell)
{
    shell->cmd_token = ft_split(command, ' ');
	// REALISER UNE MATRIX EN 3D //
	char ***token;
	int	i = 0;
	int j = 0;
	int g = 0;
	int len_spc;

	while(command[i])
	{
		if(command[i] == ' ')
		{
			j++;
			i++;
		}
		else
			i++;
	}
	token = malloc(sizeof(char **) * 3);
	token[2] = NULL;
	token[0] = malloc(sizeof(char *) * j + 1);
	token[1] = malloc(sizeof(char *) * j + 1);

	// FAIRE LA LEN DE CE QUE L'ON N'A BESOIN //
	i = 0;

	while(g <= j + 1)
	{
		//printf("Valeur de len_space -> %d\n", len_space(command, i, 1));
		len_spc = len_space(command, i);
		printf("len_spc = %d\n", len_spc);
		token[0][g] = malloc(sizeof(char) * len_spc);
		ft_copy(command, token[0][g], i, len_spc);
		i = i + len_spc + 1;
		g++;
	}
	free(token);
	int a = 0;
	while(toe)
    /*
    int i = 0;
    while(shell->cmd_token[i])
    {
        printf("Token -> %s\n", shell->cmd_token[i]);
        i++;
    }
    //
     Il faudrait aussi pouvoir identifier le token en question //
     */
}