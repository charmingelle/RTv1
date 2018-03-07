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

static double	get_a(double angle, t_vector V, double V_scal_va, t_vector va)
{
	return (pow(cos(angle * vsquare(vdiff(V, vmult(V_scal_va, va)))), 2)
		- pow(sin(angle * pow(V_scal_va, 2)), 2));
}

static double	get_b(double angle, t_vector V, double V_scal_va,
	t_vector va, t_vector delta, double delta_scal_va)
{
	return (2 * pow(cos(angle * vscal(vdiff(V, vmult(V_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va)))), 2)
		- 2 * pow(sin(angle * V_scal_va * delta_scal_va), 2));
}

static double	get_c(double angle, t_vector delta, double delta_scal_va, t_vector va)
{
	return (pow(cos(angle * vsquare(vdiff(delta, vmult(delta_scal_va, va)))), 2)
		- pow(sin(angle * pow(delta_scal_va, 2)), 2));
}

t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
{
	t_vector	P;
	t_vector	V;
	t_vector	pa;
	t_vector	va;
	double		angle;
	t_vector	delta;
	double		V_scal_va;
	double		delta_scal_va;

	// printf("cone.center = (%f, %f, %f), cone.center2 = (%f, %f, %f), code.rad = %f, cone.rad2 = %f\n",
	// 	fig->center.x, fig->center.y, fig->center.z,
	// 	fig->center2.x, fig->center2.y, fig->center2.z,
	// 	fig->rad, fig->rad2);
	P = O;
	V = D;
	pa = vsum(fig->center,
			vmult(fig->rad / (fig->rad - fig->rad2),
				vdiff(fig->center2, fig->center)));
	// printf("pa = (%f, %f, %f)\n", pa.x, pa.y, pa.z);
	va = vort(vdiff(fig->center2, fig->center));
	// printf("va = (%f, %f, %f)\n", va.x, va.y, va.z);
	angle = atan((fig->rad - fig->rad2) / (vlen(vdiff(fig->center2, fig->center))));
	// printf("angle = %f\n", angle);
	delta = vdiff(P, pa);
	V_scal_va = vscal(V, va);
	delta_scal_va = vscal(delta, va);
	return (get_quadratic_solution(get_a(angle, V, V_scal_va, va),
		get_b(angle, V, V_scal_va, va, delta, delta_scal_va),
		get_c(angle, delta, delta_scal_va, va)));
}

// t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
// {
// 	t_vector	P;
// 	t_vector	V;
// 	t_vector	pa;
// 	t_vector	va;
// 	double		angle;
// 	t_vector	delta;
// 	double		V_scal_va;
// 	double		delta_scal_va;

// 	// printf("cone.center = (%f, %f, %f), cone.center2 = (%f, %f, %f), code.rad = %f, cone.rad2 = %f\n",
// 	// 	fig->center.x, fig->center.y, fig->center.z,
// 	// 	fig->center2.x, fig->center2.y, fig->center2.z,
// 	// 	fig->rad, fig->rad2);
// 	P = O;
// 	V = D;
// 	pa = vdiff(fig->center, fig->center2);
// 	va = vort(vdiff(fig->center, fig->center2));
// 	angle = get_rad(15);
// 	delta = vdiff(P, pa);
// 	V_scal_va = vscal(V, va);
// 	delta_scal_va = vscal(delta, va);
// 	return (get_quadratic_solution(get_a(angle, V, V_scal_va, va),
// 		get_b(angle, V, V_scal_va, va, delta, delta_scal_va),
// 		get_c(angle, delta, delta_scal_va, va)));
// }

// static double	get_a(double angle, t_vector point, double scal_prod_v_v_a, t_vector v_a)
// {
// 	return (pow(cos(angle * vsquare(vdiff(point, vmult(scal_prod_v_v_a, v_a)))), 2)
// 		- pow(sin(angle * pow(scal_prod_v_v_a, 2)), 2));
// }

// static double	get_b(double angle, t_vector point, double scal_prod_v_v_a,
// 	t_vector v_a, t_vector delta, double scal_prod_delta_v_a)
// {
// 	return (2 * pow(cos(angle * vscal(vdiff(point, vmult(scal_prod_v_v_a, v_a)),
// 		vdiff(delta, vmult(scal_prod_delta_v_a, v_a)))), 2)
// 		- 2 * pow(sin(angle * scal_prod_v_v_a * scal_prod_delta_v_a), 2));
// }

// static double	get_c(double angle, t_vector delta, double scal_prod_delta_v_a, t_vector v_a)
// {
// 	return (pow(cos(angle * vsquare(vdiff(delta, vmult(scal_prod_delta_v_a, v_a)))), 2)
// 		- pow(sin(angle * pow(scal_prod_delta_v_a, 2)), 2));
// }

// t_t1t2			*get_cone_intersections(t_env *env, t_fig cone, t_vector point)
// {
// 	t_vector	p_a;
// 	t_vector	v_a;
// 	t_vector	delta;
// 	double		angle;
// 	double		scal_prod_v_v_a;
// 	double		scal_prod_delta_v_a;

// 	p_a = vsum(cone.center, vmult(cone.rad / (cone.rad - cone.rad2),
// 		vdiff(cone.center2, cone.center)));
// 	v_a = vort(vdiff(cone.center2, cone.center));
// 	angle = atan((cone.rad - cone.rad2) / (vlen(vdiff(cone.center2, cone.center))));
// 	// p_a = cone.center;
// 	// v_a = vort(vdiff(cone.center2, cone.center));
// 	// angle = get_rad(60);
// 	delta = vdiff(env->camera, p_a);
// 	scal_prod_v_v_a = vscal(point, v_a);
// 	scal_prod_delta_v_a = vscal(delta, v_a);
// 	return (get_quadratic_solution(get_a(angle, point, scal_prod_v_v_a, v_a),
// 		get_b(angle, point, scal_prod_v_v_a, v_a, delta, scal_prod_delta_v_a),
// 		get_c(angle, delta, scal_prod_delta_v_a, v_a)));
// }

// static double	get_a(t_vector d, t_vector v, double theta)
// {
// 	return (pow(vscal(d, v), 2) - pow(cos(theta), 2));
// }

// static double	get_b(t_vector d, t_vector v, t_vector co, double theta)
// {
// 	return (2 * (vscal(d, v) * vscal(co, v) - vscal(d, co) * pow(cos(theta), 2)));
// }

// static double	get_c(t_vector co, t_vector v, double theta)
// {
// 	return (pow(vscal(co, v), 2) - vsquare(co) * pow(cos(theta), 2));
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
// 	v = vort(get_vect(cone.center, cone.center2));
// 	co = get_vect(c, o);
// 	theta = get_rad(15);
// 	return (get_quadratic_solution(get_a(d, v, theta),
// 		get_b(d, v, co, theta),
// 		get_c(co, v, theta)));
// }

// static double	get_a(t_vector d)
// {
// 	return (pow(d.x, 2) + pow(d.y, 2) - pow(d.z, 2));
// }

// static double	get_b(t_vector d, t_vector e)
// {
// 	return (2 * e.x * d.x + 2 * e.y * d.y - 2 * e.z * d.z);
// }

// static double	get_c(t_vector e)
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
// 	return (get_quadratic_solution(get_a(d),
// 		get_b(d, e),
// 		get_c(e)));
// }
