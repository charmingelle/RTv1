/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/15 20:40:40 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double		get_cyl_intersection(t_fig *fig, t_ray ray)
{
	t_vector	va;
	t_vector	delta;
	double		d_va;
	double		delta_va;

	va = vort(vdiff(fig->center2, fig->center));
	delta = vdiff(ray.o, fig->center);
	d_va = vscal(ray.d, va);
	delta_va = vscal(delta, va);
	return (get_lim_solution(
				get_quadratic_solution(
					vscal(vdiff(ray.d, vmult(d_va, va)),
						vdiff(ray.d, vmult(d_va, va))),
					2 * vscal(vdiff(ray.d, vmult(d_va, va)),
						vdiff(delta, vmult(delta_va, va))),
					vscal(vdiff(delta, vmult(delta_va, va)),
						vdiff(delta, vmult(delta_va, va))) - pow(fig->rad, 2),
					ray),
				ray, fig, va));
}

t_vector	get_cyl_normal(t_vector c1, t_vector c2, t_vector p)
{
	t_vector	axis;
	t_vector	c1_minus_p;

	axis = vdiff(c2, c1);
	c1_minus_p = vdiff(c1, p);
	return (vort(vdiff(vmult(vscal(c1_minus_p, axis)
		/ vsq(axis), axis), c1_minus_p)));
}
