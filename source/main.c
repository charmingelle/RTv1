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

t_t1t2	*get_cyl_intersections(t_env *env, t_fig cyl, t_point point)
{
	t_point		p_a;
	t_point		v_a;
	t_point		delta;
	double		scal_prod_v_v_a;
	double		scal_prod_delta_v_a;
	double		a;
	double		b;
	double		c;

	p_a = cyl.axis1;
	v_a = get_vect(cyl.axis1, cyl.axis2);
	delta = get_diff(env->camera, p_a);
	scal_prod_v_v_a = get_scal_prod(point, v_a);
	scal_prod_delta_v_a = get_scal_prod(delta, v_a);
	a = get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)));
	b = 2 * get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)));
	c = get_scal_prod(get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a))) - pow(cyl.rad, 2);
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_sphere_intersections(t_env *env, t_fig sphere, t_point point)
{
	t_point		vector;
	double		a;
	double		b;
	double		c;

	vector = get_vect(sphere.center, env->camera);
	a = get_scal_prod(point, point);
	b = 2 * get_scal_prod(vector, point);
	c = get_scal_prod(vector, vector) - sphere.rad * sphere.rad;
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_intersections(t_env *env, t_fig fig, t_point point)
{
	if (ft_strcmp(fig.type, "sphere") == 0)
		return (get_sphere_intersections(env, fig, point));
	if (ft_strcmp(fig.type, "cylinder") == 0)
		return (get_cyl_intersections(env, fig, point));
	return (NULL);
}

int		trace_ray(t_env *env, t_point point)
{
	t_t1t2	*intersections;
	double		closest_t;
	int			closest_fig_num;
	int			fig_num;

	closest_t = INFINITY;
	closest_fig_num = -1;
	fig_num = -1;
	while (++fig_num < env->fig_amount)
	{
		intersections = get_intersections(env, env->figs[fig_num], point);
		if (intersections)
		{
			if (closest_t == INFINITY || intersections->t1 < closest_t)
			{
				closest_t = intersections->t1;
				closest_fig_num = fig_num;
			}
			if (closest_t == INFINITY || intersections->t2 < closest_t)
			{
				closest_t = intersections->t2;
				closest_fig_num = fig_num;
			}
			free(intersections);
		}
	}
	if (closest_fig_num == -1)
		return (env->color);
	return (get_fig_point_color(env, env->figs[closest_fig_num], point));
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
			color = trace_ray(env, point);
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

	env->fig_amount = 2;
	env->figs = (t_fig *)malloc(sizeof(t_fig) * env->fig_amount);

	env->figs[0].type = "sphere";
	env->figs[0].center = (t_point){0, 0, DISTANCE + 150};
	env->figs[0].rad = 300;
	env->figs[0].color = RED;

	env->figs[1].type = "cylinder";
	env->figs[1].axis1 = (t_point){0, 0, DISTANCE + 150};
	env->figs[1].axis2 = (t_point){100, 100, DISTANCE + 200};
	env->figs[1].rad = 500;
	env->figs[1].color = GREEN;

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
