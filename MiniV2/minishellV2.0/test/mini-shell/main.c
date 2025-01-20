#include "mini.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}


char *ft_create_path(char *cmd, char *binary)
{
    char *str;
    int i = 0;
    int j = 0;

    str = malloc(sizeof(char) * 11 + ft_strlen(cmd));
    while(binary[i])
    {
        str[i] = binary[i];
        i++;
    }
    str[i] = '/';
    i++;
    while(cmd[j])
    {
        str[i] = cmd[j];
        i++;
        j++;
    }
    return(str);
}

void	ft_exec(char **envp, char *cmd)
{
    // Il faut pouvoir split les arguments passer //
    char **array_str = ft_split(cmd, ' ');

    int i = 0;
    int j;
    while(array_str[i])
    {
        printf("%s\n", array_str[i]);
        i++;
    }
    char *path = ft_create_path(cmd ,"/usr/bin");
    char *arguments[] = {cmd, NULL};
    execve(path,arguments ,NULL);
}

int cmd_id(char *u_cmd, char *f_cmd)
{
    int i = 0;
    int j;
    while(u_cmd[i] != ' ' || u_cmd[i])
    {
        j = 0;
        while(u_cmd[i] == f_cmd[j])
        {
            i++;
            j++;
        }
        i++;
    }
}

int Command_checker(char *commande)
{
    if(cmd_id(commande, "echo") == 0)
        return (0);
    if(strcmp(commande, "cd") == 0)
        return (0);
    if(strcmp(commande, "pwd") == 0)
        return (0);
    if(strcmp(commande, "export") == 0)
        return (0);
    if(strcmp(commande, "unset") == 0)
        return (0);
    if(strcmp(commande, "env") == 0)
        return (0);
    if(strcmp(commande, "exit") == 0)
        return (0);
    else
        return (1);
}

int main(int argc, char **argv, char **envp)
{
    char *commande;
    pid_t pid;

    while (1) {
        // Afficher l'invite de commande et lire l'entrée de l'utilisateur
        commande = readline("Mini-shell : ");

        // Vérifier si la commande est NULL (EOF) ou "exit"
        if (commande == NULL || strcmp(commande, "exit") == 0)
        {
            free(commande);  // Libérer la mémoire allouée pour la commande
            break;
        }
        // Construire une fonction de test pour toutes les commandes de la minishell
        // IF le menu renvoie 1 cela signfira que il y'a une commande a traiter
        // Il faut également reussire a comprendre le fonctionement des tokens.
        if (Command_checker(commande) == 0)
        {
            pid = fork();
            //Call of execution of ls
            // Apres l'exeuction de LS, le process enfant meure directement
            if(pid == 0)
                ft_exec(envp, commande);
            else
                wait(0);
        }
        else
            printf("Unknow command -> %s\n", commande);
        // Libérer la mémoire allouée pour la commande
        free(commande);
    }
    return 0;
}