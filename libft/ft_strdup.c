/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:49:48 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/06 13:00:40 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *copy;
	char *copy_start;

	copy = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (copy == 0)
		return (0);
	copy_start = copy;
	while (*s1)
		*copy++ = *s1++;
	*copy = 0;
	return (copy_start);
}
