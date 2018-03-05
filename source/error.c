/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 14:32:20 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/01 17:36:07 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int show_usage_error()
{
	ft_putstr_fd("usage: ./RTv1 scene_file\n", 2);
	return (1);
}

int	show_file_not_found_error()
{
	ft_putstr_fd("File not found\n", 2);
	return (1);
}

int	show_invalid_color_error()
{
	ft_putstr_fd("Invalid color in the scene\n", 2);
	return (1);
}

int	show_invalid_property_error()
{
	ft_putstr_fd("The scene contains an invalid property\n", 2);
	return (1);
}

int	show_invalid_vector_error()
{
	ft_putstr_fd("The scene contains an invalid vector\n", 2);
	return (1);
}

int	show_invalid_property_value_error()
{
	ft_putstr_fd("The scene contains an invalid property-value pair\n", 2);
	return (1);
}

int	show_invalid_light_error()
{
	ft_putstr_fd("The scene contains an invalid light type\n", 2);
	return (1);
}

int	show_invalid_fig_error()
{
	ft_putstr_fd("The scene contains an invalid fig type\n", 2);
	return (1);
}
