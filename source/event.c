/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:06:53 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/15 15:15:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	handle_keypress(int keycode, t_env *env)
{
	int	redraw;

	keycode == ESC ? exit(0) : 0;
	redraw = 0;
	keycode == UP && ++redraw ? env->camera.y += 10.0 : 0;
	keycode == DOWN && ++redraw ? env->camera.y -= 10.0 : 0;
	keycode == LEFT && ++redraw ? env->camera.x -= 10.0 : 0;
	keycode == RIGHT && ++redraw ? env->camera.x += 10.0 : 0;
	keycode == PLUS && ++redraw ? env->camera.z += 10.0 : 0;
	keycode == MINUS && ++redraw ? env->camera.z -= 10.0 : 0;
	keycode == S && ++redraw ? env->angle.x = ((int)env->angle.x - 5) % 360 : 0;
	keycode == W && ++redraw ? env->angle.x = ((int)env->angle.x + 5) % 360 : 0;
	keycode == A && ++redraw ? env->angle.y = ((int)env->angle.y + 5) % 360 : 0;
	keycode == D && ++redraw ? env->angle.y = ((int)env->angle.y - 5) % 360 : 0;
	keycode == Q && ++redraw ? env->angle.z = ((int)env->angle.z - 5) % 360 : 0;
	keycode == E && ++redraw ? env->angle.z = ((int)env->angle.z + 5) % 360 : 0;
	redraw ? redraw_scene(env) : 0;
	return (0);
}
