
#include "../../minishell.h"

// -- V2 | SEUL PROBLEME AVEC CETTE VERSION J'OBTIENS UNE ERREUR DE MEMOIRE -- //
/*
static int check_flag(char *command)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while(command[i] != ' ' && command[i])
		i++;
	// MAINTENANT JE ME RETROUVE A L'ESPACE DONC SOIT IL Y'A UN FLAG SOIT IL Y'A SEULEMENT LE TEXTE //
	if(!command[i])
		return(1);
	while(command[i] == ' ')
		i++;
	if(command[i] == '-')
		flag = 1;
	if(flag != 1)
		return(1);
	else if((command[i] == '-' && command[i + 1] != 'n' && command[i + 2] == ' ') || (command[i] == '-' && command[i + 1] != 'n' && command[i + 2] == '\0'))
		return(0);
	else
		return(1);
}
*/
/*
static int check_flag(char *command)
{
    int i;
	int flag = 0;

    i = 0;
    while(command[i] && command[i] != '-')
		i++;
	if(command[i] == '-')
			flag = 1;
	if(flag != 1)
		return(1);
    if(command[i + 1] != '\0')
    {
        if((command[i + 1] == 'n' && command[i + 2] == ' ') || (command[i + 1] == 'n' && command[i + 2] == '\0'))
            return (1);
    }
    return (0);
}
*/

static int menu_cmd(char *command)
{
    if(cmd_check(command, "echo"))
        return(3);
    else if(cmd_check(command, "cd"))
        return(1);
    else if(cmd_check(command, "pwd"))
        return(1);
    else if(cmd_check(command, "export"))
        return(1);
    else if(cmd_check(command, "unset"))
        return(1); //
    else if(cmd_check(command, "env"))
        return(1); // Verif si il y'a bien pas d'avantages de choses apres //
    else if(check_bin(command))
        return(2);
    return(0);
}


int cmd_check(char *command, char *cmp_cmd)
{
    int i;

    i = 0;
    while(command[i] && command[i] != ' ')
    {
        if(command[i] != cmp_cmd[i])
            return(0);
        i++;
    }
    if(ft_strlen(cmp_cmd) == i)
        return(1);
    return(0);
}


int main_check(char *command)
{
    int men_cmd;

    if (menu_cmd(command) == 0)
        return (0);
    return(1);

}