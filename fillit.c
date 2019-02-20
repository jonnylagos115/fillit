/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:46:29 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/13 17:42:19 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

char	**create_empty_grid()
{
	char **grid;
	int i;

	grid = ft_2dstrnew(4);
	i = -1;
	while (++i < 4)
		ft_memset(grid[i], '.', 4); //fills each row with '.'
	return (grid);
}

void	reset_coordinates(int *row, int *col)
{
	int	i;
	int reset;
	int no_reset;
	int skip;

	i = -1;
	reset = 0;
	no_reset = 0;
	skip = 0;
	if (row[0] != 0) //reset coordinates if first block char. is not on row 0
	{
		reset = row[0];	//Subtract each row number with the first row number
		while (++i < 4)	//Resets coordinates to shift to the most upperbound of the grid it can be
		{
			row[i] -= reset;
			if (col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
	while (++i < 4)
		if (col[i] == 0) //no reset if any columns is at column 0
			skip = 1;
	i = -1;
	while (!no_reset && !skip)	//if no block char. is on column 0, shift to the left by one
	{
		while (++i < 4)
		{
			col[i] -= 1;
			if (col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
}

void	place_piece(Tetrom *tetrom, char **grid, char block)
{
	int i;
	int j;
	int curr;
	
	i = -1;
	j = -1;
	curr = 0;
	while (++i < 4)
		printf("Row: %d, Col: %d\n", tetrom->row[i], tetrom->col[i]);
	printf("\n");
	i = -1;
	while (++i < 4)
	{
		while (grid[i][++j])
		{
			if (i == tetrom->row[curr] && j == tetrom->col[curr])
			{
				grid[i][j] = block;
				curr++;
			}
		}
		printf("%s\n", grid[i]);
		j = -1;
	}
	printf("\n");
}

int		shift_piece(int *row, int *col)
{
	int i;
	int j;
	int curr;
	int shift_down;

	i = -1;
	j = -1;
	curr = 0;
	shift_down = 0;
	while (++i < 4)
		if (col[i] == 3)
			shift_down = 1;
	i = -1;
	while (++i < 4 && !shift_down)
		col[i] += 1;
	i = -1;
	if (shift_down == 1)
	{
		while (++i < 4)
		{
			if ((row[i] + 1) >= 4) //Reached the last location the piece can be placed
				return (0);	
			row[i] += 1;
		}
		while (shift_down)
		{
			while (++j < 4)
			{
				if (col[j] == 0)
					shift_down = 0;
			}
			j = -1;
			if (shift_down)
				while (++j < 4)
					col[j] -= 1;
			j = -1;
		}
	}
	return (1);
}

void	fillit(Tetrom *tetrom)
{
	char **grid;
	char block;

	grid = create_empty_grid();
	block = 'A';
	reset_coordinates(tetrom->row, tetrom->col);
	do
	{
		place_piece(tetrom, grid, block);
		free(grid);
		grid = create_empty_grid();
	}while (shift_piece(tetrom->row, tetrom->col));
	printf("\n");
}