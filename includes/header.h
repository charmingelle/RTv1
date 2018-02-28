/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:05 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/24 20:32:52 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 700
# define HEIGHT 700
# define DISTANCE 700
# define ESC 53

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

typedef struct	s_t1t2
{
	double	t1;
	double	t2;
}				t_t1t2;

typedef struct	s_pount
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct	s_fig
{
	char		*type;
	t_vector	center;
	t_vector	center2;
	double		rad;
	double		rad2;
	t_vector	normal;
	int			color;
}				t_fig;

typedef struct s_light
{
	double	intensity;
	t_vector	pos;
	t_vector	dir;
}				t_light;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	t_vector		camera;
	int			distance;
	int			color;
	int			fig_amount;
	t_fig		*figs;
	t_light		ambient_light;
	t_light		point_light;
	t_light		dir_light;
}				t_env;

int			handle_keypress(int keycode, t_env *env);

t_vector	get_vect(t_vector start, t_vector end);

t_vector	get_sum(t_vector v1, t_vector v2);

t_vector	get_diff(t_vector v1, t_vector v2);

t_vector	get_num_prod(double num, t_vector v);

double		get_scal_prod(t_vector v1, t_vector v2);

double		get_scal_square(t_vector vector);

double		get_len(t_vector vector);

t_vector	get_ort(t_vector vector);

double		get_ambient_light(t_env *env);

double		get_vector_light(t_vector point, t_vector normal, t_env *env);

double		get_dir_light(t_vector point, t_vector normal, t_env *env);

double		get_light(t_vector point, t_vector normal, t_env *env);

int			change_brightness(int color, double coef);

int			get_fig_point_color(t_env *env, t_fig fig, t_vector point);

t_t1t2		*get_quadratic_solution(double a, double b, double c);

double		get_rad(int degree);

int			get_closest_fig_num(t_env *env, double *closest_t, t_vector o, t_vector d);

t_t1t2		*get_cone_intersections(t_fig cone, t_vector o, t_vector d);

t_t1t2		*get_cyl_intersections(t_fig cyl, t_vector o, t_vector d);

#endif
