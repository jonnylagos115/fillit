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

int		shift_piece_left(int *row, int *col, int size)
{

	int i;
	int j;
	int shift_up;

	i = -1;
	j = -1;
	shift_up = 0;
	while (++i < 4)
		if (col[i] - 1 == -1)
			shift_up = 1;
	i = -1;
	while (++i < 4 && !shift_up)
		col[i] -= 1;	//shifts each block by one to the left
	i = -1;
	if (shift_up == 1)
	{
		while (++i < 4)
			if ((row[i] - 1) <= -1) //Reached the last location the piece can be placed
				return (0);
		i = -1;
		while (++i < 4)
			row[i] -= 1;
		while (shift_up)
		{
			while (++j < 4)
				if (col[j] == size - 1)
					shift_up = 0;
			j = -1;
			if (shift_up)
				while (++j < 4)
					col[j] += 1;
			j = -1;
		}
	}
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
	//print_grid(grid, -99);
	while (shift_piece(piece->row, piece->col, size))
	{
		if (!is_spot_taken(piece->row, piece->col, grid))
		{
			place_piece(piece, grid, piece->block);
			return (1);
		}
	}
	i = -1;
	while (++i < 4)
	{
		piece->row[i] = old_row[i];
		piece->col[i] = old_col[i];
	}
	place_piece(piece, grid, piece->block);
	return (0);
}

int		shift_prev_piece_place(char **grid, Tetrom *piece, int size)
{
	if (piece == NULL)
	{
		printf("NULL here\n");
		return (0);
	}
	if (!shift_piece_place(grid, piece, size))
	{
		clear_piece(grid, piece->next->block);
		//print_grid(grid, -2);
		if (shift_piece_place(grid, piece, size))
		{
			//print_grid(grid, -3);
			if (!reset_coordinates(piece->next, grid, size, piece->next->block))
			{
				//print_grid(grid, -4);
				shift_piece_left(piece->row, piece->col, size);
				place_piece(piece, grid, piece->block);
				return (0);
			}
		}
		else
		{
			place_piece(piece->next, grid, piece->next->block);
			if (!shift_prev_piece_place(grid, piece->prev, size))
				return (0);
		}
	}
	return (1);
}

void	reset_all_pieces(char ***grid, int dim, Tetrom *head)
{
	Tetrom *curr_p;

	curr_p = head;
	ft_strdel(*grid);
	*grid = create_empty_grid(dim);
	while (curr_p)
	{
		reset_coordinates(curr_p, *grid, dim, curr_p->block);
		curr_p = curr_p->next;
	}
	print_grid(*grid, 0);
}

void    solve_square(Tetrom *tetrom, Tetrom *head)
{
	Tetrom	*tail;
    char    **grid;
    int		num;
    int		dim;

	tail = tetrom;
	dim = tetrom->dim;
    grid = ft_2dstrdup(tetrom->filled_grid, dim);
	num = 1;
    print_grid(grid, num++);
	while (tetrom)
    {
		while (shift_piece_place(grid, tetrom, dim))
			print_grid(grid, num++);
		if (shift_prev_piece_place(grid, tetrom->prev, dim))
		{
			clear_piece(grid, tetrom->block);
			//print_grid(grid, -1);
			reset_coordinates(tetrom, grid, dim, tetrom->block); //Looks for first available spot then places
			decrease_grid_size(&grid, &dim);
			print_grid(grid, num++);
			if (num > 50)
				abort();
		}
		else
		{
			printf("Next piece\n");
			reset_all_pieces(&grid, dim, head);
			num = 1;
			tetrom = tetrom->prev;
		}
	}
}