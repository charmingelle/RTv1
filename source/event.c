/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:06:53 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/07 15:21:16 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_keypress(int keycode, t_env *env)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(env->mlx, env->window);
		exit(0);
	}
	return (0);
}
