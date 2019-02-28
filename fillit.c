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
	return (grid);
}

char 	**ft_2dstrdup(char **s1, int size)
{
	int 	i;
	int		j;
	char 	**dup;

	i = -1;
	j = -1;
	dup = create_empty_grid(size);
	while (s1[++i])
	{
		while (s1[i][++j])
			dup[i][j] = s1[i][j];
		j = -1;
	}
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
		{
			if ((row[i] + 1) >= size) //Reached the last location the piece can be placed
				return (0);	
		}
		i = -1;
		while (++i < 4)
			row[i] += 1;
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

void	place_piece(int *row, int *col, char **grid, char block)
{
	int i;
	int j;
	int curr;
	
	i = -1;
	j = -1;
	curr = 0;
	while (++i < 4)
		printf("Row: %d, Col: %d\n", row[i], col[i]);
	printf("\n");
	i = -1;
	while (grid[++i])
	{
		while (grid[i][++j])
		{
			if (i == row[curr] && j == col[curr])
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
				grid[i][j] = '.';
				printf("location of last piece, row: %d, col: %d\n", row[curr], col[curr]);
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
	while (++i < 4)
		printf("(b4 reset)Row: %d, Col: %d\n", row[i], col[i]);
	printf("\n");
	i = -1;
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
	i = -1;
	while (++i < 4)
		printf("(after reset)Row: %d, Col: %d\n", row[i], col[i]);
	printf("\n");
	while (is_spot_taken(row, col, grid))
	{
		if (!shift_piece(row, col, size))
		{
			/*i = -1;
			while (++i < 4)
				printf("(in while reset)Row: %d, Col: %d\n", row[i], col[i]);
			printf("\n");*/
			printf("Last available position, increasing dimension size of grid\n");
			//undo piece then try again;)
			return (0);
		}
	}
	return (1);
}

/*int		adjust_board_size(int num)
{
	int i;
	int result;
	int size;
	int temp;
	int sum;

	size = 1;
	temp = num;
	sum = 0;
	i = 1;
	result = 1;
	while (temp--)
		sum += 4;
	num = num * sum;
	while (result <= num)
	{
		i++;
		result = i * i;
	}
	printf("dim: %d\n", i - 1);
	return (i - 1);
}*/


void	fillit(Tetrom *tetrom)
{
	int		dim;
	int		i;
	int		num_of_place_tetrom;
	char 	**grid;
	char	**temp;
	char 	block;

	dim = 4;
	i = 1;
	num_of_place_tetrom = 1;
	grid = create_empty_grid(dim);
	block = 'A';
	while (tetrom)
	{
		if (!reset_coordinates(tetrom->row, tetrom->col, grid, dim))
		{
			if (num_of_place_tetrom == dim || !undo_piece(grid, block - i, dim))
			{
				//dim = adjust_board_size(num_of_place_tetrom);
				dim++;
				temp = ft_2dstrdup(grid, dim);
				free(grid);
				grid = create_empty_grid(dim);
				ft_2dstrcpy(grid, temp);
				free(temp);
			}
		}
		else
		{
			place_piece(tetrom->row, tetrom->col, grid, block);
			tetrom = tetrom->next;
			block++;
			num_of_place_tetrom++;
		}
	}
	//shift_piece(tetrom->row, tetrom->col)
	printf("\n");
}