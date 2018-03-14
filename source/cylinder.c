/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 18:01:39 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static double	get_a(t_vector d, double d_scal_va, t_vector va)
{
	return (vscal(vdiff(d, vmult(d_scal_va, va)),
		vdiff(d, vmult(d_scal_va, va))));
}

static double	get_b(t_vector d, t_vector delta,
	double d_scal_va, t_vector va, double delta_scal_va)
{
	return (2 * vscal(vdiff(d, vmult(d_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va))));
}

static double	get_c(t_vector delta, double delta_scal_va,
	t_vector va, double rad)
{
	return (vscal(vdiff(delta, vmult(delta_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va))) - pow(rad, 2));
}

double			get_cyl_intersection(t_fig *fig, t_ray ray)
{
	t_vector	pa;
	t_vector	va;
	t_vector	delta;
	double		d_scal_va;
	double		delta_scal_va;

	pa = fig->center;
	va = vort(vdiff(fig->center2, fig->center));
	delta = vdiff(ray.o, pa);
	d_scal_va = vscal(ray.d, va);
	delta_scal_va = vscal(delta, va);
	return (get_lim_solution(get_quadratic_solution(get_a(ray.d, d_scal_va, va),
		get_b(ray.d, delta, d_scal_va, va, delta_scal_va),
		get_c(delta, delta_scal_va, va, fig->rad), ray), ray, fig, va));
}

t_vector		get_cyl_normal(t_vector c1, t_vector c2, t_vector p)
{
	t_vector	axis;
	t_vector	c1_minus_p;

	axis = vdiff(c2, c1);
	c1_minus_p = vdiff(c1, p);
	return (vort(vdiff(vmult(vscal(c1_minus_p, axis)
		/ vsquare(axis), axis), c1_minus_p)));
}
