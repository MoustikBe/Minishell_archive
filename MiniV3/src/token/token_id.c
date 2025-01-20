#include "../../minishell.h"

int is_var(t_token *token, int i)
{
	if(str_cmp("$?", token[i].str) == 1)
	{
		token[i].id = 9;
		return(1);
	}
	if(token[i].str[0] == '$')
	{
		token[i].id = 8;
		return(1);
	}
	return(0);
}

int is_char(t_token *token, int i)
{
	int len;

	len = ft_strlen(token[i].str);
	if(token[i].str[0] == '"' && token[i].str[len - 1] == '"' || token[i].str[0] == '\'' && token[i].str[len - 1] == '\'')
    {
		token[i].id = 7;
		return(1);
	}
	return(0);
}

int is_pipe(t_token *token, int i)
{
	int j = 0;

	while(token[i].str[j])
	{
		if(token[i].str[j] == '|')
		{
			if(j > 0)
			{
				if(token[i].str[j - 1] != '\'' && token[i].str[j - 1] != '"')
				{
					token[i].id = 6;
					return(1);
				}
			}
			else
			{
				token[i].id = 6;
				return(1);
			}
		}
		j++;
	}
	return(0);

}

/* Flemme pour le moment */
int is_infile(t_token *token, int i)
{
	//int len;
	int j = 0;

	//len = ft_strlen(token[i].str);
    if(i > 0 && token[i - 1].str[0] == '<' && token[i - 1].str[1] != '<')
		token[i].id = 5;
	else if(token[i].str[0] == '<' && token[i].str[1] != '<')
		token[i].id = 5;
	if(token[i].id == 5)
	{
		token[i].str = clean_name(token[i].str);
		return(1);
	}
	// Il manque a gerer un cas, le cas ou il y'a une commande coller au reste exemple : cat<main.c
	return(0);
}

int is_outfile_append(t_token *token, int i)
{
	int j = 0;
	// 1 cas, echo hello >> test.txt 
    if(i > 0 && token[i - 1].str[0] == '>' && token[i - 1].str[1] == '>')
		token[i].id = 40;
	// 2 cas, echo hello >>test.txt
	else if(token[i].str[0] == '>' && token[i].str[1] == '>')
		token[i].id = 40;
	// 3 cas, echo hello>>test.txt
	else if(token[i].str[j])
	{
		while(token[i].str[j])
		{
			if(j > 0)
			{
				if(token[i].str[j - 1] != '"' && token[i].str[j - 1] != '\'' && token[i].str[j] == '>' && token[i].str[j + 1] == '>')
				{
					token[i].id = 40;
					return(1);
				}
			}
			j++;
		}
	}
	// 4 cas, echo hello ">>" test.txt -> pas conciderer comme un outfile
	
	if(token[i].id == 40)
	{
		token[i].str = clean_name(token[i].str);
		return(1);
	}
	
	return(0);
}



int is_outfile(t_token *token, int i)
{
	int j = 0;
	// 1 cas, echo hello >> test.txt 
    if(i > 0 && token[i - 1].str[0] == '>' && token[i - 1].str[1] != '>')
		token[i].id = 4;
	// 2 cas, echo hello >>test.txt
	else if(token[i].str[0] == '>' && token[i].str[1] != '>')
		token[i].id = 4;
	// 3 cas, echo hello>>test.txt
	else if(token[i].str[j])
	{
		while(token[i].str[j])
		{
			if(j > 0)
			{
				if(token[i].str[j - 1] != '"' && token[i].str[j - 1] != '\'' && token[i].str[j] == '>' && token[i].str[j + 1] != '>')
				{
					token[i].id = 4;
					return(1);
				}
			}
			j++;
		}
	}
	// 4 cas, echo hello ">>" test.txt -> pas conciderer comme un outfile
	
	if(token[i].id == 4)
	{
		token[i].str = clean_name(token[i].str);
		return(1);
	}
	
	return(0);
}

int is_flag(t_token *token, int i)
{
	if(token[i].str[0] == '-')
	{
		token[i].id = 2;
		return(1);
	}
	return(0);
}

int is_cmd(t_token *token, int i)
{

    if(str_cmp(token[i].str, "echo") || str_cmp(token[i].str, "/bin/echo"))
        token[i].id = 11;
    else if(str_cmp(token[i].str, "cd"))
        token[i].id = 12;
    else if(str_cmp(token[i].str, "pwd") || str_cmp(token[i].str, "/bin/pwd"))
        token[i].id = 13;
    else if(str_cmp(token[i].str, "export"))
        token[i].id = 14;
    else if(str_cmp(token[i].str, "unset"))
        token[i].id = 15;
    else if(str_cmp(token[i].str, "env") || str_cmp(token[i].str, "/bin/env"))
		token[i].id = 16;
	else if(str_cmp(token[i].str, "exit"))
		token[i].id = 17;
    else if(check_bin(token[i].str) || direct_bin(token[i].str))
        token[i].id = 10;
	if(token[i].id > 9)
		return(1);
	return (0); // = pas de resultat
}
