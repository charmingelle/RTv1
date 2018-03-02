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

int		is_in_shadow(t_fig *fig, t_vector point, t_vector ray)
{
	double	closest_t;

	closest_t = INFINITY;
	if (get_closest_fig(fig, &closest_t, point, ray) != NULL && closest_t < -1.0)
		return (1);
	return (0);
}

double	get_point_light(t_vector point, t_vector normal, t_light *light, t_fig *fig)
{
	t_vector	ray;
	double		scal_prod;
	double		point_light;

	ray = get_ort(get_vect(light->pos, point));
	if (is_in_shadow(fig, point, ray))
		return (0.0);
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
	{
		point_light = light->intensity * scal_prod;
		if (point_light > light->intensity)
			return (light->intensity);
		return (point_light);
	}
	return (0.0);
}

double	get_dir_light(t_vector point, t_vector normal, t_light *light, t_fig *fig)
{
	t_vector	ray;
	double		closest_t;
	double		scal_prod;
	double		dir_light;

	ray = get_ort(light->dir);
	closest_t = INFINITY;
	if (is_in_shadow(fig, point, ray))
		return (0.0);
	scal_prod = get_scal_prod(normal, ray);
	if (scal_prod > 0.0)
	{
		dir_light = light->intensity * scal_prod;
		if (dir_light > light->intensity)
			return (light->intensity);
		return (dir_light);
	}
	return (0.0);
}

double	get_light(t_vector point, t_vector normal, t_env *env)
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
			total_light += get_point_light(point, normal, light, env->fig);
		else if (ft_strcmp(light->type, "dir") == 0)
			total_light += get_dir_light(point, normal, light, env->fig);
		light = light->next;
	}
	if (total_light < 1.0)
		return (total_light);
	return (1.0);
}
