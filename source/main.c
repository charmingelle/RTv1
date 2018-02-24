/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:33:11 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_point	get_centered_coords(t_env *env, int x, int y)
{
	t_point	c;

	c.x = x - WIDTH / 2;
	c.y = HEIGHT / 2 - y;
	c.z = env->distance;
	return (c);
}

t_2point	*get_cyl_intersections(t_env *env, t_point point)
{
	double		k1;
	double		k2;
	double		k3;
	double		discrim;
	t_2point	*intersection;
	t_point		axis_point;

	axis_point = get_vect_sum(get_vector(env->cyl.axis2, env->cyl.axis1), point);
	k1 = get_scalar_product(axis_point, axis_point);
	k2 = 2 * get_scalar_product(axis_point, env->camera);
	k3 = get_scalar_product(env->camera, env->camera) - env->cyl.rad * env->cyl.rad;
	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
		return (NULL);
	intersection = (t_2point *)malloc(sizeof(t_2point));
	intersection->x = (-k2 + sqrt(discrim)) / (2 * k1);
	intersection->y = (-k2 - sqrt(discrim)) / (2 * k1);
	return (intersection);
}

t_2point	*get_intersections(t_env *env, t_point point)
{
	t_point		vector;
	double		k1;
	double		k2;
	double		k3;
	double		discrim;
	t_2point	*intersection;

	vector = get_vector(env->sphere.center, env->camera);
	k1 = get_scalar_product(point, point);
	k2 = 2 * get_scalar_product(vector, point);
	k3 = get_scalar_product(vector, vector) - env->sphere.rad * env->sphere.rad;
	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
		return (NULL);
	intersection = (t_2point *)malloc(sizeof(t_2point));
	intersection->x = (-k2 + sqrt(discrim)) / (2 * k1);
	intersection->y = (-k2 - sqrt(discrim)) / (2 * k1);
	return (intersection);
}

// int		trace_ray(t_env *env, t_point point)
// {
// 	t_2point	*intersection;

// 	intersection = get_intersections(env, point);
// 	if (intersection)
// 	{
// 		free(intersection);
// 		return (env->sphere.color);
// 	}
// 	else
// 		return (env->color);
// }

int		trace_cyl_ray(t_env *env, t_point point)
{
	t_2point	*intersection;
	// t_point		normal;

	intersection = get_cyl_intersections(env, point);
	if (intersection)
	{
		free(intersection);
		// normal = get_ort(get_vector(point, env->sphere.center));
		// return (change_brightness(env->sphere.color, get_ambient_light(env)));
		// return (change_brightness(env->sphere.color, get_point_light(point, normal, env)));
		// return (change_brightness(env->sphere.color, get_dir_light(normal, env)));
		// return (change_brightness(env->sphere.color, get_light(point, normal, env)));
		return (env->cyl.color);
	}
	else
		return (env->color);
}

int		trace_ray(t_env *env, t_point point)
{
	t_2point	*intersection;
	t_point		normal;

	intersection = get_intersections(env, point);
	if (intersection)
	{
		free(intersection);
		normal = get_ort(get_vector(point, env->sphere.center));
		// return (change_brightness(env->sphere.color, get_ambient_light(env)));
		// return (change_brightness(env->sphere.color, get_point_light(point, normal, env)));
		// return (change_brightness(env->sphere.color, get_dir_light(normal, env)));
		return (change_brightness(env->sphere.color, get_light(point, normal, env)));
		// return (env->sphere.color);
	}
	else
		return (env->color);
}

void	draw_scene(t_env *env)
{
	int			x;
	int			y;
	t_point	point;
	int			color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			point = get_centered_coords(env, x, y);
			// color = trace_ray(env, point);
			color = trace_cyl_ray(env, point);
			mlx_pixel_put(env->mlx, env->window, x, y, color);
			y++;
		}
		x++;
	}
}

t_env	*init_env()
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->window = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");

	env->camera = (t_point){0, 0, 0};
	env->distance = DISTANCE;
	env->color = 0;

	env->sphere.center = (t_point){0, 0, DISTANCE + 150};
	env->sphere.rad = 300;
	env->sphere.color = RED;

	env->cyl.axis1 = (t_point){0, 0, DISTANCE + 150};
	env->cyl.axis2 = (t_point){100, 100, DISTANCE + 150};
	env->cyl.rad = 100;
	env->cyl.color = GREEN;

	env->ambient_light.intensity = 0.2;

	env->point_light.intensity = 0.4;
	env->point_light.pos = (t_point){500, 500, 1000};

	env->dir_light.intensity = 0.4;
	env->dir_light.dir = (t_point){-2, -1, 0};
	return (env);
}

int	main(void)
{
	t_env	*env;

	env = init_env();
	draw_scene(env);
	mlx_key_hook(env->window, &handle_keypress, env);
	mlx_loop(env->mlx);
	return (0);
}
