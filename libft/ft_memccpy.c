/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:50:38 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/03 22:05:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
	int c, size_t n)
{
	unsigned char *source;
	unsigned char *destination;

	source = (unsigned char *)src;
	destination = (unsigned char *)dst;
	while (n && *source != (unsigned char)c)
	{
		*destination++ = *source++;
		n--;
	}
	if (n && *source == (unsigned char)c)
	{
		*destination++ = *source;
		return ((void *)destination);
	}
	return (0);
}
