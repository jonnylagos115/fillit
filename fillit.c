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

char	**create_empty_grid(int len)
{
	char **grid;
	int i;

	grid = ft_2dstrnew(len);
	i = -1;
	while (++i < len)
		ft_memset(grid[i], '.', len); //fills each row with '.'
	return (grid);
}

char 	**ft_2dstrdup(char **s1, int size)
{
	char 	**dup;
	int 	i;

	dup = ft_2dstrnew(size);
	i = -1;
	while (++i < size)
		ft_strncpy(dup[i], s1[i], size);
	dup[i] = NULL;
	return (dup);
}

char	**ft_2dstrcpy(char **dst, char **src)
{
	size_t i;
	size_t j;

	i = -1;
	j = -1;
	while (src[++i])
	{
		while (src[i][++j])
			dst[i][j] = src[i][j];
		j = -1;
	}
	dst[i] = NULL;
	return (dst);
}

int		is_spot_taken(int *row, int *col, char **grid)
{
	int	i;
	int j;
	int curr;

	i = -1;
	j = -1;
	curr = -1;
	/*	while (++i < 4)
		printf("Row: %d, Col: %d\n", row[i], col[i]);
	printf("\n");*/
	while (grid[++i])
	{
		while (grid[i][++j])
		{
			if (grid[i][j] != '.')
			{
				while (++curr < 4)
				{
					if (row[curr] == i && col[curr] == j)
						return (1);
				}
				curr = -1;
			}
		}
		j = -1;
	}
	return (0);
}

int		shift_piece(int *row, int *col, int size)
{
	int i;
	int j;
	int shift_down;

	i = -1;
	j = -1;
	shift_down = 0;
	while (++i < 4)
		if (col[i] == size - 1)
			shift_down = 1;
	i = -1;
	while (++i < 4 && !shift_down)
		col[i] += 1;
	i = -1;
	if (shift_down == 1)
	{
		while (++i < 4)
			if ((row[i] + 1) >= size) //Reached the last location the piece can be placed
				return (0);	
		i = -1;
		while (++i < 4)
			row[i] += 1;
		while (shift_down)
		{
			while (++j < 4)
				if (col[j] == 0)
					shift_down = 0;
			j = -1;
			if (shift_down)
				while (++j < 4)
					col[j] -= 1;
			j = -1;
		}
	}
	return (1);
}

void	place_piece(Tetrom *piece, char **grid, char block)
{
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
			if (i == piece->row[curr] && j == piece->col[curr] && curr < 4)
			{
				grid[i][j] = block;
				curr++;
			}
		}
		j = -1;
	}
}

int		reset_coordinates(Tetrom *piece, char **grid, int size, char block)
{
	int			i;
	int 		reset;
	int 		no_reset;
	int 		skip;
	int			old_row[4];
	int			old_col[4];

	i = -1;
	reset = 0;
	no_reset = 0;
	skip = 0;
	while (++i < 4)
	{
		old_row[i] = piece->row[i];
		old_col[i] = piece->col[i];
	}
	i = -1;
	if (piece->row[0] != 0) //reset coordinates if first block char. is not on row 0
	{
		reset = piece->row[0];	//Subtract each row number with the first row number
		while (++i < 4)	//Resets coordinates to shift to the most upperbound of the grid it can be
		{
			piece->row[i] -= reset;
			if (piece->col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
	while (++i < 4)
		if (piece->col[i] == 0) //no reset if any columns is at column 0
			skip = 1;
	i = -1;
	while (!no_reset && !skip)	//if no block char. is on column 0, shift to the left by one
	{
		while (++i < 4)
		{
			piece->col[i] -= 1;
			if (piece->col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
	if (piece->row[3] >= size || piece->col[3] >= size) //if first piece is straight vertical or horizontal and the last block wasn't placed
	{
		i = -1;
		while (++i < 4)
		{
			piece->row[i] = old_row[i];
			piece->col[i] = old_col[i];
		}
		piece->block = block;
		place_piece(piece, grid, piece->block);
		return (0);
	}
	while (is_spot_taken(piece->row, piece->col, grid))
	{
		if (!shift_piece(piece->row, piece->col, size))
		{
			i = -1;
			while (++i < 4)
			{
				piece->row[i] = old_row[i];
				piece->col[i] = old_col[i];
			}
			piece->block = block;
			place_piece(piece, grid, piece->block);
			return (0);
		}
	}
	piece->block = block;
	place_piece(piece, grid, piece->block);
	return (1);
}

int		starting_board_size(double num)
{
	double 	lo;
	double 	hi;
	double 	mid;
	int		i;

	lo = 0;
	hi = num;
	i = -1;
	while (++i < 1000)
  	{
		mid = (lo+hi)/2;
    	if (mid * mid == num)
		{
			printf("mid: %f\n", mid);
	 	 	return ((int)mid);
		}
    	if (mid * mid > num) 
			hi = mid;
    	else
			lo = mid;
	}
	i = (int)mid;
	if (mid > i + 0.5)
		mid += 1;
	printf("mid: %f\n", mid);
	return ((int)mid);
}

Tetrom	*fillit(Tetrom *tetrom, int num_of_tetrom)
{
	Tetrom	*head;
	int		dim;
	int		i;
	char 	**grid;
	char 	block;

	head = tetrom;
	printf("num of tetrom: %d\n", num_of_tetrom);
	dim = starting_board_size((double)num_of_tetrom * 4);
	printf("dim: %d\n", dim);
	i = 1;
	grid = create_empty_grid(dim);
	block = 'A';
	while (tetrom)
	{
		if (!reset_coordinates(tetrom, grid, dim, block))
		{
			dim++;
			free(grid);
			grid = create_empty_grid(dim);
			tetrom = head;
			block = 'A';
		}
		else
		{
			if (tetrom->next == NULL)
				break ;
			tetrom = tetrom->next;
			block++;
		}
	}
	tetrom->filled_grid = grid;
	tetrom->dim = dim;
	return (tetrom);
}
