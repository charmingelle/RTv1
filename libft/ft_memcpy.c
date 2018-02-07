/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:53:49 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/06 13:33:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *destination;
	unsigned char *source;

	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	while (n--)
		*destination++ = *source++;
	return (dst);
}
