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

static double	get_cone_a(double alpha, t_vector v, double vva, t_vector va)
{
	return (pow(cos(alpha * get_scal_square(get_diff(v, get_num_prod(vva, va)))), 2)
		- pow(sin(alpha * pow(vva, 2)), 2));
}

static double	get_cone_b(double alpha, t_vector v, double vva,
	t_vector va, t_vector delta, double deltava)
{
	return (2 * pow(cos(alpha * get_scal_prod(get_diff(v, get_num_prod(vva, va)),
		get_diff(delta, get_num_prod(deltava, va)))), 2)
		- 2 * pow(sin(alpha * vva * deltava), 2));
}

static double	get_cone_c(double alpha, t_vector delta, double deltava, t_vector va)
{
	return (pow(cos(alpha * get_scal_square(get_diff(delta, get_num_prod(deltava, va)))), 2)
		- pow(sin(alpha * pow(deltava, 2)), 2));
}

t_t1t2			*get_cone_intersections(t_fig cone, t_vector o, t_vector d)
{
	t_vector	p;
	t_vector	v;
	t_vector	pa;
	t_vector	va;
	double		alpha;
	t_vector	delta;
	double		vva;
	double		deltava;

	p = o;
	v = d;
	pa = get_sum(cone.center,
		get_num_prod(cone.rad / (cone.rad - cone.rad2), get_diff(cone.center2, cone.center)));
	va = get_ort(get_diff(cone.center2, cone.center));
	alpha = atan((cone.rad - cone.rad2) / (get_len(get_diff(cone.center2, cone.center))));
	delta = get_diff(p, pa);
	vva = get_scal_prod(v, va);
	deltava = get_scal_prod(delta, va);
	return (get_quadratic_solution(get_cone_a(alpha, v, vva, va),
		get_cone_b(alpha, v, vva, va, delta, deltava),
		get_cone_c(alpha, delta, deltava, va)));
}

// static double	get_cone_a(double alpha, t_vector point, double scal_prod_v_v_a, t_vector v_a)
// {
// 	return (pow(cos(alpha * get_scal_square(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)))), 2)
// 		- pow(sin(alpha * pow(scal_prod_v_v_a, 2)), 2));
// }

// static double	get_cone_b(double alpha, t_vector point, double scal_prod_v_v_a,
// 	t_vector v_a, t_vector delta, double scal_prod_delta_v_a)
// {
// 	return (2 * pow(cos(alpha * get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
// 		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)))), 2)
// 		- 2 * pow(sin(alpha * scal_prod_v_v_a * scal_prod_delta_v_a), 2));
// }

// static double	get_cone_c(double alpha, t_vector delta, double scal_prod_delta_v_a, t_vector v_a)
// {
// 	return (pow(cos(alpha * get_scal_square(get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)))), 2)
// 		- pow(sin(alpha * pow(scal_prod_delta_v_a, 2)), 2));
// }

// t_t1t2			*get_cone_intersections(t_env *env, t_fig cone, t_vector point)
// {
// 	t_vector	p_a;
// 	t_vector	v_a;
// 	t_vector	delta;
// 	double		alpha;
// 	double		scal_prod_v_v_a;
// 	double		scal_prod_delta_v_a;

// 	p_a = get_sum(cone.center, get_num_prod(cone.rad / (cone.rad - cone.rad2),
// 		get_diff(cone.center2, cone.center)));
// 	v_a = get_ort(get_diff(cone.center2, cone.center));
// 	alpha = atan((cone.rad - cone.rad2) / (get_len(get_diff(cone.center2, cone.center))));
// 	// p_a = cone.center;
// 	// v_a = get_ort(get_diff(cone.center2, cone.center));
// 	// alpha = get_rad(60);
// 	delta = get_diff(env->camera, p_a);
// 	scal_prod_v_v_a = get_scal_prod(point, v_a);
// 	scal_prod_delta_v_a = get_scal_prod(delta, v_a);
// 	return (get_quadratic_solution(get_cone_a(alpha, point, scal_prod_v_v_a, v_a),
// 		get_cone_b(alpha, point, scal_prod_v_v_a, v_a, delta, scal_prod_delta_v_a),
// 		get_cone_c(alpha, delta, scal_prod_delta_v_a, v_a)));
// }

// static double	get_cone_a(t_vector d, t_vector v, double theta)
// {
// 	return (pow(get_scal_prod(d, v), 2) - pow(cos(theta), 2));
// }

// static double	get_cone_b(t_vector d, t_vector v, t_vector co, double theta)
// {
// 	return (2 * (get_scal_prod(d, v) * get_scal_prod(co, v) - get_scal_prod(d, co) * pow(cos(theta), 2)));
// }

// static double	get_cone_c(t_vector co, t_vector v, double theta)
// {
// 	return (pow(get_scal_prod(co, v), 2) - get_scal_square(co) * pow(cos(theta), 2));
// }

// t_t1t2			*get_cone_intersections(t_env *env, t_fig cone, t_vector point)
// {
// 	t_vector	o;
// 	t_vector	d;
// 	t_vector	c;
// 	t_vector	v;
// 	t_vector	co;
// 	double		theta;

// 	o = env->camera;
// 	d = point;
// 	c = cone.center;
// 	v = get_ort(get_vect(cone.center, cone.center2));
// 	co = get_vect(c, o);
// 	theta = get_rad(15);
// 	return (get_quadratic_solution(get_cone_a(d, v, theta),
// 		get_cone_b(d, v, co, theta),
// 		get_cone_c(co, v, theta)));
// }

// static double	get_cone_a(t_vector d)
// {
// 	return (pow(d.x, 2) + pow(d.y, 2) - pow(d.z, 2));
// }

// static double	get_cone_b(t_vector d, t_vector e)
// {
// 	return (2 * e.x * d.x + 2 * e.y * d.y - 2 * e.z * d.z);
// }

// static double	get_cone_c(t_vector e)
// {
// 	return (pow(e.x, 2) + pow(e.y, 2) - pow(e.z, 2));
// }

// t_t1t2			*get_cone_intersections(t_env *env, t_fig cone, t_vector point)
// {
// 	t_vector	e;
// 	t_vector	d;

// 	cone.color = 0;
// 	e = env->camera;
// 	d = point;
// 	return (get_quadratic_solution(get_cone_a(d),
// 		get_cone_b(d, e),
// 		get_cone_c(e)));
// }
