/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:38:52 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	get_sphere_intersection(t_fig *fig, t_ray ray)
{
	t_vector	vector;
	double		a;
	double		b;
	double		c;

	vector = vdiff(ray.o, fig->center);
	a = vscal(ray.d, ray.d);
	b = 2 * vscal(vector, ray.d);
	c = vscal(vector, vector) - fig->rad * fig->rad;
	return (get_quadratic_solution(a, b, c, ray));
}
