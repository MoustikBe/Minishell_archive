#include "minishell.h"


int main(void)
{
    char *command;
    t_shell *shell;
	int ret_val;

    shell = malloc(sizeof(t_shell));
    while (1) {
        command = readline("\033[34;01mMinishell : \033[00m");
        if (command == NULL || strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        }
		ret_val = main_check(command);
        if (ret_val == 1)
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
        else if(ret_val == 0)
            printf("\033[0;31mMinishell : command not found -> %s\033[00m\n", command);
        else if(ret_val == 2)
			printf("\033[0;31mMinishell : flag unknow for echo \033[00m\n");
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
