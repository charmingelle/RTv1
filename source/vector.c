/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:24:54 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/06 18:40:06 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector	get_vect(t_vector start, t_vector end)
{
	t_vector	res;

	res.x = end.x - start.x;
	res.y = end.y - start.y;
	res.z = end.z - start.z;
	return (res);
}

t_vector	get_sum(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	get_diff(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vector	get_num_prod(double num, t_vector v)
{
	t_vector	res;

	res.x = num * v.x;
	res.y = num * v.y;
	res.z = num * v.z;
	return (res);
}

double		get_scal_prod(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		get_scal_square(t_vector vector)
{
	return (get_scal_prod(vector, vector));
}

double		get_len(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

t_vector	get_ort(t_vector vector)
{
	t_vector	res;
	double	len;

	len = get_len(vector);
	res.x = vector.x / len;
	res.y = vector.y / len;
	res.z = vector.z / len;
	return (res);
}

t_vector	get_refl_vect(t_vector vector, t_vector normal)
{
	return (get_diff(get_num_prod(2 * get_scal_prod(normal, vector), normal), vector));
}
