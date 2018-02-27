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

static double	get_cone_a(double alpha, t_vector point, double scal_prod_v_v_a, t_vector v_a)
{
	return (pow(cos(alpha * get_scal_square(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)))), 2)
		- pow(sin(alpha * pow(scal_prod_v_v_a, 2)), 2));
}

static double	get_cone_b(double alpha, t_vector point, double scal_prod_v_v_a,
	t_vector v_a, t_vector delta, double scal_prod_delta_v_a)
{
	return (2 * pow(cos(alpha * get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)))), 2)
		- 2 * pow(sin(alpha * scal_prod_v_v_a * scal_prod_delta_v_a), 2));
}

static double	get_cone_c(double alpha, t_vector delta, double scal_prod_delta_v_a, t_vector v_a)
{
	return (pow(cos(alpha * get_scal_square(get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)))), 2)
		- pow(sin(alpha * pow(scal_prod_delta_v_a, 2)), 2));
}

t_t1t2			*get_cone_intersections(t_env *env, t_fig cone, t_vector point)
{
	t_vector	p_a;
	t_vector	v_a;
	t_vector	delta;
	double	alpha;
	double	scal_prod_v_v_a;
	double	scal_prod_delta_v_a;

	p_a = get_sum(cone.center, get_num_prod(cone.rad / (cone.rad - cone.rad2),
		get_vect(cone.center, cone.center2)));
	v_a = get_ort(get_vect(cone.center, cone.center2));
	alpha = atan((cone.rad - cone.rad2) / (get_len(get_vect(cone.center, cone.center2))));
	delta = get_diff(env->camera, p_a);
	scal_prod_v_v_a = get_scal_prod(point, v_a);
	scal_prod_delta_v_a = get_scal_prod(delta, v_a);
	return (get_quadratic_solution(get_cone_a(alpha, point, scal_prod_v_v_a, v_a),
		get_cone_b(alpha, point, scal_prod_v_v_a, v_a, delta, scal_prod_delta_v_a),
		get_cone_c(alpha, delta, scal_prod_delta_v_a, v_a)));
}
