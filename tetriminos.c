/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/25 10:41:24 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetriminoes.h"

void		free_grid(char **grid)
{
	int		i;

	i = 0;
	while(i < 4)
		ft_strdel(&grid[i++]);
	ft_strdel(grid);
}

char		**create_empty_grid()
{
	int i;
	int j;
	char **grid;

	grid = (char **)malloc(4 * sizeof(char *));
	i = 4;
	j = 0;
	while (i--)
		grid[i] = ft_strnew(4);
	i = 0;
	while (i < 4)
	{
		while (j < 4)
			grid[i][j++] = '.';
		j = 0;
		i++;
	}
	return (grid);
}

void 	print_coordinates(tetrim teri)
{
	char 	**grid;
	int 	i;
	int 	j;
	int 	x;
	int 	y;

	grid = create_empty_grid();
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			if (i == teri.row[x] && j == teri.col[y])
			{
				grid[i][j] = '#';
				x++;
				y++;
			}
			ft_putchar(grid[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
		j = 0;
	}
	ft_putchar('\n');
	free_grid(grid);
}

int		check_block_coordin(tetrim teri)
{
	int row;
	int col;

	row = 0;
	col = 0;
	while (row < 4)
	{
		while (col < 4)
		{
			teri.col[col] 

}

void	read_and_filter(const int fd)
{
	tetrim  teri;
	char 	*line;
	int		i;
	int 	j;
	int 	curr;
	int		track_row;

	i = 0;
	j = 0;
	curr = 0;
	track_row = 0;
	while (get_next_line(fd, &line) > 0 && track_row < 4)
	{
		if (ft_strlen(line) != 4)
		{
			ft_putstr("~Invalid~\n");
			exit(1);
		}
		while (line[i] && *line != '\n') 
		{
			if (line[i] == '#')	//storing coordinates of block char.
			{
				teri.col[curr] = i;
				teri.row[curr] = j;
				curr++;
			}
			i++;
		}
		if (*line)
		{
			j++;
			i = 0;
		}
		if (j == 4)
		{
			if (check_block_coordin(teri) == 1)
				print_coordinates(teri);
			curr = 0;
			j = 0;
		}
		track_row++;
	}
}

int		main(int ac, char **ag)
{
	if (ac == 2)
	{
		int fd;

		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		read_and_filter(fd);
	}
	return (0);
}
