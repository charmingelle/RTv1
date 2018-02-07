/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:40:50 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 12:31:38 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 && s2)
	{
		while (*s1 && *s2 && n)
		{
			if (*s1++ != *s2++)
				return (0);
			n--;
		}
		if (n == 0 || (*s1 == *s2))
			return (1);
		return (0);
	}
	else if ((!s1 && s2 && n) || (s1 && !s2 && n))
		return (0);
	else
		return (1);
}
