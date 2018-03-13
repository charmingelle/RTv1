/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 18:24:54 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/13 13:49:07 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector	vsum(t_vector A, t_vector B)
{
	return ((t_vector){A.x + B.x, A.y + B.y, A.z + B.z});
}

t_vector	vdiff(t_vector A, t_vector B)
{
	return ((t_vector){A.x - B.x, A.y - B.y, A.z - B.z});
}

t_vector	vmult(double num, t_vector A)
{
	return ((t_vector){num * A.x, num * A.y, num * A.z});
}

double		vscal(t_vector A, t_vector B)
{
	return (A.x * B.x + A.y * B.y + A.z * B.z);
}

double		vsquare(t_vector A)
{
	return (vscal(A, A));
}

double		vlen(t_vector A)
{
	return (sqrt(A.x * A.x + A.y * A.y + A.z * A.z));
}

t_vector	vort(t_vector A)
{
	double		len;

	len = vlen(A);
	return ((t_vector){A.x / len, A.y / len, A.z / len});
}

t_vector	vmid(t_vector A, t_vector B)
{
	return ((t_vector){(A.x + B.x) / 2, (A.y + B.y) / 2, (A.z + B.z) / 2});
}

t_vector	vrefl(t_vector L, t_vector N)
{
	return (vdiff(vmult(2 * vscal(N, L), N), L));
}

t_vector	vrot(t_vector A, t_env *env)
{
	t_vector	B;
	t_vector	C;
	t_vector	D;

	B = (t_vector){
			A.x,
			A.y * cos(get_rad(env->angle.x)) + A.z * sin(get_rad(env->angle.x)),
			A.z * cos(get_rad(env->angle.x)) - A.y * sin(get_rad(env->angle.x))};
	C = (t_vector){
			B.x * cos(get_rad(env->angle.y)) - B.z * sin(get_rad(env->angle.y)),
			B.y,
			B.z * cos(get_rad(env->angle.y)) + B.x * sin(get_rad(env->angle.y))};
	D = (t_vector){
			C.x * cos(get_rad(env->angle.z)) + C.y * sin(get_rad(env->angle.z)),
			C.y * cos(get_rad(env->angle.z)) - C.x * sin(get_rad(env->angle.z)),
			C.z};
	return (D);
}
