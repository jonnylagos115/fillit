/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_sq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:29:19 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/06 13:29:46 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

char    **clear_prev_piece(char **grid, char block)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (grid[++i])
    {
        while (grid[i][++j])
        {
            if (grid[i][j] == block)
                grid[i][j] = '.';
        }
        j = -1;
    }
    return (grid);
}

int		undo_pieces(char **grid, Tetrom *piece, int size)	//shift last placed piece to the right
{
	if (!shift_piece(piece->row, piece->col, size))
		return (0);
	place_piece(piece->row, piece->col, grid, piece->block);
    clear_prev_piece(grid, piece->block);
	return (1);
}

void    print_grid(char **grid, char letter)
{
    int i;
    int j;

    i = -1;
    j = -1;
    printf("%c)\n", letter);
    while (grid[++i])
        printf("%s\n", grid[i]);
    printf("\n");
}

void    solve_square(Tetrom *tetrom) //figure out how to get pointer to beginning of linked list
{
    int     *row;
    int     *col;
    char    **grid;
    char    letter;
    int     dim;

    row = tetrom->row;
    col = tetrom->col;
    grid = tetrom->filled_grid;
    letter = 'a';
    dim = tetrom->dim;
    print_grid(grid, letter);
    letter++;
    while (shift_piece(row, col, tetrom->dim)) //returns 0 if it reaches last possible place to shift
    {
        grid = clear_prev_piece(grid, tetrom->block);
	    if (!is_spot_taken(row, col, grid)) //returns 0 if spot isn't taken
        {
            place_piece(row, col, grid, tetrom->block);
    		print_grid(grid, letter);
    		letter++;
        }
        while (tetrom && !undo_pieces(grid, tetrom->prev, dim)) //returns 0 if it can't undo the last piece placed on board to a different position
        	tetrom = tetrom->prev;
        if (tetrom)
        {
        	reset_coordinates(row, col, grid, tetrom->dim);
        	grid = clear_prev_piece(grid, tetrom->block);
        	place_piece(row, col, grid, tetrom->block);
        	print_grid(grid, letter);
        	letter++;
		}
		else
			break ;
	}
}
