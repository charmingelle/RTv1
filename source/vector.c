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

t_vector	vsum(t_vector A, t_vector B)
{
	t_vector	sum;

	sum.x = A.x + B.x;
	sum.y = A.y + B.y;
	sum.z = A.z + B.z;
	return (sum);
}

t_vector	vdiff(t_vector A, t_vector B)
{
	t_vector	diff;

	diff.x = A.x - B.x;
	diff.y = A.y - B.y;
	diff.z = A.z - B.z;
	return (diff);
}

t_vector	vmult(double num, t_vector A)
{
	t_vector	mult;

	mult.x = num * A.x;
	mult.y = num * A.y;
	mult.z = num * A.z;
	return (mult);
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
	t_vector	ort;
	double		len;

	len = vlen(A);
	ort.x = A.x / len;
	ort.y = A.y / len;
	ort.z = A.z / len;
	return (ort);
}

t_vector	vrefl(t_vector L, t_vector N)
{
	return (vdiff(vmult(2 * vscal(N, L), N), L));
}

t_vector	vrotate(t_vector A, t_env *env)
{
	t_vector	B;
	t_vector	C;
	t_vector	D;

	B.x = A.x;
	B.y = A.y * cos(get_rad(env->ang_x))
		+ A.z * sin(get_rad(env->ang_x));
	B.z = A.z * cos(get_rad(env->ang_x))
		- A.y * sin(get_rad(env->ang_x));
	C.x = B.x * cos(get_rad(env->ang_y))
		- B.z * sin(get_rad(env->ang_y));
	C.y = B.y;
	C.z = B.z * cos(get_rad(env->ang_y))
		+ B.x * sin(get_rad(env->ang_y));
	D.x = C.x * cos(get_rad(env->ang_z))
		+ C.y * sin(get_rad(env->ang_z));
	D.y = C.y * cos(get_rad(env->ang_z))
		- C.x * sin(get_rad(env->ang_z));
	D.z = C.z;
	return (D);
}
