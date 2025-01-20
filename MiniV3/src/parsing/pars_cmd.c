#include "../../minishell.h"

/* Verification of the first element of the command */
int check_cmd_quotes(char *cmd_check)
{
	if(str_cmp_quotes(cmd_check, "echo") == 1 || str_cmp_quotes(cmd_check, "/bin/echo") == 1)
		return(2);
	else if(str_cmp_quotes(cmd_check, "cd") == 1)
		return(3);
	else if(str_cmp_quotes(cmd_check, "pwd") == 1 || str_cmp_quotes(cmd_check, "/bin/pwd") == 1)
		return(4);
	else if(str_cmp_quotes(cmd_check, "export") == 1)
		return(5);
	else if(str_cmp_quotes(cmd_check, "unset") == 1)
		return(6);
	else if(str_cmp_quotes(cmd_check, "env") == 1 || str_cmp_quotes(cmd_check, "/bin/env") == 1)
		return(7);
	else if(str_cmp_quotes(cmd_check, "exit") == 1)
		return(8);
	else if(check_syntax(cmd_check) == 1)
		return(9);
	else if(check_dolar(cmd_check) == 1)
		return(10);
	else if(check_bin_quotes(cmd_check) == 1 || direct_bin(cmd_check) == 1)
		return(1);
	return(0);
}
