/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:24:54 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:37:56 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double		vlen(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector	vort(t_vector a)
{
	double		len;

	len = vlen(a);
	return ((t_vector){a.x / len, a.y / len, a.z / len});
}

t_vector	vmid(t_vector a, t_vector b)
{
	return ((t_vector){(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2});
}

t_vector	vrefl(t_vector l, t_vector n)
{
	return (vdiff(vmult(2 * vscal(n, l), n), l));
}

t_vector	vrot(t_vector a, t_env *env)
{
	t_vector	b;
	t_vector	c;
	t_vector	d;

	b = (t_vector){
		a.x,
		a.y * cos(get_rad(env->angle.x)) + a.z * sin(get_rad(env->angle.x)),
		a.z * cos(get_rad(env->angle.x)) - a.y * sin(get_rad(env->angle.x))};
	c = (t_vector){
		b.x * cos(get_rad(env->angle.y)) - b.z * sin(get_rad(env->angle.y)),
		b.y,
		b.z * cos(get_rad(env->angle.y)) + b.x * sin(get_rad(env->angle.y))};
	d = (t_vector){
		c.x * cos(get_rad(env->angle.z)) + c.y * sin(get_rad(env->angle.z)),
		c.y * cos(get_rad(env->angle.z)) - c.x * sin(get_rad(env->angle.z)),
		c.z};
	return (d);
}
