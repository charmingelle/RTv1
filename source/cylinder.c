/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:33:11 by grevenko         ###   ########.fr       */
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

t_t1t2			*get_cyl_intersections(t_fig *fig, t_vector O, t_vector D)
{
	t_vector	pa;
	t_vector	va;
	t_vector	delta;
	double		D_scal_va;
	double		delta_scal_va;

	pa = fig->center;
	va = vort(vdiff(fig->center2, fig->center));
	delta = vdiff(O, pa);
	D_scal_va = vscal(D, va);
	delta_scal_va = vscal(delta, va);
	return (get_quadratic_solution(get_a(D, D_scal_va, va),
		get_b(D, delta, D_scal_va, va, delta_scal_va),
		get_c(delta, delta_scal_va, va, fig->rad)));
}
