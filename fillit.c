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

char	**create_empty_grid(int len)
{
	char **grid;
	int i;

	grid = ft_2dstrnew(len);
	i = -1;
	while (++i < len)
		ft_memset(grid[i], '.', len); //fills each row with '.'
	grid[i] = NULL;
	return (grid);
}

char 	**ft_2dstrdup(char **s1, int size)
{
	int 	i;
	int		j;
	char 	**dup;

	i = -1;
	j = -1;
	if (!(dup = ft_2dstrnew(size)))
		return (NULL);
	while (++i < size)
	{
		while (s1[i][++j])
			dup[i][j] = s1[i][j];
		dup[i][j] = '\0';
		j = -1;
	}
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
	}
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
	while (grid[++i])
	{
		while (grid[i][++j])
		{
			if (grid[i][j] != '.')
			{
				while (grid[++curr])
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
	int curr;
	int shift_down;

	i = -1;
	j = -1;
	curr = 0;
	shift_down = 0;
	while (++i < size)
		if (col[i] == 3)
			shift_down = 1;
	i = -1;
	while (++i < size && !shift_down)
		col[i] += 1;
	i = -1;
	if (shift_down == 1)
	{
		while (++i < size)
		{
			if ((row[i] + 1) >= 4) //Reached the last location the piece can be placed
				return (0);	
			row[i] += 1;
		}
		while (shift_down)
		{
			while (++j < size)
			{
				if (col[j] == 0)
					shift_down = 0;
			}
			j = -1;
			if (shift_down)
				while (++j < size)
					col[j] -= 1;
			j = -1;
		}
	}
	return (1);
}

int		reset_coordinates(int *row, int *col, char **grid, int size)
{
	int			i;
	int 		reset;
	int 		no_reset;
	int 		skip;

	i = -1;
	reset = 0;
	no_reset = 0;
	skip = 0;
	i = -1;
	if (row[0] != 0) //reset coordinates if first block char. is not on row 0
	{
		reset = row[0];	//Subtract each row number with the first row number
		while (grid[++i])	//Resets coordinates to shift to the most upperbound of the grid it can be
		{
			row[i] -= reset;
			if (col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
	while (grid[++i])
		if (col[i] == 0) //no reset if any columns is at column 0
			skip = 1;
	i = -1;
	while (!no_reset && !skip)	//if no block char. is on column 0, shift to the left by one
	{
		while (grid[++i])
		{
			col[i] -= 1;
			if (col[i] == 0)
				no_reset = 1;
		}
		i = -1;
	}
	while (is_spot_taken(row, col, grid))
	{
		if (!(shift_piece(row, col, size)))
		{
			printf("Last available position, increasing dimension size of grid\n");
			return (0);
		}
	}
	return (1);
}

void	place_piece(Tetrom *tetrom, char **grid, char block)
{
	int i;
	int j;
	int curr;
	
	i = -1;
	j = -1;
	curr = 0;
	while (grid[++i])
		printf("Row: %d, Col: %d\n", tetrom->row[i], tetrom->col[i]);
	printf("\n");
	i = -1;
	while (grid[++i])
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

void	fillit(Tetrom *tetrom)
{
	int		dim;
	char 	**grid;
	char	**temp;
	char 	block;

	dim = 4;
	grid = create_empty_grid(dim);
	block = 'A';
	while (tetrom)
	{
		if (!reset_coordinates(tetrom->row, tetrom->col, grid, dim))
		{
			temp = ft_2dstrdup(grid, ++dim);
			free(grid);
			grid = create_empty_grid(dim);
			ft_2dstrcpy(grid, temp);
		}
		else
		{
			place_piece(tetrom, grid, block);
			tetrom = tetrom->next;
			block++;
		}
	}
	//shift_piece(tetrom->row, tetrom->col)
	/*
		Remember to change the int array in the structures to a dynamic one
		int *row = malloc(dim);
		int *col = malloc(dim);
	*/
	printf("\n");
}