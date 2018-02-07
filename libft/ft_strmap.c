/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 15:52:32 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 12:20:09 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *result;
	char *result_start;

	if (s && f)
	{
		result = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (result == 0)
			return (0);
		result_start = result;
		while (*s)
			*result++ = f(*s++);
		*result = 0;
		return (result_start);
	}
	else if (s && !f)
		return ((char *)s);
	else
		return (0);
}
