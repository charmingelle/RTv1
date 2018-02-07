/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:36:05 by grevenko          #+#    #+#             */
/*   Updated: 2017/10/27 19:36:40 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *dst_copy;

	dst_copy = dst;
	while (*src && len)
	{
		*dst++ = *src++;
		len--;
	}
	while (len--)
		*dst++ = 0;
	return (dst_copy);
}
