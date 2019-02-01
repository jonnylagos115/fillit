/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/31 16:23:38 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetriminoes.h"

/*int		check_block_coordin(tetrim teri)
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

}*/

char	**ft_2Dstrnew(size_t size)
{
	size_t		i;
	char		**arr_str;

	i = 0;
	if (!(arr_str = (char **)malloc(size * sizeof(char *))))
		return (NULL);
	while (i < 4)
		if (!(arr_str[i++] = ft_strnew(4)))
			return (NULL);
	return (arr_str);
}

Tetrim		*assemble_tetriminoes(Tetrim *tetrim, int fd)
{
	int				i;
	char			*line;
	Tetrim			*head;

	i = 0;
	head = NULL;
	if (!(tetrim->pieces = ft_2Dstrnew(4)))
		printf("NULL my dude\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			ft_strncpy(tetrim->pieces[i], line, 4);
		else
		{
			tetrim->next = head;
			head = tetrim;
			if (!(node = (Tetrim *)malloc(sizeof(*tetrim))))
				printf("NULL creating a new structure failed\n");
			tetrim->pieces = ft_2Dstrnew(4);
			i = -1;
		}
		i++;
	}
	tetrim->next = head;
	head = tetrim;
	return (head);
}

void	filter_and_print(Tetrim *head) //Will check for invalid descriptions, then prints if all good
{
	int		i;
	int 	j;
	int 	curr;
	int		track_row;
	char 	*
	i = 0;
	j = 0;
	curr = 0;
	track_row = 0;
	while (head)
	{
		
	}

}

int		main(int ac, char **ag)
{
	if (ac == 2)
	{
		int fd;
		Tetrim start;
		Tetrim *head;

		fd = open(ag[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		head = assemble_tetriminoes(&start, fd);
		read_and_filter(head);
	}
	return (0);
}
