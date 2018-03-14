/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:59:33 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	show_invalid_vector_error(void)
{
	ft_putstr_fd("The scene contains an invalid vector\n", 2);
	return (1);
}

int	show_invalid_property_value_error(void)
{
	ft_putstr_fd("The scene contains an invalid property-value pair\n", 2);
	return (1);
}

int	show_invalid_light_error(void)
{
	ft_putstr_fd("The scene contains an invalid light type\n", 2);
	return (1);
}

int	show_invalid_fig_error(void)
{
	ft_putstr_fd("The scene contains an invalid fig type\n", 2);
	return (1);
}
