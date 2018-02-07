/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 12:44:56 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 13:01:23 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int start;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		start = i;
		j = 0;
		while (haystack[i] && needle[j] && haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
			return ((char *)&haystack[start]);
		i = start + 1;
	}
	return (0);
}
