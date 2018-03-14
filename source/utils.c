/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:49:34 by grevenko         ###   ########.fr       */
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
	if (!IN_RANGE(t1, ray.t_min, ray.t_max)
		&& !IN_RANGE(t2, ray.t_min, ray.t_max))
		return (INFINITY);
	if (!IN_RANGE(t1, ray.t_min, ray.t_max))
		return (t2);
	if (!IN_RANGE(t2, ray.t_min, ray.t_max))
		return (t1);
	return (MIN(t1, t2));
}

double		get_lim_solution(double t, t_ray ray, t_fig *fig, t_vector va)
{
	t_vector	q;

	if (t == INFINITY)
		return (INFINITY);
	q = vsum(ray.o, vmult(t, ray.d));
	if (vscal(va, vdiff(q, fig->center)) > 0.0
		&& vscal(va, vdiff(q, fig->center2)) < 0.0)
		return (t);
	return (INFINITY);
}

double		get_rad(int degree)
{
	return ((degree * M_PI) / 180);
}
