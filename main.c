/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:17:13 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/13 17:27:34 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		main(int ac, char **ag)
{
	if (ac == 2)
	{
		int fd;
		int	num_of_pieces;
		Tetrom start;
		Tetrom *head;
		Tetrom *grid;

		fd = open(ag[1], O_RDONLY);
		num_of_pieces = 1;
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		head = assemble_tetrominoes(&start, fd, &num_of_pieces);
		grid = fillit(head, num_of_pieces);
		solve_square(grid);
	}
	return (0);
}
