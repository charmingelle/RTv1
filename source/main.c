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

t_vector	get_canvas_vect(t_env *env, int x, int y)
{
	t_vector	D;

	D.x = x - env->width / 2;
	D.y = env->height / 2 - y;
	D.z = env->distance;
	return (D);
}

t_t1t2	*get_sphere_intersections(t_fig *fig, t_vector O, t_vector D)
{
	t_vector	vector;
	double	a;
	double	b;
	double	c;

	vector = vdiff(O, fig->center);
	a = vscal(D, D);
	b = 2 * vscal(vector, D);
	c = vscal(vector, vector) - fig->rad * fig->rad;
	return (get_quadratic_solution(a, b, c));
}

t_t1t2	*get_plane_intersections(t_fig *fig, t_vector O, t_vector D)
{
	double	denom;
	t_t1t2	*intersections;

	denom = vscal(fig->normal, D);
	if (denom >= 0.0)
		return (NULL);
	intersections = (t_t1t2 *)malloc(sizeof(t_t1t2));
	intersections->t1 = vscal(vdiff(fig->center, O), fig->normal) / denom;
	intersections->t2 = intersections->t1;
	return (intersections);
}

t_t1t2	*get_intersections(t_fig *fig, t_vector O, t_vector D)
{
	if (ft_strcmp(fig->type, "sphere") == 0)
		return (get_sphere_intersections(fig, O, D));
	if (ft_strcmp(fig->type, "cylinder") == 0)
		return (get_cyl_intersections(fig, O, D));
	if (ft_strcmp(fig->type, "cone") == 0)
		return (get_cone_intersections(fig, O, D));
	if (ft_strcmp(fig->type, "plane") == 0)
		return (get_plane_intersections(fig, O, D));
	return (NULL);
}

t_fig	*get_closest_fig(t_fig *fig, double *closest_t, double min_t, double max_t, t_vector O, t_vector D)
{
	t_t1t2	*intersections;
	t_fig	*closest_fig;

	closest_fig = NULL;
	while (fig)
	{
		intersections = get_intersections(fig, O, D);
		if (intersections)
		{
			if (intersections->t1 >= min_t && intersections->t1 <= max_t && intersections->t1 < *closest_t)
			{
				*closest_t = intersections->t1;
				closest_fig = fig;
			}
			if (intersections->t2 >= min_t && intersections->t2 < max_t && intersections->t2 < *closest_t)
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

t_vector	get_cyl_normal(t_vector C1, t_vector C2, t_vector P)
{
	t_vector	axis;
	t_vector	C1_minus_P;

	axis = vdiff(C2, C1);
	C1_minus_P = vdiff(C1, P);
	return (vdiff(vmult(vscal(C1_minus_P, axis) / vsquare(axis), axis), C1_minus_P));
}

t_vector	get_normal(t_vector P, t_fig *fig)
{
	if (!ft_strcmp(fig->type, "sphere"))
		return (vort(vdiff(P, fig->center)));
	if (!ft_strcmp(fig->type, "cylinder"))
		return (get_cyl_normal(fig->center, fig->center2, P));
	// if (!ft_strcmp(fig->type, "cone"))
	// 	return (get_cone_normal());
	if (!ft_strcmp(fig->type, "plane"))
		return (fig->normal);
	return ((t_vector){0, 0, 0});
}

int		trace_ray(t_env *env, t_vector O, t_vector D, double min_t, double max_t, int depth)
{
	t_fig		*closest_fig;
	double		closest_t;
	t_vector	P;
	t_vector	N;
	int			local_color;
	t_vector	R;
	int			refl_color;

	closest_t = INFINITY;
	closest_fig = get_closest_fig(env->fig, &closest_t, min_t, max_t, O, D);
	if (closest_fig == NULL)
		return (env->color);
	P = vsum(O, vmult(closest_t, D));
	N = get_normal(P, closest_fig);
	local_color = get_fig_point_color(closest_fig, P, N, env);
	if (depth <= 0 || closest_fig->refl <= 0.0)
		return (local_color);
	R = vrefl(vmult(-1, D), N);
	refl_color = trace_ray(env, P, R, 0.001, INFINITY, depth - 1);
	// return (get_color_sum(change_brightness(local_color, 1.0 - closest_fig->refl),
	// 	change_brightness(refl_color, closest_fig->refl)));
	return (change_brightness(local_color, 1.0 - closest_fig->refl) +
		change_brightness(refl_color, closest_fig->refl));
	// return (get_middle_color(change_brightness(local_color, 1.0 - closest_fig->refl),
	// 	change_brightness(refl_color, closest_fig->refl)));
}

void	draw_scene(t_env *env)
{
	int			x;
	int			y;
	t_vector	D;
	int			color;

	x = -1;
	while (++x < env->width)
	{
		y = -1;
		while (++y < env->height)
		{
			D = get_canvas_vect(env, x, y);
			color = trace_ray(env, env->camera, D, 1.0, INFINITY, DEPTH);
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
