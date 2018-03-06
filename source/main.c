/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/06 19:54:00 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector	get_centered_coords(t_env *env, int x, int y)
{
	t_vector	c;

	c.x = x - env->width / 2;
	c.y = env->height / 2 - y;
	c.z = env->distance;
	return (c);
}

t_t1t2	*get_sphere_intersections(t_fig *fig, t_vector o, t_vector d)
{
	t_vector	vector;
	double	a;
	double	b;
	double	c;

	vector = get_vect(fig->center, o);
	a = get_scal_prod(d, d);
	b = 2 * get_scal_prod(vector, d);
	c = get_scal_prod(vector, vector) - fig->rad * fig->rad;
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_plane_intersections(t_fig *fig, t_vector o, t_vector d)
{
	double	denom;
	t_t1t2	*intersections;

	denom = get_scal_prod(fig->normal, d);
	if (denom >= 0.0)
		return (NULL);
	intersections = (t_t1t2 *)malloc(sizeof(t_t1t2));
	intersections->t1 = get_scal_prod(get_diff(fig->center, o), fig->normal) / denom;
	intersections->t2 = intersections->t1;
	return (intersections);
}

t_t1t2	*get_intersections(t_fig *fig, t_vector o, t_vector d)
{
	if (ft_strcmp(fig->type, "sphere") == 0)
		return (get_sphere_intersections(fig, o, d));
	if (ft_strcmp(fig->type, "cylinder") == 0)
		return (get_cyl_intersections(fig, o, d));
	if (ft_strcmp(fig->type, "cone") == 0)
		return (get_cone_intersections(fig, o, d));
	if (ft_strcmp(fig->type, "plane") == 0)
		return (get_plane_intersections(fig, o, d));
	return (NULL);
}

t_fig	*get_closest_fig(t_fig *fig, double *closest_t, t_vector o, t_vector d)
{
	t_t1t2	*intersections;
	t_fig	*closest_fig;

	closest_fig = NULL;
	while (fig)
	{
		intersections = get_intersections(fig, o, d);
		if (intersections)
		{
			if (intersections->t1 < *closest_t)
			{
				*closest_t = intersections->t1;
				closest_fig = fig;
			}
			if (intersections->t2 < *closest_t)
			{
				*closest_t = intersections->t2;
				closest_fig = fig;
			}
			free(intersections);
		}
		fig = fig->next;
	}
	return (closest_fig);
}

t_vector	get_cyl_normal(t_vector c1, t_vector c2, t_vector p)
{
	t_vector	axis;
	t_vector	c1_minus_p;

	axis = get_vect(c1, c2);
	c1_minus_p = get_diff(c1, p);
	return (get_diff(c1_minus_p,
		get_num_prod(get_scal_prod(c1_minus_p, axis) / get_scal_square(axis), axis)));
}

t_vector	get_normal(t_vector point, t_fig *fig)
{
	if (!ft_strcmp(fig->type, "sphere"))
		return (get_ort(get_vect(point, fig->center)));
	if (ft_strcmp(fig->type, "cylinder") == 0)
		return (get_cyl_normal(fig->center, fig->center2, point));
	if (ft_strcmp(fig->type, "plane") == 0)
		return (get_num_prod(-1, fig->normal));
	return ((t_vector){0, 0, 0});
}

int		trace_ray(t_env *env, t_vector start, t_vector point, double min_t, double max_t, int depth)
{
	t_fig		*closest_fig;
	double		closest_t;
	t_vector	fig_point;
	t_vector	normal;
	int			local_color;
	t_vector	refl_vect;
	int			refl_color;

	closest_t = INFINITY;
	closest_fig = get_closest_fig(env->fig, &closest_t, start, point);
	if (closest_fig == NULL || closest_t < min_t || closest_t > max_t)
		return (env->color);
	// if (depth == 2)
	// 	printf("closest_fig = %p, closest_t = %f\n", closest_fig, closest_t);
	fig_point = get_sum(start, get_num_prod(closest_t, point));
	normal = get_normal(fig_point, closest_fig);
	local_color = get_fig_point_color(closest_fig, fig_point, normal, env);
	if (depth == 2)
		printf("closest_fig->color = %X, fig_point = (%f, %f, %f), normal = (%f, %f, %f), local_color = %X\n", closest_fig->color, fig_point.x, fig_point.y, fig_point.z, normal.x, normal.y, normal.z, local_color);
	if (DEPTH <= 0 || closest_fig->refl <= 0.0)
		return (local_color);
	refl_vect = get_refl_vect(get_num_prod(-1, point), normal);
	refl_color = trace_ray(env, refl_vect, fig_point, 0.001, INFINITY, depth - 1);
	return (get_color_sum(change_brightness(1.0 - closest_fig->refl, local_color), change_brightness(closest_fig->refl, refl_color)));
}

void	draw_scene(t_env *env)
{
	int			x;
	int			y;
	t_vector	point;
	int			color;

	x = -1;
	while (++x < env->width)
	{
		y = -1;
		while (++y < env->height)
		{
			point = get_centered_coords(env, x, y);
			color = trace_ray(env, env->camera, point, 1.0, INFINITY, DEPTH);
			mlx_pixel_put(env->mlx, env->window, x, y, color);
		}
	}
}

int	main(int amount, char **args)
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
