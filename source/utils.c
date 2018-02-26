/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:33:11 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_t1t2	*get_quadratic_solution(double a, double b, double c)
{
	double	discrim;
	t_t1t2	*intersections;

	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (NULL);
	intersections = (t_t1t2 *)malloc(sizeof(t_t1t2));
	intersections->t1 = (-b + sqrt(discrim)) / (2 * a);
	intersections->t2 = (-b - sqrt(discrim)) / (2 * a);
	return (intersections);
}
