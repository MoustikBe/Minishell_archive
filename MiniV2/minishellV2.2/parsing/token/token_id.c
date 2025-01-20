#include "../../minishell.h"

static int flag_check(char *echo)
{
	int i;

	while(echo[i])
    {
          if(echo[i] == '-')
		  {
            i++;
            if(echo[i] != 'n')
              return(0);
			while(echo[i] == 'n')
			{
				if(echo[i] != 'n')
					return(0);
             	i++;
			}
			if(echo[i] == '\0')
				return(2);
          }
          i++;
    }
    return(1);
}

static int is_cmd(char *str)
{
    if(cmd_check(str, "echo"))
        return(11);
    else if(cmd_check(str, "cd"))
        return(12);
    else if(cmd_check(str, "pwd"))
        return(13);
    else if(cmd_check(str, "export"))
        return(14);
    else if(cmd_check(str, "unset"))
        return(15); //
    else if(cmd_check(str, "env"))
        return(16);
    else if(check_bin(str))
        return(10);
    return(0);
}

static int is_flag(char *str)
{
	return(str && str[0] == '-');
}

static int is_infile(char *str, t_token *token, int i)
{
    if(i == 0)
      	return(0);
  	if(token[i - 1].str[0] == '<' || token[i - 1].str[0] == '<' && token[i - 1].str[1] == '<')
          return(1);
	return(0);
}

static int is_outfile(char *str, t_token *token, int i)
{
    if(i == 0)
      	return(0);
  	if(token[i - 1].str[0] == '>' || token[i - 1].str[0] == '>' && token[i - 1].str[1] == '>')
          return(1);
	return(0);
}

static int is_syntax(char *str)
{
	if(cmd_check(str, "|") || cmd_check(str, "<") || cmd_check(str, ">") || cmd_check(str, "<<") || cmd_check(str, ">>"))
        return(1);
	else
		return(0);

}

static int is_char(char *str)
{
	int len;

	len = ft_strlen(str);
	if(str[0] == '"' && str[len - 1] == '"' || str[0] == '\'' && str[len - 1] == '\'')
          return(1);
	return(0);
}
void    set_id(t_token *token, int j)
{
    int i = 0;

    // Parcourir toute l'array, et identifier un par un tout les membre //
    while(i <= j)
    {
        if(is_cmd(token[i].str))
        {
         	token[i].id = is_cmd(token[i].str);
			if(token[i].id == 11)
			{
				// VERIFIER SI I + 1 EXISTE POUR CHECKER SI IL EST POSSIBLE DE L'UTILISER SINON SEGFAULT //
				if(j > 0)
                {
					if(flag_check(token[i + 1].str) == 2)
						token[i].id = 17;
                }
			}
        }
        else if(is_flag(token[i].str))
			token[i].id = 2;
        else if(is_infile(token[i].str, token, i))
            token[i].id = 3;
        else if(is_outfile(token[i].str, token, i))
			token[i].id = 4;
        else if(is_char(token[i].str))
			token[i].id = 5;
        else if(is_syntax(token[i].str))
            token[i].id = 6;
        else
            token[i].id = 0;
        i++;
    }

    i = 0;
    while(i <= j)
    {
        printf("Token[%d] char * -> %s\n", i,token[i].str);
        printf("Token[%d] int -> %d\n", i,token[i].id);
        i++;
    }
}
// CREER UN TOKEN POUR L'IDENTIFICATION DE -n pour echo //

/*
        if(is_char(token[i].str))
            token[i].id = 5;



 */