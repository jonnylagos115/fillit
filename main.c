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
		Tetrom start;
		Tetrom *head;

		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		head = assemble_tetrominoes(&start, fd);
		fillit(head);
	}
	return (0);
}
