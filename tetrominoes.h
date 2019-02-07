/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/06 16:37:10 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETROMINOES_H
# define TETROMINOES_H
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
int			check_invalid_tetrom(int row[4], int col[4]);
int			store_block_coordinates(Tetrom *tetrom, char **piece);
char		**ft_2Dstrnew(size_t size);
Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int fd);

#endif
