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

int		decrease_grid_size(char ***grid, int *size)
{
	char	**temp;
	int		i;
	int 	j;
	int		len;

	i = -1;
	j = -1;
	len = *size;
	while ((*grid)[len - 1][++j])
		if ((*grid)[len - 1][j] != '.')
			return (0);
	while ((*grid)[++i])
		if ((*grid)[i][len - 1] != '.')
			return (0);
	temp = ft_2dstrdup(*grid, len - 1);
	ft_strdel(*grid);
	*grid = temp;
	(*size)--;
	return (1);
}

int		shift_piece_place(char **grid, Tetrom *piece, int size)
{
	int	i;
	int	old_row[4];
	int	old_col[4];

	i = -1;
	while (++i < 4)
	{
		old_row[i] = piece->row[i];
		old_col[i] = piece->col[i];
	}
	clear_piece(grid, piece->block);
	while (shift_piece(piece->row, piece->col, size))
	{
		if (!is_spot_taken(piece->row, piece->col, grid))
		{
			place_piece(piece->row, piece->col, grid, piece->block);
			decrease_grid_size(&grid, &size);
			return (1);
		}
	}
	i = -1;
	while (++i < 4)
	{
		piece->row[i] = old_row[i];
		piece->col[i] = old_col[i];
	}
	place_piece(piece->row, piece->col, grid, piece->block);
	print_grid(grid, -1);
	return (0);
}

int		shift_prev_piece_place(char **grid, Tetrom *piece, int size)
{
	if (piece == NULL)
		return (0);
	if (!shift_piece_place(grid, piece, size))
	{
		print_grid(grid, -2);
		if (!shift_prev_piece_place(grid, piece->prev, size))
			return (0);
	}
	clear_piece(grid, piece->next->block);
	reset_coordinates(piece->next->row, piece->next->col, grid, size);
	place_piece(piece->next->row, piece->next->col, grid, piece->next->block);
	return (1);
}

void    solve_square(Tetrom *tetrom)
{
    char    **grid;
    int		num;
    int		dim;

    grid = tetrom->filled_grid;
    dim = tetrom->dim;
	num = 1;
    print_grid(grid, num++);
	while (tetrom)
    {
		while (shift_piece_place(grid, tetrom, dim))
			print_grid(grid, num++);
		if (!shift_prev_piece_place(grid, tetrom->prev, dim))
			tetrom = tetrom->prev;
		print_grid(grid, num++);
	}
}