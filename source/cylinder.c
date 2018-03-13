/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/13 15:38:56 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static double	get_a(t_vector D, double D_scal_va, t_vector va)
{
	return (vscal(vdiff(D, vmult(D_scal_va, va)),
		vdiff(D, vmult(D_scal_va, va))));
}

static double	get_b(t_vector D, t_vector delta,
	double D_scal_va, t_vector va, double delta_scal_va)
{
	return (2 * vscal(vdiff(D, vmult(D_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va))));
}

static double	get_c(t_vector delta, double delta_scal_va, t_vector va, double rad)
{
	return (vscal(vdiff(delta, vmult(delta_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va))) - pow(rad, 2));
}

double			get_lim_solution(double t, t_ray ray, t_fig *fig, t_vector va)
{
	t_vector	Q;

	if (t == INFINITY)
		return (INFINITY);
	Q = vsum(ray.O, vmult(t, ray.D));
	if (vscal(va, vdiff(Q, fig->center)) > 0.0 && vscal(va, vdiff(Q, fig->center2)) < 0.0)
		return (t);
	return (INFINITY);
}

double			get_cyl_intersection(t_fig *fig, t_ray ray)
{
	t_vector	pa;
	t_vector	va;
	t_vector	delta;
	double		D_scal_va;
	double		delta_scal_va;

	pa = fig->center;
	va = vort(vdiff(fig->center2, fig->center));
	delta = vdiff(ray.O, pa);
	D_scal_va = vscal(ray.D, va);
	delta_scal_va = vscal(delta, va);
	return (get_lim_solution(get_quadratic_solution(get_a(ray.D, D_scal_va, va),
		get_b(ray.D, delta, D_scal_va, va, delta_scal_va),
		get_c(delta, delta_scal_va, va, fig->rad), ray), ray, fig, va));
}
