#include "minishell.h"


int main(void)
{
    char *command;
    t_shell *shell;

    shell = malloc(sizeof(t_shell));
    while (1) {
        command = readline("Minishell : ");
        if (command == NULL || strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        }
        else if(main_check(command) == 1)
        {
            // La commande est identifier comme existante du coup on doit
            // passer par le lexiqeur, puis la tokenisation
            // puis le parser
            // et finalement l'executeur
            token(command, shell);
            printf("Command identify\n");
            // Main_check -> identifie toutes les commande comme il faut //
            // Avant d'effectuer une tokenisation il faut verif le reste de la commande //
        }
        else
            printf("Command not found -> %s\n", command);
        add_history(command);
        free(command);
    }
    return 0;
}
// HAVE TO MANAGE //
// -> echo      (with option -n)
// -> cd        (with only a relative or absolute path)
// -> pwd       (with no options)
// -> export    (with no options)
// -> unset     (with no options)
// -> env       (with no options or arguments)
// -> exit      (with no options)
