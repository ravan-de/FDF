/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ravan-de <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/10 15:03:15 by ravan-de      #+#    #+#                 */
/*   Updated: 2019/05/15 17:40:58 by ravan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <stdlib.h>

static int	ft_locatefd(char *rest, int fd)
{
	size_t	n;
	char	*itoa;

	n = 0;
	while (rest[n] != '\0')
	{
		if (ft_atoi(&rest[n]) == fd)
			return (n + 6);
		if (n >= (BUFF_SIZE + 7) * 100)
			return (-1);
		n += BUFF_SIZE + 7;
	}
	itoa = ft_itoa(fd);
	if (itoa == NULL)
		return (-1);
	ft_strcpy(&rest[n], itoa);
	free(itoa);
	return (n + 6);
}

void		ft_del(void *data, size_t size)
{
	ft_memdel(&data);
	size = 0;
}

char		*ft_final(t_list **lst, t_list *new)
{
	t_list	*begin;
	char	*line;
	size_t	size;

	size = 0;
	ft_lstadd(lst, new);
	begin = *lst;
	while (begin->next != NULL)
	{
		size += begin->content_size;
		begin = begin->next;
	}
	line = ft_strnew(size);
	while ((*lst)->next != NULL)
	{
		size -= (*lst)->content_size;
		ft_memcpy(&line[size], (*lst)->content, (*lst)->content_size);
		begin = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(&begin, ft_del);
	}
	ft_lstdelone(lst, ft_del);
	return (line);
}

static int	ft_read(t_list **lst, char **line, char *rest, int bytes_read)
{
	char	*buf;
	size_t	i;

	i = 0;
	if (rest[0] == 0 || bytes_read == -2)
	{
		buf = (char *)ft_memalloc(BUFF_SIZE + 1);
		ft_bzero(rest, BUFF_SIZE);
		bytes_read = read(ft_atoi(rest - 6), (void *)buf, BUFF_SIZE);
		if (bytes_read != -1)
			ft_memcpy(rest, buf, bytes_read);
		ft_strdel(&buf);
		if (bytes_read == -1)
			return (-1);
	}
	while (rest[i] != '\0' && rest[i] != '\n')
		i++;
	if (rest[i] == '\0' && bytes_read > 0)
	{
		ft_lstadd(lst, ft_lstnew(rest, i));
		return (-2);
	}
	*line = ft_final(lst, ft_lstnew(rest, i));
	ft_memmove(rest, &rest[i + 1], ft_strlen(&rest[i + 1]) + 1);
	return (bytes_read);
}

int			get_next_line(const int fd, char **line)
{
	static char		rest[(BUFF_SIZE + 7) * 100];
	t_list			*lst;
	int				index;
	int				bytes_read;

	lst = ft_lstnew("", 1);
	bytes_read = BUFF_SIZE;
	index = ft_locatefd(rest, fd);
	rest[index + BUFF_SIZE] = '\0';
	if (index == -1 || line == NULL)
		return (-1);
	while (bytes_read != 0)
	{
		if (bytes_read == -1)
			return (-1);
		bytes_read = ft_read(&lst, line, &rest[index], bytes_read);
		if (bytes_read > 0)
			return (1);
	}
	if (*line[0] == '\0')
		return (0);
	return (1);
}
