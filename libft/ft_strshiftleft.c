/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshiftleft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:27:11 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/09 16:32:23 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshiftleft(char *s)
{
	char	*shifted;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	shifted = (char *)malloc(sizeof(char) * (len + 1));
	shifted[len - 1] = s[0];
	i = len - 2;
	while (i >= 0)
	{
		shifted[i] = s[i + 1];
		i--;
	}
	shifted[len] = 0;
	return (shifted);
}
