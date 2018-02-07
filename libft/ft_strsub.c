/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:50:32 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 12:35:57 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *s_copy;
	char *result;
	char *result_start;

	if (s)
	{
		s_copy = (char *)s;
		result = (char *)malloc(sizeof(char) * (len + 1));
		if (result == 0)
			return (0);
		result_start = result;
		while (len-- > 0)
		{
			*result++ = *(s_copy + start);
			s_copy++;
		}
		*result = 0;
		return (result_start);
	}
	else
		return (0);
}
