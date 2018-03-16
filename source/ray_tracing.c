/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/16 16:32:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_vector	get_normal(t_vector p, t_fig *fig)
{
	if (!ft_strcmp(fig->type, "sphere"))
		return (vort(vdiff(p, fig->center)));
	if (!ft_strcmp(fig->type, "cylinder"))
		return (get_cyl_normal(fig->center, fig->center2, p));
	if (!ft_strcmp(fig->type, "cone"))
		return (get_cone_normal(fig, p));
	if (!ft_strcmp(fig->type, "plane"))
		return (vort(fig->center2));
	return ((t_vector){0, 0, 0});
}

static t_sol	get_intersection(t_fig *fig, t_ray ray)
{
	if (ft_strcmp(fig->type, "sphere") == 0)
		return (get_sphere_intersection(fig, ray));
	if (ft_strcmp(fig->type, "cylinder") == 0)
		return (get_cyl_intersection(fig, ray));
	if (ft_strcmp(fig->type, "cone") == 0)
		return (get_cone_intersection(fig, ray));
	if (ft_strcmp(fig->type, "plane") == 0)
		return (get_plane_intersection(fig, ray));
	return ((t_sol){INFINITY, INFINITY});
}

t_fig			*get_closest_fig(t_ray ray, t_fig *fig, double *closest_t)
{
	t_sol	sol;
	t_fig	*closest_fig;

	closest_fig = NULL;

	while (fig)
	{
		sol = get_intersection(fig, ray);
		if (IN_RANGE(sol.t1, ray.t_min, ray.t_max) && sol.t1 < *closest_t)
		{
			*closest_t = sol.t1;
			closest_fig = fig;
		}
		if (IN_RANGE(sol.t2, ray.t_min, ray.t_max) && sol.t2 < *closest_t)
		{
			*closest_t = sol.t2;
			closest_fig = fig;
		}
		fig = fig->next;
	}
	return (closest_fig);
}

int				trace_ray(t_env *env, t_ray ray, int depth)
{
	t_fig		*closest_fig;
	double		closest_t;
	int			local_color;
	t_vector	r;
	int			refl_color;

	closest_t = INFINITY;
	closest_fig = get_closest_fig(ray, env->fig, &closest_t);
	if (closest_fig == NULL)
		return (env->color);
	ray.p = vsum(ray.o, vmult(closest_t, ray.d));
	ray.n = get_normal(ray.p, closest_fig);
	local_color = get_fig_point_color(closest_fig, ray, env);
	if (depth <= 0 || closest_fig->refl == 0.0)
		return (local_color);
	r = vrefl(vmult(-1, ray.d), ray.n);
	refl_color = trace_ray(env,
		(t_ray){ray.p, r, (t_vector){0.0, 0.0, 0.0},
		(t_vector){0.0, 0.0, 0.0}, 0.001, INFINITY}, depth - 1);
	return (change_brightness(local_color, 1.0 - closest_fig->refl) +
			change_brightness(refl_color, closest_fig->refl));
}
