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
		char	**grid;
		//int i;
		//Tetrom *last_placed_piece;

		fd = open(ag[1], O_RDONLY);
		num_of_pieces = 0;
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		if (!(head = assemble_tetrominoes(&start, &num_of_pieces, fd)))
		{
			printf("error\n");
			return (0);
		}
		grid = fillit(head, num_of_pieces);
		//last_placed_piece = fillit(head, num_of_pieces);
		solve_square(head, grid);
	}
	return (0);
}
