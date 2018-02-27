/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:38:52 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 19:45:05 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	get_ambient_light(t_env *env)
{
	return (env->ambient_light.intensity);
}

double	get_vector_light(t_vector point, t_vector normal, t_env *env)
{
	t_vector	ray;
	double	scal_prod;

	ray = get_ort(get_vect(point, env->point_light.pos));
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
		return (env->point_light.intensity * scal_prod);
	return (0.0);
}

double	get_dir_light(t_vector normal, t_env *env)
{
	t_vector	ray;
	double	scal_prod;

	ray = get_ort(env->dir_light.dir);
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
		return (env->dir_light.intensity * scal_prod);
	return (0.0);
}

double	get_light(t_vector point, t_vector normal, t_env *env)
{
	double	light;

	light = get_ambient_light(env) + get_vector_light(point, normal, env) + get_dir_light(normal, env);
	if (light < 1.0)
		return (light);
	return (1.0);
}
