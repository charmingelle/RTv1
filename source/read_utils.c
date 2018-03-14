/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:40:12 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	hex_to_digit(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= '0' && c <= '9')
		return (c - '0');
	exit(show_invalid_color_error());
}

int			read_color(char *s)
{
	int	result;
	int	i;

	if ((s[0] != '0') || (s[1] != 'x'))
		exit(show_invalid_color_error());
	result = 0;
	i = 1;
	while (s[++i])
		result = result * 16 + hex_to_digit(s[i]);
	if (result > 0xFFFFFF)
		exit(show_invalid_color_error());
	return (result);
}

int			get_non_negative(int n)
{
	if (n < 0)
		exit(show_invalid_value_error());
	return (n);
}

void		set_vector_value(char *source, t_vector *vector)
{
	char	**coords;

	coords = ft_strsplit(source, ',');
	if (count_elems(coords) != 3)
		exit(show_invalid_vector_error());
	*vector = (t_vector){
		ft_atoi(coords[0]),
		ft_atoi(coords[1]),
		ft_atoi(coords[2])};
	free_split(coords);
}

int			count_elems(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
