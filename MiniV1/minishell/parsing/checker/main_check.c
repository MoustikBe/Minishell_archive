#include "../../minishell.h"

static int cmd_check(char *command, char *cmp_cmd)
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
    if(cmd_check(command, "echo"))
    {
        if(echo_checker(command)) // Verif si l'argument qui suit est bien -n
             return(1);
   }
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
    return(0);
}