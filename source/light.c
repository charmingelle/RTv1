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

double	get_shine(t_vector point, t_vector normal, t_vector l)
{
	t_vector	r;
	t_vector	v;
	double		r_dot_v;

	r = get_ort(get_diff(get_num_prod(2 * get_scal_prod(normal, l), normal), l));
	v = get_ort(point);
	r_dot_v = get_scal_prod(r, v);
	if (r_dot_v > 0.0)
		return(r_dot_v);
	return (0.0);
}

double	get_point_light(t_vector point, t_vector normal, t_light *light, t_fig *fig, t_fig *fig_list)
{
	t_vector	l;
	double		normal_dot_l;
	double		point_light;

	l = get_ort(get_vect(light->pos, point));
	if (is_in_shadow(fig_list, point, l))
		return (0.0);
	normal_dot_l = get_scal_prod(normal, l);
	if (normal_dot_l > 0.0)
	{
		point_light = light->intensity * normal_dot_l;
		if (point_light > light->intensity)
			point_light = light->intensity;
		if (fig->shine != -1)
			point_light += light->intensity * pow(get_shine(point, normal, l), fig->shine);
		return (point_light);
	}
	return (0.0);
}

double	get_dir_light(t_vector point, t_vector normal, t_light *light, t_fig *fig, t_fig *fig_list)
{
	t_vector	l;
	double		closest_t;
	double		normal_dot_l;
	double		dir_light;

	l = get_ort(light->dir);
	closest_t = INFINITY;
	if (is_in_shadow(fig_list, point, l))
		return (0.0);
	normal_dot_l = get_scal_prod(normal, l);
	if (normal_dot_l > 0.0)
	{
		dir_light = light->intensity * normal_dot_l;
		if (dir_light > light->intensity)
			dir_light = light->intensity;
		if (fig->shine != -1)
			dir_light += light->intensity * pow(get_shine(point, normal, l), fig->shine);
		return (dir_light);
	}
	return (0.0);
}

double	get_light(t_vector point, t_vector normal, t_fig *fig, t_env *env)
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
			total_light += get_point_light(point, normal, light, fig, env->fig);
		else if (ft_strcmp(light->type, "dir") == 0)
			total_light += get_dir_light(point, normal, light, fig, env->fig);
		light = light->next;
	}
	return (total_light);
}
