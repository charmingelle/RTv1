/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:52:57 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 12:57:39 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (*a && *b)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (*a - *b);
}
