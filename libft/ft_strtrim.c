/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:57:51 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 13:01:34 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space_symbol(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static int		find_start(char *s)
{
	int start;

	start = 0;
	while (*s && is_space_symbol(*s++))
		start++;
	return (start);
}

static int		find_end(char *s)
{
	int end;

	end = ft_strlen(s) - 1;
	s = s + ft_strlen(s) - 1;
	while (end >= 0 && is_space_symbol(*s--))
		end--;
	return (end + 1);
}

static char		*get_empty_string(void)
{
	char *result;

	result = (char *)malloc(1);
	*result = 0;
	return (result);
}

char			*ft_strtrim(char const *s)
{
	char	*s_copy;
	int		start;
	int		end;
	char	*result;
	char	*result_start;

	if (!s)
		return (0);
	s_copy = (char *)s;
	start = find_start(s_copy);
	if (start == (int)ft_strlen(s_copy))
		return (get_empty_string());
	end = find_end(s_copy);
	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (result == 0)
		return (0);
	result_start = result;
	s_copy = (char *)s + start;
	while (start++ < end)
		*result++ = *s_copy++;
	*result = 0;
	return (result_start);
}
