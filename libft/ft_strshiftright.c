/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshiftright.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:03:45 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/09 16:32:29 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshiftright(char *s)
{
	char	*shifted;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	shifted = (char *)malloc(sizeof(char) * (len + 1));
	shifted[0] = s[len - 1];
	i = 1;
	while (i < len)
	{
		shifted[i] = s[i - 1];
		i++;
	}
	shifted[len] = 0;
	return (shifted);
}
