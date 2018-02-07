/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:09:10 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/01 18:12:22 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_fdlist_tail(int fd, t_fdlist **fdlist)
{
	char		*buffer;
	t_fdlist	*previous;

	if (*fdlist && ((*fdlist)->fd == fd))
	{
		buffer = (*fdlist)->text;
		previous = *fdlist;
		*fdlist = (*fdlist)->next;
		free(previous);
		return (buffer);
	}
	while (*fdlist)
	{
		if ((*fdlist)->fd == fd)
		{
			buffer = (*fdlist)->text;
			previous->next = (*fdlist)->next;
			free(*fdlist);
			return (buffer);
		}
		previous = *fdlist;
		fdlist = &((*fdlist)->next);
	}
	return (NULL);
}

int		add_fdlist_tail(t_fdlist **fdlist, int fd, char *text)
{
	t_fdlist *new;

	new = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (!fdlist && !*fdlist && !new && !text)
		return (1);
	new->fd = fd;
	new->text = text;
	new->next = *fdlist;
	*fdlist = new;
	return (0);
}

int		get_endline_index(char *s)
{
	int i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		read_more(char **line, int fd)
{
	char	*buffer;
	char	*temp;
	int		read_result;

	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (get_endline_index(*line) == -1)
	{
		if ((read_result = read(fd, buffer, BUFF_SIZE)) <= 0)
		{
			free(buffer);
			return (read_result);
		}
		if (!(temp = ft_strjoin(*line, buffer)))
		{
			free(buffer);
			return (-1);
		}
		free(*line);
		*line = temp;
		ft_bzero(buffer, BUFF_SIZE);
	}
	free(buffer);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_fdlist	*fdlist;
	char			*temp;
	int				endline_index;

	if (fd < 0 || !line)
		return (-1);
	*line = get_fdlist_tail(fd, &fdlist);
	if (!*line || (*line && (get_endline_index(*line) == -1)))
		if (read_more(line, fd) == -1)
			return (-1);
	if (!*line)
		return (0);
	endline_index = get_endline_index(*line);
	if (endline_index == -1)
		endline_index = ft_strlen(*line);
	if (!(temp = ft_strsub(*line, 0, endline_index)))
		return (-1);
	if (endline_index < (int)(ft_strlen(*line) - 1))
		if (add_fdlist_tail(&fdlist, fd,
							ft_strsub(*line, endline_index + 1,
								ft_strlen(*line) - endline_index - 1)))
			return (-1);
	free(*line);
	*line = temp;
	return (1);
}
