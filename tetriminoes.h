/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/04 18:44:44 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIMINOES_H
# define TETRIMINOES_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "./gnl/get_next_line.h"

typedef struct Tetriminoes
{
	int					row[4];
	int					col[4];
	char				**pieces;
	struct Tetriminoes	*next;
}Tetrim;
void 		printLine(Tetrim *t);
void		tetrim_lstiter(Tetrim *lst, void (*f)(Tetrim *elem));
void		store_block_coordinates(Tetrim *tetrim, char **piece);
char		**ft_2Dstrnew(size_t size);
Tetrim		*assemble_tetriminoes(Tetrim *tetrim, int fd);

#endif
