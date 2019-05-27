/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:46:29 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/26 11:00:04 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		shift_coordinates(Tetrom *tetrom, int size)
{
	int i;
	int	j;
	int	shift_down;

	i = -1;
	j = -1;
	shift_down = 0;
	while (++i < 4)
		if (tetrom->col[i] == size - 1)
			shift_down = 1;
	while (shift_down && ++j < 4)
		if ((tetrom->row[j] + 1) >= size)
			return (0);
	i = -1;
	j = -1;
	if (shift_down)
	{
		while (++j < 4)
			tetrom->row[j] += 1;
		get_reset_coordinates(tetrom, "col");
	}
	else
		while (++i < 4)
			tetrom->col[i] += 1;
	return (1);
}

int		store_place_piece(Tetrom *tetrom, char **grid, int dim)
{
	int		i;

	i = -1;
	while (check_available_spot(tetrom, grid))
		if (!shift_coordinates(tetrom, dim))
			return (0);
	if (ft_2dstrlen(grid) >= tetrom->height)
	{
		while (++i < 4)
			grid[tetrom->row[i]][tetrom->col[i]] = tetrom->alphabet;
	}
	else
		return (0);
	return (1);
}

void		reset_piece_coordinates(Tetrom *head)
{
	Tetrom	*curr;

	curr = head;
	while (curr)
	{
		get_reset_coordinates(curr, "both");
		curr = curr->next;
	}
}

void		clear_all_pieces(Tetrom *start, char **grid)
{
	Tetrom	*curr;

	curr = start;
	while (curr)
	{
		clear_piece(grid, curr->alphabet);
		curr = curr->next;
	}
}

/*
** Undoes previous placed piece, shifts over to the next available spot
** Function will return 0 ONLY if the piece cannot be shift any further
** Before it returns 0, it will reset piece back to the most upper left it can be 
** 
*/
int		undo_prev_piece(Tetrom *head, char prev_letter, char **grid, int dim)
{
	Tetrom	*tetrom;
	int		i;

	i = -1;
	//printf("Undoing: %c\nTo place: %c\nThe piece to place:\n", prev_letter, prev_letter + 1);
	if (!(tetrom = locate_prev_piece(head, prev_letter)))
		return (2);
	clear_all_pieces(tetrom, grid);
	if (!shift_coordinates(tetrom, dim) || !store_place_piece(tetrom, grid, dim))
	{
		get_reset_coordinates(tetrom, "both");
		store_place_piece(tetrom, grid, dim);
		return (0);
	}
	return (1);
}

char	**fillit(Tetrom *tetrom, int num_of_tetrom)
{
	Tetrom	*head;
	int		dim;
	char 	**grid;

	head = tetrom;
	dim = starting_board_size((double)num_of_tetrom * 4);
	while (tetrom->height > dim)
		dim++;
	grid = create_empty_grid(dim);
	while (tetrom)
	{
		if (!store_place_piece(tetrom, grid, dim))
		{
			while (!undo_prev_piece(head, tetrom->alphabet - 1, grid, dim))
			{
				tetrom = locate_prev_piece(head, tetrom->alphabet - 1);
				if (tetrom->alphabet == 'A')
				{
					ft_strdel(grid);
					grid = create_empty_grid(++dim);
					reset_piece_coordinates(head);
					break ;
				}
			}
			get_reset_coordinates(tetrom, "both");
		}
		else
		{
			tetrom = tetrom->next;
			if (tetrom)
				get_reset_coordinates(tetrom, "both");
		}
	}
	print_grid(grid);
	return (grid);
}
