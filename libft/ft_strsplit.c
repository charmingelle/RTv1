/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:59:14 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 13:01:02 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int words;
	int i;

	if (!s)
		return (0);
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			words++;
		i++;
	}
	return (words);
}

static int	copy_word(char **result, char *source, char c)
{
	int word_len;
	int	word_len_copy;
	int	i;

	word_len = 0;
	while (source[word_len] && source[word_len] != c)
		word_len++;
	if (!(*result = (char *)malloc(word_len + 1)))
		return (0);
	word_len_copy = word_len;
	i = 0;
	while (word_len-- > 0)
		(*result)[i++] = *source++;
	(*result)[i] = 0;
	return (word_len_copy);
}

static void	free_copied_strings(char **result, int word_it)
{
	while (word_it--)
		free(*result++);
	free(result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**result;
	char	*s_copy;
	int		word_it;
	int		copy_result;

	result = (char **)malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (!s || result == 0)
		return (0);
	s_copy = (char *)s;
	word_it = 0;
	while (*s_copy)
		if (*s_copy == c)
			s_copy++;
		else
		{
			copy_result = copy_word(&result[word_it++], s_copy, c);
			if (!copy_result)
			{
				free_copied_strings(result, word_it);
				return (0);
			}
			s_copy += copy_result;
		}
	result[word_it] = 0;
	return (result);
}
