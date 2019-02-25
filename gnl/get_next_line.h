/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:57:05 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/17 14:43:39 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 500
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(const int fd, char **line);
char	*fill_saved_bytes(char **saved_bytes, const int fd);
char	*fill_line(char **line, char **saved_bytes);

#endif
