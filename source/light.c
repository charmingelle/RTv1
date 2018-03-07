/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:38:52 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/06 18:42:52 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		is_in_shadow(t_vector P, t_vector L, t_fig *fig)
{
	double	closest_t;

	closest_t = INFINITY;
	// if (get_closest_fig(fig, &closest_t, P, L) != NULL && closest_t < -1.0)
	// 	return (1);
	if (get_closest_fig(fig, &closest_t, -INFINITY, -1.001, P, L) != NULL)
		return (1);
	return (0);
}

double	get_shine(t_vector P, t_vector N, t_vector L)
{
	t_vector	R;
	t_vector	V;
	double		R_scal_V;

	R = vort(vrefl(L, N));
	V = vort(P);
	R_scal_V = vscal(R, V);
	if (R_scal_V > 0.0)
		return(R_scal_V);
	return (0.0);
}

double	get_point_light(t_vector P, t_vector N, t_light *light, t_fig *fig, t_fig *fig_list)
{
	t_vector	L;
	double		N_scal_L;
	double		point_light;

	L = vort(vdiff(P, light->pos));
	if (is_in_shadow(P, L, fig_list))
		return (0.0);
	N_scal_L = vscal(N, L);
	if (N_scal_L > 0.0)
	{
		point_light = light->intensity * N_scal_L;
		if (point_light > light->intensity)
			point_light = light->intensity;
		if (fig->shine != -1)
			point_light += light->intensity * pow(get_shine(P, N, L), fig->shine);
		return (point_light);
	}
	return (0.0);
}

double	get_dir_light(t_vector P, t_vector N, t_light *light, t_fig *fig, t_fig *fig_list)
{
	t_vector	L;
	double		closest_t;
	double		N_scal_L;
	double		dir_light;

	L = vort(light->dir);
	closest_t = INFINITY;
	if (is_in_shadow(P, L, fig_list))
		return (0.0);
	N_scal_L = vscal(N, L);
	if (N_scal_L > 0.0)
	{
		dir_light = light->intensity * N_scal_L;
		if (dir_light > light->intensity)
			dir_light = light->intensity;
		if (fig->shine != -1)
			dir_light += light->intensity * pow(get_shine(P, N, L), fig->shine);
		return (dir_light);
	}
	return (0.0);
}

double	get_light(t_vector P, t_vector N, t_fig *fig, t_env *env)
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
			total_light += get_point_light(P, N, light, fig, env->fig);
		else if (ft_strcmp(light->type, "dir") == 0)
			total_light += get_dir_light(P, N, light, fig, env->fig);
		light = light->next;
	}
	return (total_light);
}
