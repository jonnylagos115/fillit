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

char    **clear_piece(char **grid, char block)
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

void    print_grid(char **grid, int num)
{
    int i;

    i = -1;
    printf("%d)\n", num);
    while (grid[++i])
        printf("%s\n", grid[i]);
    printf("\n");
}

int		shift_prev_pieces(char **grid, Tetrom *piece, int size)	//shift last placed piece to the right
{
	int	i;

	i = 0;
	while (piece && (i = shift_piece(piece->row, piece->col, size)))
	{
		clear_piece(grid, piece->block);
		if (!is_spot_taken(piece->row, piece->col, grid))
		{
			place_piece(piece->row, piece->col, grid, piece->block);
			break ;
		}
		else
		{
			clear_piece(grid, piece->next->block);
			if (!is_spot_taken(piece->row, piece->col, grid))
			{
				place_piece(piece->row, piece->col, grid, piece->block);
				if (reset_coordinates(piece->next->row, piece->next->col, grid, size))
					break ;
			}
			place_piece(piece->next->row, piece->next->col, grid, piece->next->block);
		}
	}
	if (!i || !piece)
	{
		if (piece)
		{
			reset_coordinates(piece->next->row, piece->next->col, grid, size);
			place_piece(piece->next->row, piece->next->col, grid, piece->next->block);
		}
		return (0);
	}
	return (1);
}

int		decrease_grid_size(char ***grid, int size)
{
	char	**temp;
	int		i;
	int 	j;

	i = -1;
	j = -1;
	while ((*grid)[size - 1][++j])
		if ((*grid)[size - 1][j] != '.')
			return (0);
	while ((*grid)[++i])
		if ((*grid)[i][size - 1] != '.')
			return (0);
	temp = ft_2dstrdup(*grid, size - 1);
	ft_strdel(*grid);
	*grid = temp;
	return (1);
}

void    solve_square(Tetrom *tetrom)
{
	Tetrom	*restart;
    char    **grid;
    int		num;
    int		dim;

	restart = tetrom;
    grid = tetrom->filled_grid;
    dim = tetrom->dim;
	num = 1;
    print_grid(grid, num++);
	while (tetrom)
    {
        while (shift_piece(tetrom->row, tetrom->col, dim)) //returns 0 if it reaches last possible place to shift
        {
            clear_piece(grid, tetrom->block);
	        if (!is_spot_taken(tetrom->row, tetrom->col, grid)) //returns 0 if spot isn't taken
            {
                place_piece(tetrom->row, tetrom->col, grid, tetrom->block);
				if (decrease_grid_size(&grid, dim))	//if the last column & row is empty, decrease grid size, It should minimize the search for solution
				{
					tetrom = restart; //fix this
					dim--;
					num = 1;
				}
    		    print_grid(grid, num);
    		    num++;
            }
        }
        while (tetrom && !shift_prev_pieces(grid, tetrom->prev, dim)) //returns 0 if it can't undo the last piece placed on board to a different position
			tetrom = tetrom->prev;
        if (tetrom)
        {
        	reset_coordinates(tetrom->row, tetrom->col, grid, dim);
        	clear_piece(grid, tetrom->block);
        	place_piece(tetrom->row, tetrom->col, grid, tetrom->block);
			if (decrease_grid_size(&grid, dim))
			{
				tetrom = restart; //fix this
				dim--;
				num = 1;
			}
        	print_grid(grid, num);
        	num++;
        }
	}
}