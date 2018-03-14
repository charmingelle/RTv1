/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 17:04:33 by grevenko         ###   ########.fr       */
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

int			get_fig_point_color(t_fig *fig, t_vector p, t_vector n, t_env *env)
{
	return (change_brightness(fig->color, get_light(p, n, fig, env)));
}
