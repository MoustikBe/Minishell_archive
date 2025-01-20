#ifndef MINI
# define MINI
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
// -- Strucutre de la liste chainer -- //
typedef struct s_list
{
    char                    *content;
    struct s_list   *next;
}                                       t_list;
// - Fonction - //
t_list  *mk_clean(t_list **lst);
void    add_to_lst(t_list **lst, char *buff, int readed, int count);
void    count_for_line(t_list *lst, char **line);
void    read_store(int fd, t_list **lst);
void    free_all(t_list *lst);
void    reset_lst(t_list **lst, int count, int count_2, t_list *clean);
void    define_line(t_list *lst, char **line);
char    *get_next_line(int fd);
char    *so_free(t_list **lst);
int     found_a_count(t_list *lst, const char *str, int flag, int count);
char	**ft_split(char const *s, char c);
#endif