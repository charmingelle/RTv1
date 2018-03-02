/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/01 18:04:32 by grevenko         ###   ########.fr       */
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

t_t1t2	*get_sphere_intersections(t_fig sphere, t_vector o, t_vector d)
{
	t_vector	vector;
	double	a;
	double	b;
	double	c;

	vector = get_vect(sphere.center, o);
	a = get_scal_prod(d, d);
	b = 2 * get_scal_prod(vector, d);
	c = get_scal_prod(vector, vector) - sphere.rad * sphere.rad;
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_plane_intersections(t_fig fig, t_vector o, t_vector d)
{
	double	denom;
	t_t1t2	*intersections;

	denom = get_scal_prod(d, fig.normal);
	if (denom > 1e-6)
		return (NULL);
	intersections = (t_t1t2 *)malloc(sizeof(t_t1t2));
	intersections->t1 = get_scal_prod(get_diff(fig.center, o), fig.normal)
		/ get_scal_prod(d, fig.normal);
	intersections->t2 = intersections->t1;
	return (intersections);
}

t_t1t2	*get_intersections(t_fig fig, t_vector o, t_vector d)
{
	if (ft_strcmp(fig.type, "sphere") == 0)
		return (get_sphere_intersections(fig, o, d));
	if (ft_strcmp(fig.type, "cylinder") == 0)
		return (get_cyl_intersections(fig, o, d));
	if (ft_strcmp(fig.type, "cone") == 0)
		return (get_cone_intersections(fig, o, d));
	if (ft_strcmp(fig.type, "plane") == 0)
		return (get_plane_intersections(fig, o, d));
	return (NULL);
}

int		get_closest_fig_num(t_env *env, double *closest_t, t_vector o, t_vector d)
{
	t_t1t2	*intersections;	
	int		closest_fig_num;
	int		fig_num;

	closest_fig_num = -1;
	fig_num = -1;
	while (++fig_num < env->fig_amount)
	{
		intersections = get_intersections(env->figs[fig_num], o, d);
		if (intersections)
		{
			if (intersections->t1 < *closest_t)
			{
				*closest_t = intersections->t1;
				closest_fig_num = fig_num;
			}
			if (intersections->t2 < *closest_t)
			{
				*closest_t = intersections->t2;
				closest_fig_num = fig_num;
			}
			free(intersections);
		}
	}
	return (closest_fig_num);
}

int		trace_ray(t_env *env, t_vector point)
{
	int			closest_fig_num;
	double		closest_t;
	t_vector	fig_point;

	closest_t = INFINITY;
	closest_fig_num = get_closest_fig_num(env, &closest_t, env->camera, point);
	if (closest_fig_num == -1 || closest_t < 1.0)
		return (env->color);
	fig_point = get_sum(env->camera, get_num_prod(closest_t, point));
	return (get_fig_point_color(env, env->figs[closest_fig_num], fig_point));
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

	env->fig_amount = 7;
	env->figs = (t_fig *)malloc(sizeof(t_fig) * env->fig_amount);

	env->figs[0].type = "sphere";
	env->figs[0].center = (t_vector){-150, -100, DISTANCE + 150};
	env->figs[0].rad = 100;
	env->figs[0].color = 0x679327;

	env->figs[1].type = "sphere";
	env->figs[1].center = (t_vector){150, -100, DISTANCE + 250};
	env->figs[1].rad = 150;
	env->figs[1].color = 0xFFEF00;

	env->figs[2].type = "sphere";
	env->figs[2].center = (t_vector){0, 100, DISTANCE + 600};
	env->figs[2].rad = 150;
	env->figs[2].color = 0x0B6623;

	env->figs[3].type = "cylinder";
	env->figs[3].center = (t_vector){-400, 0, DISTANCE + 600};
	env->figs[3].center2 = (t_vector){-300, 300, DISTANCE + 600};
	env->figs[3].rad = 50;
	env->figs[3].color = 0xD8C077;

	env->figs[4].type = "cylinder";
	env->figs[4].center = (t_vector){200, 400, DISTANCE + 900};
	env->figs[4].center2 = (t_vector){300, 0, DISTANCE + 900};
	env->figs[4].rad = 70;
	env->figs[4].color = 0x3A1B0F;

	env->figs[5].type = "cylinder";
	env->figs[5].center = (t_vector){0, 400, DISTANCE + 1500};
	env->figs[5].center2 = (t_vector){0, 0, DISTANCE + 1500};
	env->figs[5].rad = 50;
	env->figs[5].color = 0xFFFCCC;

	env->figs[6].type = "plane";
	env->figs[6].center = (t_vector){0, -200, DISTANCE};
	env->figs[6].normal = (t_vector){0, 5, -1};
	env->figs[6].color = 0xAADA64;

	// env->figs[3].type = "cone";
	// env->figs[3].center = (t_vector){0, 0, DISTANCE};
	// env->figs[3].center2 = (t_vector){0, -50, DISTANCE};
	// env->figs[3].rad = 50;
	// env->figs[3].rad2 = 100;
	// env->figs[3].color = BLUE;

	env->ambient_light.intensity = 0.2;

	env->point_light.intensity = 0.4;
	env->point_light.pos = (t_vector){-350, 350, DISTANCE};

	env->dir_light.intensity = 0.4;
	env->dir_light.dir = (t_vector){-1, -2, 0};

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
