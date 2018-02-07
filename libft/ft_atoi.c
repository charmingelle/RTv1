/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:24:49 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 12:50:05 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*skip_spaces(char *str)
{
	while ((*str >= 9 && *str <= 14) || *str == ' ')
		str++;
	return (str);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	digit_from_char(char c)
{
	return (c - '0');
}

int			ft_atoi(const char *str)
{
	char			*copy;
	long long int	sign;
	long long int	result;
	int				digit_amount;

	copy = skip_spaces((char *)str);
	sign = 1;
	result = 0;
	digit_amount = 0;
	if (*copy == '+' || *copy == '-')
		if (*copy++ == '-')
			sign = -1;
	digit_amount = 0;
	while (is_digit(*copy))
	{
		result = result * 10 + digit_from_char(*copy++);
		if (result)
			digit_amount++;
		if (((digit_amount > 19) || (result < 0)) && (sign == -1))
			return (0);
		else if (((digit_amount > 19) || (result < 0)
			|| (!result && digit_amount)) && (sign == 1))
			return (-1);
	}
	return ((int)(result * sign));
}
