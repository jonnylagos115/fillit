/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_llist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:42:46 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/25 14:13:10 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetriminoes.c"
#include <fcntl.h>

char	**ft_2Dstrnew(size_t size)
{
	size_t		i;
	char		**arr_str;

	i = 0;
	if (!(arr_str = (char **)malloc(size + 1 *sizeof(char))))
		return (NULL);
	while (i < 4)
		if (!(arr_str[i] = ft_strnew(5)

}

void	push(t_list *head, char *line)
{
	t_list			*node;
	static int		i;
       
	if (!(node = (t_list *)malloc(sizeof(*node))))
		return (NULL);
	node->next = head;
	if (content == NULL)
		node->content = NULL;
	else
	{
		if (!(node->tetrim = ft_2Dstrnew(4)))
			return (NULL);
		ft_strncpy(node->tetrim[i++], *line, 5);
	}
	*head = node;
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
	return (0);
}
