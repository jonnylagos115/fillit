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

void    print_grid(char **grid, int num)
{
    int i;

    i = -1;
    printf("%d)\n", num);
    while (grid[++i])
        printf("%s\n", grid[i]);
    printf("\n");
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
	return (dst);
}

Tetrom		*locate_prev_piece(Tetrom *head, char letter)
{
	Tetrom *tetrom;

	tetrom = head;
	if (letter < 'A')
		return (NULL);
	while (tetrom->next)
	{
		if (tetrom->alphabet == letter)
			break ;
		tetrom = tetrom->next;
	}
	return (tetrom);
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
	 	 	return ((int)mid);
    	if (mid * mid > num) 
			hi = mid;
    	else
			lo = mid;
	}
	i = (int)mid;
	if (mid > i + 0.5)
		mid += 1;
	return ((int)mid);
}

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

/*
** resets piece coordinates to the upper most left corner of grid
*/
void	get_reset_coordinates(Tetrom *tetrom, char *str)
{
	int		i;
	int		j;
	int		curr;

	i = -1;
	j = -1;
	curr = 0;
	while (tetrom->piece[++i] && curr != 4)
	{
		while (tetrom->piece[i][++j])
		{
			if (tetrom->piece[i][j] == '#')
			{
				if (!ft_strcmp(str, "row"))
					tetrom->row[curr] = i;
				else if (!ft_strcmp(str, "col"))
					tetrom->col[curr] = j;
				else if (!ft_strcmp(str, "both"))
				{
					tetrom->row[curr] = i;
					tetrom->col[curr] = j;
				}
				curr++;
			}
		}
		j = -1;
	}
}

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

int		check_available_spot(Tetrom *tetrom, char **grid)
{
	int		i;

	i = 0;
	while (grid[tetrom->row[i]][tetrom->col[i]] == '.' && i < 4)
		i++;
	if (i != 4)
		return (1);
	return (0);
}

int		store_place_piece(Tetrom *tetrom, char **grid, int dim)
{
	int		i;
	
	i = -1;
	while (check_available_spot(tetrom, grid))
		if (!shift_coordinates(tetrom, dim))
			return (0);
	while (++i < 4)
		grid[tetrom->row[i]][tetrom->col[i]] = tetrom->alphabet;
	return (1);
}

void	reset_all_pieces(Tetrom *start, char **grid, int dim, char end_piece)
{
	Tetrom	*curr;

	curr = start;
	while (curr && curr->alphabet != end_piece)
	{
		clear_piece(grid, curr->alphabet);
		get_reset_coordinates(curr, "both");
		store_place_piece(curr, grid, dim);
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
	//print_grid(tetrom->next->piece, 69);
	clear_piece(grid, prev_letter);
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
	char	**tmp;
	int		i;
	int		num;

	head = tetrom;
	dim = starting_board_size((double)num_of_tetrom * 4);
	grid = create_empty_grid(dim);
	i = 1;
	num = 1;
	printf("dim: %d\n", dim);
	while (tetrom)
	{
		if (!store_place_piece(tetrom, grid, dim))
		{
			while (!undo_prev_piece(head, tetrom->alphabet - i, grid, dim))
			{
				i++;
				if ((tetrom->alphabet - i) + 1 == 'A')
				{
					tmp = create_empty_grid(++dim);
					ft_2dstrcpy(tmp, grid);
					ft_strdel(grid);
					grid = tmp;
					/*ft_strdel(grid);
					grid = create_empty_grid(++dim);*/
					i = 1;
					reset_all_pieces(head, grid, dim, tetrom->alphabet);
					break ;
				}
			}
			//print_grid(grid, -5);
			get_reset_coordinates(tetrom, "both");
		}
		else
		{
			//print_grid(grid, num++);
			tetrom = tetrom->next;
			i = 1;
		}
	}
	return (grid);
}
