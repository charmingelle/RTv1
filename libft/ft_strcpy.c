/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:57:06 by grevenko          #+#    #+#             */
/*   Updated: 2017/10/27 18:15:21 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char *dst_start;

	dst_start = dst;
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return (dst_start);
}
