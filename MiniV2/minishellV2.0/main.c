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
    char *full_cmd;
    int i = 0;
    int j = 0;

    full_cmd = malloc(sizeof(char) * ft_strlen(cmd) + ft_strlen(binary) + 1);
    while(binary[i])
    {
        full_cmd[i] = binary[i];
        i++;
    }
    while(cmd[j] && cmd[j] != ' ')
    {
        full_cmd[i] = cmd[j];
        j++;
        i++;
    }
    full_cmd[i] = '\0';
    return(full_cmd);
}

int strlen_array(char **array_str)
{
    int i = 0;

    while(array_str[i])
        i++;
    return(i);
}

char **clean_quotes(char **array_str)
{
    int i = 0;
    int j = 0;
    int a = 0;
    int b = 0;

    char **clean_str;
    clean_str = malloc(sizeof(char *) * strlen_array(array_str));
    while(array_str[i])
    {
        j = 0;
        b = 0;
        clean_str[a] = malloc(sizeof(char) * ft_strlen(array_str[i]));
        while(array_str[i][j])
        {
            if(array_str[i][j] != '"' && array_str[i][j] != '\'')
            {
                clean_str[a][b] = array_str[i][j];
                j++;
                b++;
            }
            else
                j++;
        }
        clean_str[a][b] = '\0';
        a++;
        i++;
    }
    clean_str[i] = NULL;
    return(clean_str);
}

int    check_quotes(char **array_str)
{
    int i = 1;
    /*
    while(array_str[i])
    {

    }
    */
    return(1);
}

int    check_simple(char **array_str)
{
    int i = 1;
    int j = 0;
    int s_flag = 0;
    int d_flag = 0;

    while(array_str[i])
    {
        j = 0;
        while(array_str[i][j])
        {
            if(array_str[i][j] == '"')
                d_flag++;
            else if(array_str[i][j] == '\'')
                s_flag++;
            j++;
        }
        i++;
    }
    if(s_flag % 2 || d_flag % 2)
        return(1);
    else
        return(0);
}

int wait_end(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '"')
        {
            printf("-> return 0 %s\n", str);
            return(0);
        }
    }
    printf("-> return 1 %s\n", str);
    return(1);
}

void	ft_exec(char **envp, char *cmd, int id_cmd)
{
    // Il faut pouvoir split les arguments passer //
    // WE ARE IN THE CASE OF ECHO //
    char **array_str;
    int index = 1;
    if(id_cmd == 2)
    {
        // FOR THIS PART WE NEED TO CHECK IF THERE IS A SIMPLE "", IF THERE IS ONLY ONE ->  //
        // WE NEED TO CREATE A SECOND FUNCTION WHO ACTUALLY CALL GET_NEXT_LINE //
        array_str = ft_split(cmd, ' ');
        // TO CODE //
        // Check_simple(char **array_str);
       // if (check_simple(array_str) == 1) // MEANS THAT WE FIND ONLY ONE //
         //   while(wait_end(get_next_line(0))); // THE PROBLEM IS, I GET STUCK IN GET_NEXT_LINE FUNCTION //
            // SOLUTION -> CODE A MINI GET_NEXT_LINE
        // -> THEN LAUNCH get_next_line(); -> IN THAT, WAIT FOR THE OTHER "", cross the output at the research of it
        // IF HE FINDS IT OUTPUT THE FULL LINE //
        // TO CODE //
        char *path = ft_create_path(cmd ,"/usr/bin/");
        char **new_str = clean_quotes(array_str);
        int index = 0;
        execve(path, clean_quotes(array_str), NULL);
    }
    array_str = ft_split(cmd, ' ');
    //int i = 0;
    //while(array_str[i])
    //{
        // Now, all the element is stock in that array //
        // printf("->%s\n", array_str[i]);
        // i++;
    //}
    char *path = ft_create_path(cmd ,"/usr/bin/");
    execve(path, array_str ,NULL);
}

int cmd_id(char *u_cmd, char *f_cmd)
{
    int i = 0;
    int j;

    while(u_cmd[i] == f_cmd[i])
        i++;
    if(!u_cmd[i] || u_cmd[i] == ' ')
    {
        //printf("Commande identifier\n");
        return(0);
    }
    else
        return(1);
}

int Command_checker(char *commande)
{
    if(cmd_id(commande, "echo") == 0) // Il faut pouvoir gerer " " et ' '
        return (2);
    if(cmd_id(commande, "cd") == 0) // Utiliser -> opendir
        return (1);
    if(cmd_id(commande, "pwd") == 0) // V
        return (1);
    if(cmd_id(commande, "export") == 0) // Marche pas
        return (1);
    if(cmd_id(commande, "unset") == 0) // Marche pas
        return (1);
    if(cmd_id(commande, "env") == 0) // Marche pas
        return (1);
    if(cmd_id(commande, "exit") == 0) // V
        return (1);
    else
        return (0);
}

int main(int argc, char **argv, char **envp)
{
    char *commande;
    pid_t pid;
    int id_cmd;

    while (1) {
        // Afficher l'invite de commande et lire l'entrée de l'utilisateur
        commande = readline("Mini-shell : ");
        // Vérifier si la commande est NULL (EOF) ou "exit"
        if (commande == NULL || strcmp(commande, "exit") == 0)
        {
            free(commande);  // Libérer la mémoire allouée pour la commande
            break;
        }
        add_history(commande);
        id_cmd = Command_checker(commande);
        if (id_cmd)
        {
            pid = fork();
            if(pid == 0)
                ft_exec(envp, commande, id_cmd);
            else
                wait(0);
        }
        else
            printf("Command not found -> %s\n", commande);
        // Libérer la mémoire allouée pour la commande
        free(commande);
    }
    return 0;
}