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
# define BUFFER_SIZE 20
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "./gnl/get_next_line.h"

typedef struct Tetrominoes
{
	char				**piece;
	char				alphabet;
	int					height;
	int					width;
	int					row[4];
	int					col[4];
	struct Tetrominoes	*next;
}Tetrom;

typedef struct Point
{
	int	x;
	int y;
}t_point;
Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int *tetrom_count, int fd);
Tetrom		*locate_prev_piece(Tetrom *head, char letter);
char		**fillit(Tetrom *tetrom, int num_of_tetrom);
char    	**clear_piece(char **grid, char block);
char		**create_empty_grid(int len);
char		**ft_2dstrcpy(char **dst, char **src);
void    	solve_square(Tetrom *head, char **grid);
void		get_reset_coordinates(Tetrom *tetrom, char *str);
void		reset_all_pieces(Tetrom *start, char **grid, int dim, char end_piece);
void    	print_grid(char **grid, int num);
int			ft_2dstrlen(char **str_arr);
int			shift_coordinates(Tetrom *tetrom, int size);
int			check_available_spot(Tetrom *tetrom, char **grid);
int			store_place_piece(Tetrom *tetrom, char **grid, int dim);
int			undo_prev_piece(Tetrom *head, char prev_letter, char **grid, int dim);

#endif
