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
