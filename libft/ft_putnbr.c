/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:34:47 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/01 19:36:23 by grevenko         ###   ########.fr       */
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

void		ft_putnbr(int n)
{
	int		digit_amount;
	char	symbol;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	digit_amount = get_digit_amount(mod(n));
	if (n < 0)
	{
		ft_putchar('-');
		n = mod(n);
	}
	while (digit_amount > 0)
	{
		symbol = (n / power(10, digit_amount - 1)) + '0';
		ft_putchar(symbol);
		n %= power(10, digit_amount - 1);
		digit_amount--;
	}
}
