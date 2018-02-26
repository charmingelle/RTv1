/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:24:54 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:32:45 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_point	get_vect(t_point start, t_point end)
{
	t_point	res;

	res.x = end.x - start.x;
	res.y = end.y - start.y;
	res.z = end.z - start.z;
	return (res);
}

t_point	get_sum(t_point v1, t_point v2)
{
	t_point	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_point	get_diff(t_point v1, t_point v2)
{
	t_point	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_point	get_num_prod(double num, t_point v)
{
	t_point	res;

	res.x = num * v.x;
	res.y = num * v.y;
	res.z = num * v.z;
	return (res);
}

double	get_scal_prod(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	get_len(t_point vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

t_point	get_ort(t_point vector)
{
	t_point	res;
	double	len;

	len = get_len(vector);
	res.x = vector.x / len;
	res.y = vector.y / len;
	res.z = vector.z / len;
	return (res);
}