/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 18:03:12 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

double	get_plane_intersection(t_fig *fig, t_ray ray)
{
	double	denom;
	double	t;

	denom = vscal(fig->center2, ray.d);
	if (denom == 0.0)
		return (INFINITY);
	t = vscal(vdiff(fig->center, ray.o), fig->center2) / denom;
	if (t >= ray.t_min && t <= ray.t_max)
		return (t);
	return (INFINITY);
}
