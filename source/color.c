/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/21 14:35:22 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_r(int color)
{
	return (color / 0x10000);
}

static int	get_g(int color)
{
	return ((color - (color / 0x10000) * 0x10000) / 0x100);
}

static int	get_b(int color)
{
	return (color % 0x100);
}

int			change_brightness(int color, double coef)
{
	int		r;
	int		g;
	int		b;

	r = (int)(get_r(color) * coef) % 256;
	g = (int)(get_g(color) * coef) % 256;
	b = (int)(get_b(color) * coef) % 256;
	return (r * 0x10000 + g * 0x100 + b);
}

int			get_fig_point_color(t_env *env, t_fig fig, t_point point)
{
	t_point		normal;

	if (ft_strcmp(fig.type, "sphere") == 0)
	{
		normal = get_ort(get_vect(point, fig.center));
		// return (change_brightness(env->sphere.color, get_ambient_light(env)));
		// return (change_brightness(env->sphere.color, get_point_light(point, normal, env)));
		// return (change_brightness(env->sphere.color, get_dir_light(normal, env)));
		return (change_brightness(fig.color, get_light(point, normal, env)));
	}
	return (fig.color);
}
