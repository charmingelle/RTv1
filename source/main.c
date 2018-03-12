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

double		get_sphere_intersection(t_fig *fig, t_ray ray)
{
	t_vector	vector;
	double	a;
	double	b;
	double	c;

	vector = vdiff(ray.O, fig->center);
	a = vscal(ray.D, ray.D);
	b = 2 * vscal(vector, ray.D);
	c = vscal(vector, vector) - fig->rad * fig->rad;
	return (get_quadratic_solution(a, b, c, ray));
}

double		get_plane_intersection(t_fig *fig, t_ray ray)
{
	double	denom;
	double	t;

	denom = vscal(fig->center2, ray.D);
	if (denom >= 0.0)
		return (INFINITY);
	t = vscal(vdiff(fig->center, ray.O), fig->center2) / denom;
	if (t >= ray.t_min && t <= ray.t_max)
		return (t);
	return (INFINITY);
}

double	get_intersection(t_fig *fig, t_ray ray)
{
	if (ft_strcmp(fig->type, "sphere") == 0)
		return (get_sphere_intersection(fig, ray));
	if (ft_strcmp(fig->type, "cylinder") == 0)
		return (get_cyl_intersection(fig, ray));
	if (ft_strcmp(fig->type, "cone") == 0)
		return (get_cone_intersection(fig, ray));
	if (ft_strcmp(fig->type, "plane") == 0)
		return (get_plane_intersection(fig, ray));
	return (INFINITY);
}

t_fig	*get_closest_fig(t_ray ray, t_fig *fig, double *closest_t)
{
	double	t;
	t_fig	*closest_fig;

	closest_fig = NULL;
	while (fig)
	{
		t = get_intersection(fig, ray);
		if (t < *closest_t)
		{
			*closest_t = t;
			closest_fig = fig;
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

t_vector	get_cone_normal(t_vector C1, t_vector C2, double rad, double rad2, t_vector P)
{
	t_vector	G1;
	t_vector	G2;
	t_vector	gener;
	t_vector	G1_minus_P;

	G1 = vsum(C1, (t_vector){rad, 0.0, 0.0});
	G2 = vsum(C2, (t_vector){rad2, 0.0, 0.0});
	gener = vdiff(G2, G1);
	G1_minus_P = vdiff(G1, P);
	return (vdiff(vmult(vscal(G1_minus_P, gener) / vsquare(gener), gener), G1_minus_P));
}

t_vector	get_normal(t_vector P, t_fig *fig)
{
	if (!ft_strcmp(fig->type, "sphere"))
		return (vort(vdiff(P, fig->center)));
	if (!ft_strcmp(fig->type, "cylinder"))
		return (get_cyl_normal(fig->center, fig->center2, P));
	if (!ft_strcmp(fig->type, "cone"))
		return (get_cone_normal(fig->center, fig->center2, fig->rad, fig->rad2, P));
	if (!ft_strcmp(fig->type, "plane"))
		return (fig->center2);
	return ((t_vector){0, 0, 0});
}

int		trace_ray(t_env *env, t_ray ray, int depth)
{
	t_fig		*closest_fig;
	double		closest_t;
	t_vector	P;
	t_vector	N;
	int			local_color;
	t_vector	R;
	int			refl_color;

	closest_t = INFINITY;
	closest_fig = get_closest_fig(ray, env->fig, &closest_t);
	if (closest_fig == NULL)
		return (env->color);
	P = vsum(ray.O, vmult(closest_t, ray.D));
	N = get_normal(P, closest_fig);
	local_color = get_fig_point_color(closest_fig, P, N, env);
	if (depth <= 0 || closest_fig->refl == 0.0)
		return (local_color);
	R = vrefl(vmult(-1, ray.D), N);
	refl_color = trace_ray(env, (t_ray){P, R, 0.001, INFINITY}, depth - 1);
	return (change_brightness(local_color, 1.0 - closest_fig->refl) +
		change_brightness(refl_color, closest_fig->refl));
}

void	redraw_scene(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	draw_scene(env);
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
			color = trace_ray(env, (t_ray){vrotate(env->camera, env), D, 1.0, INFINITY}, DEPTH);
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
