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

double	get_cyl_a(t_vector point, double scal_prod_v_v_a, t_vector v_a)
{
	return (get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(point, get_num_prod(scal_prod_v_v_a, v_a))));
}

double	get_cyl_b(t_vector point, t_vector delta,
	double scal_prod_v_v_a, t_vector v_a, double scal_prod_delta_v_a)
{
	return (2 * get_scal_prod(get_diff(point, get_num_prod(scal_prod_v_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a))));
}

double	get_cyl_c(t_vector delta, double scal_prod_delta_v_a, t_vector v_a, double rad)
{
	return (get_scal_prod(get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a)),
		get_diff(delta, get_num_prod(scal_prod_delta_v_a, v_a))) - pow(rad, 2));
}

t_t1t2	*get_cyl_intersections(t_env *env, t_fig cyl, t_vector point)
{
	t_vector	p_a;
	t_vector	v_a;
	t_vector	delta;
	double	scal_prod_v_v_a;
	double	scal_prod_delta_v_a;

	p_a = cyl.center;
	v_a = get_ort(get_vect(cyl.center, cyl.center2));
	delta = get_diff(env->camera, p_a);
	scal_prod_v_v_a = get_scal_prod(point, v_a);
	scal_prod_delta_v_a = get_scal_prod(delta, v_a);
	return (get_quadratic_solution(get_cyl_a(point, scal_prod_v_v_a, v_a),
		get_cyl_b(point, delta, scal_prod_v_v_a, v_a, scal_prod_delta_v_a),
		get_cyl_c(delta, scal_prod_delta_v_a, v_a, cyl.rad)));
}

t_t1t2	*get_plane_intersections(t_env *env, t_fig fig, t_vector point)
{
	double	denom;
	t_t1t2	*intersections;

	denom = get_scal_prod(point, fig.normal);
	if (denom == 0.0)
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

	env->fig_amount = 4;
	env->figs = (t_fig *)malloc(sizeof(t_fig) * env->fig_amount);

	env->figs[0].type = "sphere";
	env->figs[0].center = (t_vector){0, 0, DISTANCE + 150};
	env->figs[0].rad = 300;
	env->figs[0].color = RED;

	env->figs[1].type = "cylinder";
	env->figs[1].center = (t_vector){0, 0, DISTANCE + 150};
	env->figs[1].center2 = (t_vector){100, 100, DISTANCE + 160};
	env->figs[1].rad = 150;
	env->figs[1].color = GREEN;

	env->figs[2].type = "plane";
	env->figs[2].center = (t_vector){0, 0, DISTANCE};
	env->figs[2].normal = (t_vector){1, 1, 1};
	env->figs[2].color = YELLOW;

	env->figs[3].type = "cone";
	env->figs[3].center = (t_vector){0, 0, DISTANCE};
	env->figs[3].center2 = (t_vector){-50, -50, DISTANCE};
	env->figs[3].rad = 50;
	env->figs[3].rad2 = 100;
	env->figs[3].color = BLUE;

	env->ambient_light.intensity = 0.2;

	env->point_light.intensity = 0.4;
	env->point_light.pos = (t_vector){500, 500, 1000};

	env->dir_light.intensity = 0.4;
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
