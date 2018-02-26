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

# define WIDTH 600
# define HEIGHT 600
# define DISTANCE 600
# define ESC 53

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

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
}				t_point;

typedef struct	s_fig
{
	char	*type;
	t_point	center;
	t_point	axis1;
	t_point	axis2;
	double	rad;
	double	rad2;
	int		color;
}				t_fig;

typedef struct s_light
{
	double	intensity;
	t_point	pos;
	t_point	dir;
}				t_light;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	t_point		camera;
	int			distance;
	int			color;
	int			fig_amount;
	t_fig		*figs;
	t_light		ambient_light;
	t_light		point_light;
	t_light		dir_light;
}				t_env;

int		handle_keypress(int keycode, t_env *env);

t_point	get_vect(t_point start, t_point end);

t_point	get_sum(t_point v1, t_point v2);

t_point	get_diff(t_point v1, t_point v2);

t_point	get_num_prod(double num, t_point v);

double	get_scal_prod(t_point v1, t_point v2);

double	get_scal_square(t_point vector);

double	get_len(t_point vector);

t_point	get_ort(t_point vector);

double	get_ambient_light(t_env *env);

double	get_point_light(t_point point, t_point normal, t_env *env);

double	get_dir_light(t_point normal, t_env *env);

double	get_light(t_point point, t_point normal, t_env *env);

int		change_brightness(int color, double coef);

int		get_fig_point_color(t_env *env, t_fig fig, t_point point);

t_t1t2	*get_quadratic_solution(double a, double b, double c);

double	get_rad(int degree);

#endif
