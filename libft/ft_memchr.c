/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:17:29 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 17:45:32 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *source;

	source = (unsigned char *)s;
	while (n && *source != (unsigned char)c)
	{
		n--;
		source++;
	}
	if (n != 0 && *source == (unsigned char)c)
		return (source);
	return (0);
}
