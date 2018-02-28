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

t_vector	get_centered_coords(t_env *env, int x, int y)
{
	t_vector	c;

	c.x = x - WIDTH / 2;
	c.y = HEIGHT / 2 - y;
	c.z = env->distance;
	return (c);
}

t_t1t2	*get_sphere_intersections(t_env *env, t_fig sphere, t_vector point)
{
	t_vector	vector;
	double	a;
	double	b;
	double	c;

	vector = get_vect(sphere.center, env->camera);
	a = get_scal_prod(point, point);
	b = 2 * get_scal_prod(vector, point);
	c = get_scal_prod(vector, vector) - sphere.rad * sphere.rad;
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_plane_intersections(t_env *env, t_fig fig, t_vector point)
{
	double	denom;
	t_t1t2	*intersections;

	denom = get_scal_prod(point, fig.normal);
	if (denom > 1e-6)
		return (NULL);
	intersections = (t_t1t2 *)malloc(sizeof(t_t1t2));
	intersections->t1 = get_scal_prod(get_diff(fig.center, env->camera), fig.normal)
		/ get_scal_prod(point, fig.normal);
	intersections->t2 = intersections->t1;
	return (intersections);
}

t_t1t2	*get_intersections(t_env *env, t_fig fig, t_vector point)
{
	if (ft_strcmp(fig.type, "sphere") == 0)
		return (get_sphere_intersections(env, fig, point));
	if (ft_strcmp(fig.type, "cylinder") == 0)
		return (get_cyl_intersections(env, fig, point));
	if (ft_strcmp(fig.type, "cone") == 0)
		return (get_cone_intersections(env, fig, point));
	if (ft_strcmp(fig.type, "plane") == 0)
		return (get_plane_intersections(env, fig, point));
	return (NULL);
}

int		trace_ray(t_env *env, t_vector point)
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
			if (closest_t == INFINITY || (intersections->t1 > 0 && intersections->t1 < closest_t) )
			{
				closest_t = intersections->t1;
				closest_fig_num = fig_num;
			}
			if (closest_t == INFINITY || (intersections->t2 > 0 && intersections->t2 < closest_t) )
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
	t_vector	point;
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

	env->camera = (t_vector){0, 0, 0};
	env->distance = DISTANCE;
	env->color = 0;

	env->fig_amount = 6;
	env->figs = (t_fig *)malloc(sizeof(t_fig) * env->fig_amount);

	env->figs[0].type = "sphere";
	env->figs[0].center = (t_vector){-150, -100, DISTANCE + 150};
	env->figs[0].rad = 100;
	env->figs[0].color = 0x679327;

	env->figs[1].type = "sphere";
	env->figs[1].center = (t_vector){150, -100, DISTANCE + 75};
	env->figs[1].rad = 150;
	env->figs[1].color = 0xFFEF00;

	env->figs[2].type = "cylinder";
	env->figs[2].center = (t_vector){-400, 0, DISTANCE + 600};
	env->figs[2].center2 = (t_vector){-300, 300, DISTANCE + 600};
	env->figs[2].rad = 50;
	env->figs[2].color = 0xD8C077;

	env->figs[3].type = "cylinder";
	env->figs[3].center = (t_vector){200, 400, DISTANCE + 900};
	env->figs[3].center2 = (t_vector){300, 0, DISTANCE + 900};
	env->figs[3].rad = 70;
	env->figs[3].color = 0x3A1B0F;

	env->figs[4].type = "cylinder";
	env->figs[4].center = (t_vector){0, 400, DISTANCE + 1500};
	env->figs[4].center2 = (t_vector){0, 0, DISTANCE + 1500};
	env->figs[4].rad = 100;
	env->figs[4].color = 0x3A1B0F;

	env->figs[5].type = "plane";
	env->figs[5].center = (t_vector){0, -200, DISTANCE};
	env->figs[5].normal = (t_vector){0, 5, -1};
	env->figs[5].color = 0xAADA64;

	// env->figs[3].type = "cone";
	// env->figs[3].center = (t_vector){0, 0, DISTANCE};
	// env->figs[3].center2 = (t_vector){0, -50, DISTANCE};
	// env->figs[3].rad = 50;
	// env->figs[3].rad2 = 100;
	// env->figs[3].color = BLUE;

	env->ambient_light.intensity = 0.1;

	env->point_light.intensity = 0.6;
	env->point_light.pos = (t_vector){-300, 100, DISTANCE};

	env->dir_light.intensity = 0.3;
	env->dir_light.dir = (t_vector){-2, -1, 0};

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
