/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:08:58 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 12:48:13 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n'));
}

int			ft_wordlen(char *s, int word_start)
{
	int len;

	len = 0;
	if (!s || !(word_start >= 0 && word_start < ft_strlen(s))
		|| is_space(s[word_start]))
		return (0);
	s += word_start;
	while (*s++)
		len++;
	return (len);
}
