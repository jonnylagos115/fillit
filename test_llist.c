/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_llist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:42:46 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/31 15:58:11 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetriminoes.h"
#include <fcntl.h>

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

void		node_lstiter(Node *lst, void (*f)(Node *elem))
{
	while (lst != NULL)
	{
		(*f)(lst);
		printf("\n");
		lst = lst->next;
	}
}

void	printLine(Node *node)
{
	int i;

	i = 0;
	while (i < 4)
		printf("%s\n", node->tetrim[i++]);
}

void	push(Node *node, int fd)
{
	int				i;
	char			*line;
	Node			*start;
	Node			*head;

	i = 0;
	start = node;
	head = NULL;
	if (!(node->tetrim = ft_2Dstrnew(4)))
		printf("NULL my dude\n");
	while (get_next_line(fd, &line) > 0) 
	{
		if (*line)
			ft_strncpy(node->tetrim[i], line, 4);
		else
		{
			node->next = head;
			head = node;
			if (!(node = (Node *)malloc(sizeof(*node))))
				printf("NULL creating a new structure failed\n");
			node->tetrim = ft_2Dstrnew(4);
			i = -1;
		}
		i++;
	}
	node->next = head;
	head = node;
	node_lstiter(head, printLine);
}

int		main(int argc, char **argv)
{
	int		fd;
	Node 	start;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	push(&start, fd);
	if (argc == 2)
		close(fd);
	return (0);
}
