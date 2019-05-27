/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:33:59 by jlagos            #+#    #+#             */
/*   Updated: 2019/05/06 13:34:00 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

void    print_grid(char **grid)
{
    int i;

    i = -1;
    while (grid[++i])
	{
        ft_putstr(grid[i]);
		ft_putchar('\n');
	}
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

char	**create_empty_grid(int len)
{
	char **grid;
	int i;

	grid = ft_2dstrnew(len);
	i = -1;
	while (++i < len)
		ft_memset(grid[i], '.', len);
	return (grid);
}

int		check_available_spot(Tetrom *tetrom, char **grid)
{
	int		i;

	i = 0;
	if (ft_2dstrlen(grid) >= tetrom->height)
	{
		while (i < 4 && grid[tetrom->row[i]][tetrom->col[i]] == '.')
			i++;
		if (i != 4)
			return (1);
	}
	return (0);
}