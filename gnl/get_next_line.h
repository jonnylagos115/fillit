/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:57:05 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/27 17:16:11 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 5

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	char	*saved_bytes;
	int		fd[1024];
	int		index;
}				t_list;
int				get_next_line(const int fd, char **line);

#endif
