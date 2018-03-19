/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:38:52 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/19 22:01:26 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		is_in_shadow(t_vector p, t_vector l, t_fig *fig, double limit)
{
	double	closest_t;

	closest_t = INFINITY;
	if (get_closest_fig(&(t_ray){p, l, (t_vector){0.0, 0.0, 0.0},
		(t_vector){0.0, 0.0, 0.0}, 0.001, limit}, fig, &closest_t, NULL))
		return (1);
	return (0);
}

static double	get_shine(t_vector p, t_vector n, t_vector l)
{
	t_vector	r;
	t_vector	v;
	double		r_scal_v;

	r = vort(vrefl(l, n));
	v = vort(vmult(-1, p));
	r_scal_v = vscal(r, v);
	if (r_scal_v > 0.0)
		return (r_scal_v);
	return (0.0);
}

static double	get_point_light(t_ray ray, t_light *light,
	t_fig *fig, t_fig *fig_list)
{
	t_vector	l;
	double		n_scal_minus_d;
	double		n_scal_l;
	double		point_light;

	l = vort(vdiff(light->pos, ray.p));
	n_scal_minus_d = vscal(ray.n, vmult(-1, ray.d));
	n_scal_l = vscal(ray.n, l);
	if (n_scal_minus_d > 0.0 && n_scal_l > 0.0)
	{
		if (is_in_shadow(ray.p, vdiff(light->pos, ray.p), fig_list, 0.99))
			return (0.0);
		point_light = light->intensity * n_scal_l;
		if (point_light > light->intensity)
			point_light = light->intensity;
		if (fig->shine > 0)
			point_light += light->intensity
				* pow(get_shine(ray.p, ray.n, l), fig->shine);
		return (point_light);
	}
	return (0.0);
}

static double	get_dir_light(t_ray ray, t_light *light,
	t_fig *fig, t_fig *fig_list)
{
	t_vector	l;
	double		n_scal_minus_d;
	double		n_scal_l;
	double		dir_light;

	l = vort(vmult(-1, light->dir));
	n_scal_minus_d = vscal(ray.n, vmult(-1, ray.d));
	n_scal_l = vscal(ray.n, l);
	if (n_scal_minus_d > 0.0 && n_scal_l > 0.0)
	{
		if (is_in_shadow(ray.p, l, fig_list, INFINITY))
			return (0.0);
		dir_light = light->intensity * n_scal_l;
		if (dir_light > light->intensity)
			dir_light = light->intensity;
		if (fig->shine > 0)
			dir_light += light->intensity
				* pow(get_shine(ray.p, ray.n, l), fig->shine);
		return (dir_light);
	}
	return (0.0);
}

double			get_light(t_ray ray, t_fig *fig, t_env *env)
{
	double	total_light;
	t_light	*light;

	total_light = 0.0;
	light = env->light;
	while (light)
	{
		if (ft_strcmp(light->type, "ambient") == 0)
			total_light += light->intensity;
		else if (ft_strcmp(light->type, "point") == 0)
			total_light += get_point_light(ray, light, fig, env->fig);
		else if (ft_strcmp(light->type, "dir") == 0)
			total_light += get_dir_light(ray, light, fig, env->fig);
		light = light->next;
	}
	return (total_light);
}
