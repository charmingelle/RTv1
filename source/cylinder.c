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

static double	get_cyl_a(t_vector point, double scal_prod_v_v_a, t_vector v_a)
{
	return (get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(point, get_num_prod(scal_prod_v_v_a, v_a))));
}

static double	get_cyl_b(t_vector point, t_vector delta,
	double scal_prod_v_v_a, t_vector v_a, double scal_prod_delta_v_a)
{
	return (2 * get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a))));
}

static double	get_cyl_c(t_vector delta, double scal_prod_delta_v_a, t_vector v_a, double rad)
{
	return (get_scal_prod(get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a))) - pow(rad, 2));
}

t_t1t2			*get_cyl_intersections(t_fig cyl, t_vector o, t_vector d)
{
	t_vector	p_a;
	t_vector	v_a;
	t_vector	delta;
	double		scal_prod_v_v_a;
	double		scal_prod_delta_v_a;

	p_a = cyl.center;
	v_a = get_ort(get_vect(cyl.center, cyl.center2));
	delta = get_diff(o, p_a);
	scal_prod_v_v_a = get_scal_prod(d, v_a);
	scal_prod_delta_v_a = get_scal_prod(delta, v_a);
	return (get_quadratic_solution(get_cyl_a(d, scal_prod_v_v_a, v_a),
		get_cyl_b(d, delta, scal_prod_v_v_a, v_a, scal_prod_delta_v_a),
		get_cyl_c(delta, scal_prod_delta_v_a, v_a, cyl.rad)));
}
