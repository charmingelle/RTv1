/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:17:42 by grevenko          #+#    #+#             */
/*   Updated: 2017/10/31 13:52:13 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_passed;
	size_t	source_len;

	dest_passed = 0;
	while (*dst && dstsize)
	{
		dst++;
		dstsize--;
		dest_passed++;
	}
	source_len = ft_strlen(src);
	if (dstsize == 0)
		return (dest_passed + source_len);
	while (*src && dstsize-- > 1)
		*dst++ = *src++;
	*dst = 0;
	return (dest_passed + source_len);
}
