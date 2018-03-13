/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/13 16:05:45 by grevenko         ###   ########.fr       */
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

double		get_lim_solution(double t, t_ray ray, t_fig *fig, t_vector va)
{
	t_vector	Q;

	if (t == INFINITY)
		return (INFINITY);
	Q = vsum(ray.O, vmult(t, ray.D));
	if (vscal(va, vdiff(Q, fig->center)) > 0.0 && vscal(va, vdiff(Q, fig->center2)) < 0.0)
		return (t);
	return (INFINITY);
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
