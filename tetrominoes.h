/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/13 17:18:52 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETROMINOES_H
# define TETROMINOES_H
# define ABS(n) (((n) < 0) ? -(n) : (n)) /* Absolute function */
# define TOL 0.001 /* Tolerance */
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "./gnl/get_next_line.h"

typedef struct Tetrominoes
{
	int					row[4];
	int					col[4];
	char				**pieces;
	struct Tetrominoes	*next;
}Tetrom;
void 		printLine(Tetrom *t);
void		tetrom_lstiter(Tetrom *lst, void (*f)(Tetrom *elem));
int			check_invalid_tetrom(int *row, int *col);
int			store_block_coordinates(Tetrom *tetrom, char **piece);
Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int fd, int *num_of_pieces);
void		fillit(Tetrom *tetrom, int num_of_tetrom);

#endif
