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

/*
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

int		shift_piece_place(char **grid, Tetrom *tetrom, int size)
{
	clear_piece(grid, tetrom->alphabet);
	//print_grid(grid, -99);
	if (!shift_coordinates(tetrom, size) || !store_place_piece(tetrom, grid, size))
	{
		get_reset_coordinates(tetrom, "both");
		store_place_piece(tetrom, grid, size);
		return (0);
	}
	return (1);
}*/

/*
** Function will return 1 if prev piece was shift, returns 2 if no prev piece could be shifted
** Resets pieces back to orignal spots if it returns 2 on grid
**
*/
/*int		shift_prev_piece_place(Tetrom *tetrom, char prev_letter, char **grid, int size)
{
	int		ret;
	int		i;

	ret = 0;
	i = 1;
	tetrom = locate_prev_piece(tetrom, prev_letter);
	while (!shift_piece_place(grid, tetrom, size))
	{
		shift_piece_place(grid, tetrom, size);
	}
	if (ret == 2)
		reset_all_pieces(head, grid, size, tetrom->alphabet);
	print_grid(grid, -2);
	return (ret);
}*/

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

int		compare_with_best(char **curr, char **best)
{
	
}

char	**swap_pieces(Tetrom *p_swap, Tetrom *curr, char **grid, int dim)
{
	char	**tmp;

	printf("%c:\n", p_swap->alphabet);
	tmp = create_empty_grid(dim);
	ft_2dstrcpy(tmp, grid);
	clear_piece(tmp, p_swap->alphabet);
	clear_piece(tmp, curr->alphabet);
	get_reset_coordinates(p_swap, "both");
	get_reset_coordinates(curr, "both");
	if (!store_place_piece(p_swap, tmp, dim) || !store_place_piece(curr, tmp, dim))
		printf("could not swap :(\n");
	return (tmp);
}

void    solve_square(Tetrom *head, char **grid)
{
	Tetrom	*tetrom;
	Tetrom	*p_swap;
	char	**ret;
	char	**best_solution; 
    int		num;
    int		dim;

	tetrom = head;
	p_swap = head;
	dim = ft_2dstrlen(grid);
	best_solution = ft_2dstrdup(grid, dim);
	num = 1;
	print_grid(best_solution, 0);
	while (tetrom)
    {
		printf("Swapping piece: %c to all pieces\n", tetrom->alphabet);
		while (p_swap)
		{
			if (p_swap->alphabet != tetrom->alphabet)
			{
				ret = swap_pieces(p_swap, tetrom, grid, dim);
				print_grid(ret, num++);
				ft_strdel(ret);
			}
			p_swap = p_swap->next;
		}
		/*while (!shift_piece_place(grid, tetrom, dim))
		{
			clear_piece(grid, tetrom->alphabet);
			shift_prev_piece_place(tetrom->alphabet - 1, grid);
			get_reset_coordinates(tetrom, "both");
			printf("inside shift_piece_place\n");
			print_grid(grid, num++);
			if (num > 20)
				abort();
		}
		get_reset_coordinates(tetrom, "both");
		store_place_piece(tetrom, grid, dim);
		i++;*/
		printf("Next piece\n");
		tetrom = tetrom->next;
		p_swap = head;
	}
}