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

static double	get_a(double angle, t_vector D, double V_scal_va, t_vector va)
{
	return (pow(cos(angle), 2) * vsquare(vdiff(D, vmult(V_scal_va, va)))
		- pow(sin(angle), 2) * pow(V_scal_va, 2));
}

static double	get_b(double angle, t_vector D, double V_scal_va,
	t_vector va, t_vector delta, double delta_scal_va)
{
	return (2 * pow(cos(angle), 2) * vscal(vdiff(D, vmult(V_scal_va, va)),
		vdiff(delta, vmult(delta_scal_va, va)))
		- 2 * pow(sin(angle), 2) * V_scal_va * delta_scal_va);
}

static double	get_c(double angle, t_vector delta, double delta_scal_va, t_vector va)
{
	return (pow(cos(angle), 2) * vsquare(vdiff(delta, vmult(delta_scal_va, va)))
		- pow(sin(angle), 2) * pow(delta_scal_va, 2));
}

// t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
// {
// 	t_vector	pa;
// 	t_vector	va;
// 	double		angle;
// 	t_vector	delta;
// 	double		V_scal_va;
// 	double		delta_scal_va;

// 	pa = fig->center;
// 	va = vort(vdiff(fig->center2, fig->center));
// 	angle = get_rad(15);
// 	delta = vdiff(O, pa);
// 	V_scal_va = vscal(D, va);
// 	delta_scal_va = vscal(delta, va);
// 	return (get_quadratic_solution(get_a(angle, D, V_scal_va, va),
// 		get_b(angle, D, V_scal_va, va, delta, delta_scal_va),
// 		get_c(angle, delta, delta_scal_va, va)));
// }

t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
{
	t_vector	pa;
	t_vector	va;
	double		angle;
	t_vector	delta;
	double		V_scal_va;
	double		delta_scal_va;

	pa = vsum(fig->center,
			vmult(fig->rad / (fig->rad - fig->rad2),
				vdiff(fig->center2, fig->center)));
	va = vort(vdiff(fig->center2, fig->center));
	angle = atan((fig->rad - fig->rad2) / (vlen(vdiff(fig->center2, fig->center))));
	delta = vdiff(O, pa);
	V_scal_va = vscal(D, va);
	delta_scal_va = vscal(delta, va);
	return (get_quadratic_solution(get_a(angle, D, V_scal_va, va),
		get_b(angle, D, V_scal_va, va, delta, delta_scal_va),
		get_c(angle, delta, delta_scal_va, va)));
}

// t_t1t2			*filter_solutions(t_t1t2 *sol, t_vector va, t_vector P, t_vector V, t_fig *fig)
// {
// 	t_vector	Q;
// 	int			first;
// 	int			second;

// 	if (sol == NULL)
// 		return (NULL);
// 	printf("here\n");
// 	Q = vsum(P, vmult(sol->t1, V));
// 	if (vscal(va, vdiff(Q, fig->center)) <= 0 || vscal(va, vdiff(Q, fig->center2)) >= 0)
// 		first = 1;
// 	Q = vsum(P, vmult(sol->t2, V));
// 	if (vscal(va, vdiff(Q, fig->center)) <= 0 || vscal(va, vdiff(Q, fig->center2)) >= 0)
// 		second = 1;
// 	if (first && second)
// 		return (NULL);
// 	if (first)
// 		sol->t1 = sol->t2;
// 	if (second)
// 		sol->t2 = sol->t1;
// 	return (sol);
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

// ---

// static double	get_a(t_vector D, t_vector V, double theta)
// {
// 	return (pow(vscal(D, V), 2) - pow(cos(theta), 2));
// }

// static double	get_b(t_vector D, t_vector V, t_vector CO, double theta)
// {
// 	return (2 * (vscal(D, V) * vscal(CO, V) - vscal(D, CO) * pow(cos(theta), 2)));
// }

// static double	get_c(t_vector CO, t_vector V, double theta)
// {
// 	return (pow(vscal(CO, V), 2) - vsquare(CO) * pow(cos(theta), 2));
// }

// t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
// {
// 	t_vector	C;
// 	t_vector	V;
// 	t_vector	CO;
// 	double		theta;
// 	t_t1t2		*sol;

// 	C = fig->center;
// 	V = vort(vdiff(fig->center2, fig->center));
// 	CO = vdiff(O, C);
// 	theta = get_rad(15);
// 	sol = get_quadratic_solution(get_a(D, V, theta),
// 		get_b(D, V, CO, theta),
// 		get_c(CO, V, theta));
// 	return (get_quadratic_solution(get_a(D, V, theta),
// 		get_b(D, V, CO, theta),
// 		get_c(CO, V, theta)));
// }

// ---

// static double	get_a(t_vector D)
// {
// 	return (pow(D.x, 2) + pow(D.y, 2) - pow(D.z, 2));
// }

// static double	get_b(t_vector D, t_vector E)
// {
// 	return (2 * E.x * D.x + 2 * E.y * D.y - 2 * E.z * D.z);
// }

// static double	get_c(t_vector E)
// {
// 	return (pow(E.x, 2) + pow(E.y, 2) - pow(E.z, 2));
// }

// t_t1t2			*get_cone_intersections(t_fig *fig, t_vector O, t_vector D)
// {
// 	return (get_quadratic_solution(get_a(D),
// 		get_b(D, O),
// 		get_c(O)));
// }
