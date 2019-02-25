/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:09:21 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/17 14:13:43 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		check_invalid_tetrom(int *row, int *col)
{
	int i;
	int j;
	int touches;
	int len;

	i = -1;
	j = -1;
	touches = 0;
	len = 3;
	while (++i < 4) //record the number of touches each block has from one another
	{
		if (i == 0)
		{
			if (row[i] == row[i + 1]) //checks right only 
					if ((col[i + 1] - col[i]) == 1)
						touches++;
			while (++j < 3) 
			{
				if (col[i] == col[j + 1]) //checks below only
					if ((row[j + 1] - row[i]) == 1) 
						touches++;
			}
			j = -1;
		}
		else
		{
			if (row[i] == row[i + 1])
				if ((col[i + 1] - col[i]) == 1) //checks from the right of current block
					touches++;
			if (row[i - 1] == row[i])
				if ((col[i] - col[i - 1]) == 1) //checks from the left of current block
					touches++;
			while (++j < 3)
			{
				if (col[i] == col[j + 1])
					if ((row[j + 1] - row[i]) == 1) //checks below of current block
						touches++;
				if (col[j - 1] == col[i])
					if ((row[i] - row[j - 1]) == 1) //checks above of current block
						touches++;
			}
			j = -1;
		}
		if (i == 2) 
		{
			i++; //increment to last set of coordinates 
			if (row[i] == row[i - 1]) //checks the left
				if ((col[i] - col[i - 1]) == 1)
					touches++;
			while (++j < 3)
			{
				if (col[i] == col[j]) //checks above (it is at bottom end)
					if ((row[i] - row[j]) == 1)
						touches++;
			}
			j = -1;
		}
	}
	if (touches < 6) //A valid tetrominoe will have at minimum 6 connections total among the blocks
		return (0);
	return (1);
}

int		store_block_coordinates(Tetrom *tetrom, char **piece)
{
	int i;
	int j;
	int curr;

	i = -1;
	j = -1;
	curr = 0;
	while (++i < 4)
	{
		while (piece[i][++j])
		{
			if (piece[i][j] != '.')
			{
				if (curr > 3)
					return (0);
				tetrom->row[curr] = i;
				tetrom->col[curr] = j;
				curr++;
			}
		}
		j = -1;
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
	if (!(tetrom->pieces = ft_2dstrnew(4)))
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
			tetrom->pieces = ft_2dstrnew(4);
			i = -1;
			track_row = 0;
		}
		i++;
	}
	tetrom->next = head;
	head = tetrom;
	return (head);
}