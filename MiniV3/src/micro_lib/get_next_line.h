/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaac-c <misaac-c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:19:41 by misaac-c          #+#    #+#             */
/*   Updated: 2024/02/18 18:25:57 by misaac-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
// --- Declaration des bibliotheque --- // 
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
// ------------------------------------ // 
// -- PARTIE BUFFER -- //
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
// ------------------- //
// -- Strucutre de la liste chainer -- //
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
// ----------------------------------- //
// - Fonction - //
t_list	*mk_clean(t_list **lst);
void	add_to_lst(t_list **lst, char *buff, int readed, int count);
void	count_for_line(t_list *lst, char **line);
void	read_store(int fd, t_list **lst);
void	free_all(t_list *lst);
void	reset_lst(t_list **lst, int count, int count_2, t_list *clean);
void	define_line(t_list *lst, char **line);
char	*get_next_line(int fd);
char	*so_free(t_list **lst);
int		found_a_count(t_list *lst, const char *str, int flag, int count);
// ------------ //
#endif
