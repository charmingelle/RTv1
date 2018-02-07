/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:10:17 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/01 19:50:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*result_copy;
	int		result_len;

	result_len = 0;
	if (s1)
		result_len += ft_strlen(s1);
	if (s2)
		result_len += ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (result == NULL)
		return (NULL);
	result_copy = result;
	if (s1)
		while (*s1)
			*result++ = *s1++;
	if (s2)
		while (*s2)
			*result++ = *s2++;
	*result = 0;
	return (result_copy);
}
