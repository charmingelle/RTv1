/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:15:42 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/06 13:16:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a && *b && n)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*a - *b);
}
