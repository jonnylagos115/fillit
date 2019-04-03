/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/26 11:26:16 by jlagos           ###   ########.fr       */
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
	int					dim;
	char				block;
	char				**pieces;
	char				**filled_grid;
	struct Tetrominoes	*next;
	struct Tetrominoes	*prev;
}Tetrom;
void 		printLine(Tetrom *t);
void    	print_grid(char **grid, int num);
void		tetrom_lstiter(Tetrom *lst, void (*f)(Tetrom *elem));
void		place_piece(int *row, int *col, char **grid, char block);
void    	solve_square(Tetrom *tetrom);
int			reset_coordinates(int *row, int *col, char **grid, int size);
int			shift_piece(int *row, int *col, int size);
int			is_spot_taken(int *row, int *col, char **grid);
int			check_invalid_tetrom(int *row, int *col);
int			store_block_coordinates(Tetrom *tetrom, char **piece);
Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int fd, int *num_of_pieces);
Tetrom		*fillit(Tetrom *tetrom, int num_of_tetrom);
char		**create_empty_grid(int len);
char 		**ft_2dstrdup(char **s1, int size);
char		**ft_2dstrcpy(char **dst, char **src);

#endif
