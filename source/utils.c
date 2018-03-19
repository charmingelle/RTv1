/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/19 15:37:35 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sol	get_quadratic_solution(double a, double b, double c)
{
	double	discrim;

	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return ((t_sol){INFINITY, INFINITY});
	return ((t_sol){(-b + sqrt(discrim)) / (2 * a),
		(-b - sqrt(discrim)) / (2 * a)});
}

t_sol	get_lim_solution(t_sol sol, t_ray ray, t_fig *fig, t_vector va)
{
	t_vector	q;

	if (sol.t1 == INFINITY && sol.t2 == INFINITY)
		return (sol);
	q = vsum(ray.o, vmult(sol.t1, ray.d));
	if ((vscal(va, vdiff(q, fig->center)) <= 0.0
		|| vscal(va, vdiff(q, fig->center2)) >= 0.0))
		sol.t1 = INFINITY;
	q = vsum(ray.o, vmult(sol.t2, ray.d));
	if ((vscal(va, vdiff(q, fig->center)) <= 0.0
		|| vscal(va, vdiff(q, fig->center2)) >= 0.0))
		sol.t2 = INFINITY;
	return (sol);
}

double	get_rad(int degree)
{
	return ((degree * M_PI) / 180);
}
