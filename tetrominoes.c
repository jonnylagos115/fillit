/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/06 19:20:11 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		check_invalid_tetrom(int row[4], int col[4])
{
	int i;
	int j;
	int touches;
	int len;

	i = -1;
	j = -1;
	touches = 0;
	len = 3;
	while (++i < 3) //record the number of touches each block has from one another
	{
	/*	if (row[i] == row[0]) //checks right only (it is at left end)
			if ((col[j + 1] - col[j]) == 1)
				touches++;
		if (col[i] == col[0]) //checks below only (it is at upper end)
			if ((row[j + 1] - row[j]) == 1) 
				touches++;
		printf("touches after yea: %d\n", touches);*/
		while (++j < len)
		{
			if (row[i] == row[j + 1])
			{
				if ((col[j + 1] - col[i]) == 1) //checks from the right of current block
					touches++;
				if (i)
					if ((col[i] - col[i - 1]) == 1) //checks from the left of current block
						touches++;
			}
			printf("touches after row: %d\n", touches);
			if (col[i] == col[j + 1])
			{
				if ((row[j + 1] - row[i]) == 1) //checks below of current block
					touches++;
				if (i)
					if ((row[i] - row[i - 1]) == 1) //checks above of current block
						touches++;
			}
		}
		printf("touches: %d\n", touches);
/*		if (row[i] == row[3]) //checks left (it is at right end)
			if ((col[j] - col[j - 1]) == -1)
				touches++;
		if (col[i] == col[3]) //checks above (it is at bottom end)
			if ((row[j] - row[j - 1]) == -1)
				touches++;*/
		j = i;
		len++;
	}
	printf("final touches: %d\n", touches);
	if (touches < 6) //A valid tetrominoe will have at minimum 6 connections total among the blocks
		return (0);
	return (1);
}

int		store_block_coordinates(Tetrom *tetrom, char **piece)
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
				if (curr > 3)
					return (0);
				tetrom->row[curr] = i;
				tetrom->col[curr] = j;
				curr++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (curr != 4)
		return (0);
	if (!check_invalid_tetrom(tetrom->row, tetrom->col))
	{
		printf("Invalid Tetrominoe\n");
		return (0);
	}
	return (1);
}

void	printLine(Tetrom *t)
{
	int i;

	i = 0;
	while (i < 4)
		printf("%s\n", t->pieces[i++]);
	printf("\n");
}

void		tetrom_lstiter(Tetrom *lst, void (*f)(Tetrom *elem))
{
	while (lst != NULL)
	{
		(*f)(lst);
		lst = lst->next;
	}
}

int		check_invalid_char(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '.' && str[i] != '#')
			return (0);
	}
	return (1);
}

Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int fd)
{
	int				i;
	int				track_row;
	char			*line;
	Tetrom			*head;

	i = 0;
	track_row = 0;
	head = NULL;
	if (!(tetrom->pieces = ft_2Dstrnew(4)))
	{
		printf("NULL my dude\n");
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (*line && track_row < 4)
		{
			if (ft_strlen(line) == 4) //checks for correct number of columns
			{
				if(!check_invalid_char(line))
				{
					printf("Invalid description, invalid character\n");
					return (NULL);
				}
				ft_strncpy(tetrom->pieces[i], line, 4);
			}
			else
			{
				printf("Invalid description, not exactly 4 columns\n");
				return (NULL);
			}
			track_row++;
			if (track_row == 4)
			{
				if (!store_block_coordinates(tetrom, tetrom->pieces))
				{
					printf("Invalid description, incorrect number of block chars\n");
					return (NULL);
				}
			}
		}
		else
		{
			if (track_row != 4)
			{
				printf("Invalid description, not exactly 4 rows\n");
				return (NULL);
			}
			tetrom->next = head;
			head = tetrom;
			if (!(tetrom = (Tetrom *)malloc(sizeof(*tetrom))))
				printf("NULL creating a new structure failed\n");
			tetrom->pieces = ft_2Dstrnew(4);
			i = -1;
			track_row = 0;
		}
		i++;
	}
	tetrom->next = head;
	head = tetrom;
	return (head);
}

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
		if (head)
			tetrom_lstiter(head, printLine);
	}
	return (0);
}
