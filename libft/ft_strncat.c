/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:59:18 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 13:00:03 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *start;

	start = s1;
	while (*s1)
		s1++;
	while (*s2 && n)
	{
		*s1++ = *s2++;
		n--;
	}
	*s1 = 0;
	return (start);
}
