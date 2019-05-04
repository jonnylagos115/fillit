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

/*
** Returns length of string array (I'm going to add it to libft later)
*/
int		ft_2dstrlen(char **str_arr)
{
	int	len;

	len = 0;
	while (str_arr[len])
		len++;
	return (len);
}

/*
** Function below counts the total number of sides touching in each block
** This determines invalid pieces like diagonals or disconnected blocks
*/
int		check_invalid_tetrom(char *str)
{
	int i;
	int touches;

	i = -1;
	touches = 0;
	while (str[++i]) //record the number of touches each block has from one another
	{
		if (str[i] == '#')
		{
			if (i != 0 && str[i - 1] == '#') //checks left
				touches++;
			if (str[i + 1] == '#') //checks right
				touches++;
			if (i > 4 && str[i - 5] == '#') //checks above
				touches++;
			if (i < 14 && str[i + 5] == '#') //checks below
				touches++;
		}
	}
	if (touches < 6) //A valid tetrominoe will have either 6 or 8 connections total among the blocks
		return (0);
	return (1);
}

/* int	check_if_lines_valid(char *str)
** Function checks the following:
** Correct number of blocks '#'
** Invalid chars (ones thats are neither '#' nor '.')
** Newline character is in correct index (also determines the correct number of columns)
*/
int		check_if_lines_valid(char *str)
{
	int 		i;
	int			check_nl;
	int			block_nbr;

	i = -1;
	check_nl = 4;
	block_nbr = 0;
	while (str[++i])
	{
		if (str[i] == '#')
			block_nbr++;
		if (i == check_nl)
		{
			if (str[i] == '\n')
				check_nl += 5;
			else
				return (0);
		}
		else if (str[i] != '.' && str[i] != '#')
			return (0);
	}
	return (1);
}

int		check_if_insert_space(char *str, int index)
{
	int	touches;

	touches = 0;
	if (index != 0 && (str[index - 1] == '#' || str[index - 1] == ' ')) //checks left
		touches++;
	if (str[index + 1] == '#' || str[index + 1] == ' ') //checks right
		touches++;
	if (index > 4 && (str[index - 5] == '#' || str[index - 5] == ' ')) //checks above
		touches++;
	if (index < 14 && (str[index + 5] == '#' || str[index + 5] == ' ')) //checks below
		touches++;
	if (touches >= 2)
	{
		str[index] = ' ';
		return (1);
	}
	return (0);
}

/* create_store_piece(Tetrom *tetrom, char *str)
** Function traverses through string to locate where to assign character space
** The reason I do this is to get the sole shape of the piece in string array form (calling ft_strsplit) without it being inside a 4x4 grid
** Example:
** (Before in char array form)		(After in string array form)
** ....(\n)							##		
** .##.(\n)			 			 	 #
** ..#.(\n)			 			 	 #
** ..#.(\n)
** Then functions stores the height, width, and piece itself
*/

void	create_store_piece(Tetrom *tetrom, char *str)
{
	int		i;
	int		s;
	int		flag;

	i = -1;
	s = -5;
	flag = 0;
	while (++i < 4)
	{
		while (((s += 5) <= 15))
		{
			if (str[i + s] == '#' || str[i + s] == ' ')
			{
				if (i != 0 && str[(i - 1) + s] == '.') //checks left
					flag += check_if_insert_space(str, i - 1 + s);
				if (str[(i + 1) + s] == '.') //checks right
					flag += check_if_insert_space(str, i + 1 + s);
				if ((i + s) > 4 && str[(i + s) - 5] == '.') //checks above
					flag += check_if_insert_space(str, i + s - 5);
				if ((i + s) < 14 && str[(i + s) + 5] == '.') //checks below
					flag += check_if_insert_space(str, i + s + 5);
			}
		}
		s = -5;
		if (flag)
		{
			i = -1;
			flag = 0;
		}
	}
	i = -1;
	while (((i += 5) <= 20)) //overwrites every newline char to '.' in order for ft_strsplit to count it as a delimiter
		str[i] = '.';
	tetrom->piece = ft_strsplit(str, '.');
	tetrom->height = ft_2dstrlen(tetrom->piece);
	tetrom->width = ft_strlen(tetrom->piece[0]);
	get_reset_coordinates(tetrom, "both");
}

/* Tetrom *assemble_tetrominoes(Tetrom *tetrom, int fd)
** Parses through the file, creates a list if piece is valid and adds it onto the linked list of pieces
*/

Tetrom		*assemble_tetrominoes(Tetrom *tetrom, int *tetrom_count, int fd)
{
	Tetrom			*head;
	Tetrom			*tmp;
	char			line[BUFFER_SIZE + 1];
	char			alpha;
	int				i;

	head = tetrom;
	tetrom->next = NULL;
	alpha = 'A';
	i = -1;
	while (read(fd, line, BUFFER_SIZE))
	{
		line[BUFFER_SIZE] = '\0';
		if (!check_if_lines_valid(line) || !check_invalid_tetrom(line))
			return (NULL);
		if (!tetrom)
		{
			if (!(tetrom = (Tetrom *)malloc(sizeof(*tetrom))))
				return (NULL);
			tmp->next = tetrom;
			tetrom->next = NULL;
		}
		create_store_piece(tetrom, line);
		read(fd, line, 1);
		tetrom->alphabet = alpha++;
		tmp = tetrom;
		tetrom = tetrom->next;
		(*tetrom_count)++;
	}
	return (head);
}