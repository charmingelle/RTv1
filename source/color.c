/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/01 17:36:07 by grevenko         ###   ########.fr       */
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

	r = get_r(color) * coef;
	if (r > 0xFF)
		r = 0xFF;
	g = get_g(color) * coef;
	if (g > 0xFF)
		g = 0xFF;
	b = get_b(color) * coef;
	if (b > 0xFF)
		b = 0xFF;
	return (r * 0x10000 + g * 0x100 + b);
}

t_vector	get_cyl_normal(t_vector c1, t_vector c2, t_vector p)
{
	t_vector	axis;
	t_vector	c1_minus_p;

	axis = get_vect(c1, c2);
	c1_minus_p = get_diff(c1, p);
	return (get_diff(c1_minus_p,
		get_num_prod(get_scal_prod(c1_minus_p, axis) / get_scal_square(axis), axis)));
}

int			get_fig_point_color(t_fig *fig, t_vector point, t_env *env)
{
	t_vector		normal;

	if (ft_strcmp(fig->type, "sphere") == 0)
	{
		normal = get_ort(get_vect(point, fig->center));
		return (change_brightness(fig->color, get_light(point, normal, fig, env)));
	}
	if (ft_strcmp(fig->type, "cylinder") == 0)
	{
		normal = get_cyl_normal(fig->center, fig->center2, point);
		return (change_brightness(fig->color, get_light(point, normal, fig, env)));
	}
	if (ft_strcmp(fig->type, "plane") == 0)
		return (change_brightness(fig->color, get_light(point,
			get_num_prod(-1, fig->normal), fig, env)));
	return (fig->color);
}
