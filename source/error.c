/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/21 13:24:58 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	show_usage_error(void)
{
	ft_putstr_fd("usage: ./RTv1 scene_file\n", 2);
	return (1);
}

int	show_file_not_found_error(void)
{
	ft_putstr_fd("File not found\n", 2);
	return (1);
}

int	show_invalid_color_error(void)
{
	ft_putstr_fd("The scene contains an invalid color\n", 2);
	return (1);
}

int	show_invalid_property_error(void)
{
	ft_putstr_fd("The scene contains an invalid property\n", 2);
	return (1);
}

int	show_invalid_value_error(void)
{
	ft_putstr_fd("The scene contains an invalid value\n", 2);
	return (1);
}
