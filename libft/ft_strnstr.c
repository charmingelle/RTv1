/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:28:19 by grevenko          #+#    #+#             */
/*   Updated: 2017/10/30 13:52:30 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t start;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		start = i;
		j = 0;
		while (haystack[i] && (i < len) && needle[j]
			&& haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
			return ((char *)&haystack[start]);
		i = start + 1;
	}
	return (0);
}
