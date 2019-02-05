/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/04 19:17:59 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetriminoes.h"

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

void	store_block_coordinates(Tetrim *tetrim, char **piece)
{
	int i;
	int j;
	int curr;

	i = 0;
	j = 0;
	curr = 0;
	while (i < 4)
	{
		while (piece[i][j])
		{
			if (piece[i][j] == '#')
			{
				tetrim->row[curr] = i;
				tetrim->col[curr] = j;
				curr++;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	printLine(Tetrim *t)
{
	int i;

	i = 0;
	while (i < 4)
		printf("%s\n", t->pieces[i++]);
	printf("\n");
}

void		tetrim_lstiter(Tetrim *lst, void (*f)(Tetrim *elem))
{
	while (lst != NULL)
	{
		(*f)(lst);
		lst = lst->next;
	}
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
			store_block_coordinates(tetrim, tetrim->pieces);
			tetrim->next = head;
			head = tetrim;
			if (!(tetrim = (Tetrim *)malloc(sizeof(*tetrim))))
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
		tetrim_lstiter(head, printLine);
	}
	return (0);
}
