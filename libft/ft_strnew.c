/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 14:40:37 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/06 14:03:17 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *string;
	char *string_start;

	string = (char *)malloc(sizeof(char) * (size + 1));
	if (string == 0)
		return (0);
	string_start = string;
	while ((int)size-- >= 0)
		*string++ = 0;
	return (string_start);
}
