/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:58:49 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/06 16:39:15 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	array_reverse(int *array, int start, int end)
{
	int i;
	int j;
	int temp;

	i = start;
	j = end - 1;
	while (i < j)
	{
		temp = array[i];
		array[i++] = array[j];
		array[j--] = temp;
	}
}

void		ft_array_rotate(int *array, int len, int steps)
{
	if (array)
	{
		if (ABS(steps) > len)
			steps = steps % len;
		if (steps < 0)
			steps = len - ABS(steps);
		array_reverse(array, 0, steps);
		array_reverse(array, steps, len);
		array_reverse(array, 0, len);
	}
}
