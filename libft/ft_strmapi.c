/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:23:08 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 12:21:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	char	*result_start;
	int		i;

	if (s && f)
	{
		result = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (result == 0)
			return (0);
		result_start = result;
		i = 0;
		while (*s)
			*result++ = f(i++, *s++);
		*result = 0;
		return (result_start);
	}
	else if (s && !f)
		return ((char *)s);
	else
		return (0);
}
