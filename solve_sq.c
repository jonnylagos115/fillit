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

int		undo_piece(char **grid, char block, int size)	//shift last placed piece to the right
{
	int row[4];
	int col[4];
	int i;
	int j;
	int curr;

	i = -1;
	j = -1;
	curr = 0;
	while (grid[++i])
	{
		while (grid[i][++j])
		{
			if (grid[i][j] == block)
			{
				row[curr] = i;
				col[curr] = j;
				grid[i][j] = '.'; //clears space
				//printf("location of last piece, row: %d, col: %d\n", row[curr], col[curr]);
				curr++;
			}
		}
		j = -1;
	}
	if (!shift_piece(row, col, size))
		return (0);
	place_piece(row, col, grid, block);
	return (1);
}

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

void    solve_square(Tetrom *tetrom)
{
    int     *row;
    int     *col;
    char    **grid;
    char    letter;

    row = tetrom->row;
    col = tetrom->col;
    grid = tetrom->filled_grid;
    letter = 'a';
    print_grid(grid, letter);
    letter++;
    while (tetrom->block != 'A')
	{
        if (!shift_piece(row, col, tetrom->dim))
        {
            if (!undo_piece(grid, tetrom->block - 1, tetrom->dim))
            {
                tetrom->block -= 1;

            }
            else
            {
                reset_coordinates(row, col, grid, tetrom->dim);
                grid = clear_prev_piece(grid, tetrom->block);
                place_piece(row, col, grid, tetrom->block);
                print_grid(grid, letter);
                letter++;
            }
        }
        else
        {
            grid = clear_prev_piece(grid, tetrom->block);
		    if (!is_spot_taken(row, col, grid))
            {
                place_piece(row, col, grid, tetrom->block);
                print_grid(grid, letter);
                letter++;
            }
        }
	}
}
