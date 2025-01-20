#include "../../minishell.h"
#include <fcntl.h>

static char *get_bin_path(char *command, char *bin)
{
	char *bin_path;
	int i;
	int j;

	i = 0;
    j = 0;
	bin_path = malloc(sizeof(char) * ft_strlen(command) + ft_strlen(bin));
	bin_path[ft_strlen(command) + ft_strlen(bin)] = '\0';
	while(bin[i])
	{
          bin_path[i] = bin[i];
          i++;
	}
	while(command[j] && command[j] != ' ')
	{
          bin_path[i] = command[j];
          i++;
          j++;
	}
	//printf("%s\n", bin_path);
	return(bin_path);
}

int check_bin(char *command)
{
	int return_val;
	char *bin_path;

	if(command[0] == '\0')
		return(0);
	bin_path = get_bin_path(command, "/usr/bin/");
	//printf("%d\n", open(bin_path, O_RDONLY));
	return_val = open(bin_path, O_RDONLY);
    if(return_val > 0)
	{
      	  free(bin_path);
          close(return_val);
          return(1);
	}
    return(0);
}