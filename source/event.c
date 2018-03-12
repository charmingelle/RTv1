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
	int	redraw;

	if (keycode == ESC)
	{
		mlx_destroy_window(env->mlx, env->window);
		exit(0);
	}
	redraw = 1;
	keycode == UP && (redraw = 1) ? env->camera.z += 10.0 : 0;
	keycode == DOWN && (redraw = 1) ? env->camera.z -= 10.0 : 0;
	keycode == LEFT && (redraw = 1) ? env->camera.x -= 10.0 : 0;
	keycode == RIGHT && (redraw = 1) ? env->camera.x += 10.0 : 0;
	keycode == PLUS && (redraw = 1) ? env->camera.y += 10.0 : 0;
	keycode == MINUS && (redraw = 1) ? env->camera.y -= 10.0 : 0;
	keycode == WW && (redraw = 1) ? env->ang_y = (env->ang_y + 5) % 360 : 0;
	keycode == SS && (redraw = 1) ? env->ang_y = (env->ang_y - 5) % 360 : 0;
	keycode == AA && (redraw = 1) ? env->ang_x = (env->ang_x - 5) % 360 : 0;
	keycode == DD && (redraw = 1) ? env->ang_x = (env->ang_x + 5) % 360 : 0;
	keycode == QQ && (redraw = 1) ? env->ang_z = (env->ang_z - 15) % 360 : 0;
	keycode == EE && (redraw = 1) ? env->ang_z = (env->ang_z + 15) % 360 : 0;
	redraw ? redraw_scene(env) : 0;
	return (0);
}
