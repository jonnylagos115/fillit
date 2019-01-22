/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/22 14:21:14 by jlagos           ###   ########.fr       */
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
	tetrim		*head;
	int i;
	int j;
	int x;
	int y;

	head = malloc(sizeof(tetrim));
	head->grid = create_empty_grid();
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
			printf("%c", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
	free_grid(grid);
}

void	read_and_filter(const int fd)
{
	tetrim  teri;
	char 	*line;
	int		i;
	int 	j;
	int 	curr;

	i = 0;
	j = 0;
	curr = 0;
	while (get_next_line(fd, &line) > 0)
	{
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
		if (*line == '\n')
			print_coordinates(teri);
		j++;
		i = 0;
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
			printf("ERROR!\n");
			return (-1);
		}
		read_and_filter(fd);
	}
	return (0);
}
