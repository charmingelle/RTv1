/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:38:02 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/10 12:52:30 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	mod(int n)
{
	return (n * ((n > 0) - (n < 0)));
}

static int	get_digit_amount(int n)
{
	int digit_amount;

	digit_amount = 1;
	while ((n / 10) > 0)
	{
		digit_amount++;
		n = n / 10;
	}
	return (digit_amount);
}

static int	power(int base, int power)
{
	int result;

	result = 1;
	while (power-- > 0)
		result *= base;
	return (result);
}

static char	*handle_smallest_negative(void)
{
	char *result;

	result = (char *)malloc(sizeof(char) * 12);
	ft_strcpy(result, "-2147483648");
	return (result);
}

char		*ft_itoa(int n)
{
	int		digit_amount;
	char	*result;
	char	*result_start;

	if (n == -2147483648)
		return (handle_smallest_negative());
	digit_amount = get_digit_amount(mod(n));
	result = (char *)malloc(sizeof(char) * (digit_amount + (n < 0) + 1));
	if (result == 0)
		return (0);
	result_start = result;
	if (n < 0)
	{
		*result++ = '-';
		n = mod(n);
	}
	while (digit_amount > 0)
	{
		*result++ = (n / power(10, digit_amount - 1)) + '0';
		n %= power(10, digit_amount - 1);
		digit_amount--;
	}
	*result = 0;
	return (result_start);
}
