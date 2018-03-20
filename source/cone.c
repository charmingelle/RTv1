/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/19 15:40:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sol		get_cone_intersection(t_fig *fig, t_ray ray)
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
						- pow(sin(ang), 2) * pow(delta_va, 2)),
				ray, fig, va));
}

t_vector	get_cone_normal(t_fig *fig, t_vector p)
{
	t_vector	pa;
	t_vector	n;
	t_vector	t;

	pa = vsum(fig->center, vmult(fig->rad / (fig->rad - fig->rad2),
			vdiff(fig->center2, fig->center)));
	n = vdiff(p, fig->center);
	t = vmult(1.0 / vlen(vdiff(pa, p)), vdiff(pa, p));
	return (vort(vdiff(n, vmult(vscal(n, t), t))));
}
