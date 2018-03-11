/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:33:11 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double		get_quadratic_solution(double a, double b, double c, t_ray ray)
{
	double	discrim;
	double	t1;
	double	t2;

	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (INFINITY);
	t1 = (-b + sqrt(discrim)) / (2 * a);
	t2 = (-b - sqrt(discrim)) / (2 * a);
	if (!IN_RANGE(t1, ray.t_min, ray.t_max) && !IN_RANGE(t2, ray.t_min, ray.t_max))
		return (INFINITY);
	if (!IN_RANGE(t1, ray.t_min, ray.t_max))
		return (t2);
	if (!IN_RANGE(t2, ray.t_min, ray.t_max))
		return (t1);
	return (MIN(t1, t2));
}

double		get_rad(int degree)
{
	return ((degree * M_PI) / 180);
}

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

int			count_elems(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
