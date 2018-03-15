/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/15 20:03:24 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double		get_cone_intersection(t_fig *fig, t_ray ray)
{
	t_vector	va;
	double		ang;
	t_vector	delta;
	double		v_va;
	double		delta_va;

	va = vort(vdiff(fig->center2, fig->center));
	ang = atan((fig->rad - fig->rad2)
		/ (vlen(vdiff(fig->center2, fig->center))));
	delta = vdiff(ray.o,
		vsum(fig->center, vmult(fig->rad / (fig->rad - fig->rad2),
			vdiff(fig->center2, fig->center))));
	delta = vdiff(ray.o, fig->center2);
	v_va = vscal(ray.d, va);
	delta_va = vscal(delta, va);
	return (get_lim_solution(
				get_quadratic_solution(
					pow(cos(ang), 2) * vsq(vdiff(ray.d, vmult(v_va, va)))
						- pow(sin(ang), 2) * pow(v_va, 2),
					2 * pow(cos(ang), 2) * vscal(vdiff(ray.d, vmult(v_va, va)),
						vdiff(delta, vmult(delta_va, va)))
						- 2 * pow(sin(ang), 2) * v_va * delta_va,
					pow(cos(ang), 2) * vsq(vdiff(delta, vmult(delta_va, va)))
						- pow(sin(ang), 2) * pow(delta_va, 2),
					ray),
				ray, fig, va));
}

t_vector	get_cone_normal(t_fig *fig, t_vector p)
{
	// t_vector	cyl_normal;
	// t_vector	g1;
	// t_vector	g2;

	// cyl_normal = get_cyl_normal(fig->center, fig->center2, p);
	// g1 = vsum(fig->center, vmult(fig->rad, cyl_normal));
	// g2 = vsum(fig->center2, vmult(fig->rad2, cyl_normal));
	// return (get_cyl_normal(g1, g2, p));
	return (get_cyl_normal(fig->center, fig->center2, p));
}

/*
**	return (get_cyl_normal(c1, c2, p));
*/
