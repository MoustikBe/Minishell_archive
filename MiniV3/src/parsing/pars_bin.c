#include "../../minishell.h"

int direct_bin(char *cmd)
{
    int i;

	i = 0;
	// Check if PATH EXIST FIRST 
	if(access(cmd, O_RDONLY) == 0)
		return(1);
	return(0);
}
