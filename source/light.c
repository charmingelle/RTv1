/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:38:52 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/01 17:55:59 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_in_shadow(t_env *env, t_vector point, t_vector ray)
{
	double	closest_t;

	closest_t = INFINITY;
	if (get_closest_fig_num(env, &closest_t, point, ray) != -1 && closest_t < -1.0)
		return (1);
	return (0);
}

double	get_ambient_light(t_env *env)
{
	return (env->ambient_light.intensity);
}

double	get_point_light(t_vector point, t_vector normal, t_env *env)
{
	t_vector	ray;
	double		scal_prod;
	double		point_light;

	ray = get_ort(get_vect(env->point_light.pos, point));
	if (is_in_shadow(env, point, ray))
		return (0.0);
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
	{
		point_light = env->point_light.intensity * scal_prod;
		if (point_light > env->point_light.intensity)
			return (env->point_light.intensity);
		return (point_light);
	}
	return (0.0);
}

double	get_dir_light(t_vector point, t_vector normal, t_env *env)
{
	t_vector	ray;
	double		closest_t;
	double		scal_prod;
	double		dir_light;

	ray = get_ort(env->dir_light.dir);
	closest_t = INFINITY;
	if (is_in_shadow(env, point, ray))
		return (0.0);
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
	{
		dir_light = env->dir_light.intensity * scal_prod;
		if (dir_light > env->dir_light.intensity)
			return (env->dir_light.intensity);
		return (dir_light);
	}
	return (0.0);
}

double	get_light(t_vector point, t_vector normal, t_env *env)
{
	double	light;

	light = get_ambient_light(env) + get_point_light(point, normal, env) + get_dir_light(point, normal, env);
	if (light < 1.0)
		return (light);
	return (1.0);
}
