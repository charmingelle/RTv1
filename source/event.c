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
	else if (keycode == UP)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.z += 10.0;
		draw_scene(env);
	}
	else if (keycode == DOWN)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.z -= 10.0;
		draw_scene(env);	
	}
	else if (keycode == LEFT)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.x -= 10.0;
		draw_scene(env);
	}
	else if (keycode == RIGHT)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.x += 10.0;
		draw_scene(env);
	}
	else if (keycode == PLUS)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.y += 10.0;
		draw_scene(env);
	}
	else if (keycode == MINUS)
	{
		mlx_clear_window(env->mlx, env->window);
		env->camera.y -= 10.0;
		draw_scene(env);
	}
	else if (keycode == WW)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_y = (env->ang_y + 5) % 360;
		draw_scene(env);
	}
	else if (keycode == SS)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_y = (env->ang_y - 5) % 360;
		draw_scene(env);
	}
	else if (keycode == AA)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_x = (env->ang_x - 5) % 360;
		draw_scene(env);
	}
	else if (keycode == DD)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_x = (env->ang_x + 5) % 360;
		draw_scene(env);
	}
	else if (keycode == QQ)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_z = (env->ang_z - 15) % 360;
		draw_scene(env);
	}
	else if (keycode == EE)
	{
		mlx_clear_window(env->mlx, env->window);
		env->ang_z = (env->ang_z + 15) % 360;
		draw_scene(env);
	}
	return (0);
}
