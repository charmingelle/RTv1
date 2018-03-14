/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:58:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_vector	get_canvas_vect(t_env *env, int x, int y)
{
	return (vrot((t_vector){x - env->size / 2, env->size / 2 - y, env->size},
		env));
}

static void		draw_scene(t_env *env)
{
	int			x;
	int			y;
	int			color;
	t_vector	d;

	x = -1;
	while (++x < env->size)
	{
		y = -1;
		while (++y < env->size)
		{
			d = get_canvas_vect(env, x, y);
			color = trace_ray(env, (t_ray){env->camera, d, 0.0, INFINITY},
				DEPTH);
			mlx_pixel_put(env->mlx, env->window, x, y, color);
		}
	}
}

void			redraw_scene(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	draw_scene(env);
}

int				main(int amount, char **args)
{
	t_env	*env;
	int		fd;

	if (amount != 2)
		exit(show_usage_error());
	fd = open(args[1], O_RDONLY);
	if (fd < 0)
		exit(show_file_not_found_error());
	env = get_env(fd);
	draw_scene(env);
	mlx_key_hook(env->window, &handle_keypress, env);
	mlx_loop(env->mlx);
	return (0);
}
