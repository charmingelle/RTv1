/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:14:09 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 12:54:13 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *source1;
	unsigned char *source2;

	source1 = (unsigned char *)s1;
	source2 = (unsigned char *)s2;
	while (n--)
		if (*source1++ != *source2++)
			return (*(source1 - 1) - *(source2 - 1));
	return (0);
}
