#include "../../minishell.h"

void pwd(void)
{
	// RECUPER LE REPERTOIRE COURANT, ET L'AFFICHER
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}