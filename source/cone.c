/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 17:56:34 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static double	get_a(double angle, t_vector d, double v_scal_va, t_vector va)
{
	return (pow(cos(angle), 2) * vsquare(vdiff(d, vmult(v_scal_va, va)))
		- pow(sin(angle), 2) * pow(v_scal_va, 2));
}

static double	get_b(double angle, t_vector d, double v_scal_va,
	t_vector va, t_vector delta, double delta_scal_va)
{
	return (2 * pow(cos(angle), 2) * vscal(vdiff(d, vmult(v_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va)))
		- 2 * pow(sin(angle), 2) * v_scal_va * delta_scal_va);
}

static double	get_c(double angle, t_vector delta,
	double delta_scal_va, t_vector va)
{
	return (pow(cos(angle), 2) * vsquare(vdiff(delta, vmult(delta_scal_va, va)))
		- pow(sin(angle), 2) * pow(delta_scal_va, 2));
}

double			get_cone_intersection(t_fig *fig, t_ray ray)
{
	t_vector	pa;
	t_vector	va;
	double		angle;
	t_vector	delta;
	double		v_scal_va;
	double		delta_scal_va;

	pa = vsum(fig->center,
			vmult(fig->rad / (fig->rad - fig->rad2),
				vdiff(fig->center2, fig->center)));
	va = vort(vdiff(fig->center2, fig->center));
	angle = atan((fig->rad - fig->rad2)
		/ (vlen(vdiff(fig->center2, fig->center))));
	delta = vdiff(ray.o, pa);
	v_scal_va = vscal(ray.d, va);
	delta_scal_va = vscal(delta, va);
	return (get_lim_solution(
				get_quadratic_solution(
					get_a(angle, ray.d, v_scal_va, va),
					get_b(angle, ray.d, v_scal_va, va, delta, delta_scal_va),
					get_c(angle, delta, delta_scal_va, va),
					ray),
				ray, fig, va));
}

t_vector		get_cone_normal(t_vector c1, t_vector c2,
	double rad, double rad2, t_vector p)
{
	/*
	t_vector	cyl_normal;
	t_vector	G1;
	t_vector	G2;

	cyl_normal = get_cyl_normal(C1, C2, P);
	G1 = vsum(C1, vmult(rad, cyl_normal));
	G2 = vsum(C2, vmult(rad2, cyl_normal));
	return (get_cyl_normal(G1, G2, P));
	*/
	return (get_cyl_normal(c1, c2, p));
}
