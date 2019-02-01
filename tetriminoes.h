/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/31 16:23:40 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIMINOES_H
# define TETRIMINOES_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "./gnl/get_next_line.h"

typedef struct Tetriminoes
{
	int					row[4];
	int					col[4];
	char				**pieces;
	struct Tetriminoes	*next;
}Tetrim;
void 		print_coordinates(tetrim teri);
void		read_and_filter(Tetrim *head);
char		**ft_2Dstrnew(size_t size);
Tetrim		*assemble_tetriminoes(Tetrim *tetrim, int fd);

#endif
