/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:05 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/06 19:55:40 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define PLUS 69
# define MINUS 78
# define WW 13
# define AA 0
# define SS 1
# define DD 2
# define QQ 12
# define EE 14

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

# define DEPTH 3

# define MIN(X, Y) (X < Y ? X : Y)

# define IN_RANGE(VALUE, MIN, MAX) (VALUE >= MIN && VALUE <= MAX ? 1 : 0)

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef	struct	s_ray
{
	t_vector	O;
	t_vector	D;
	double		t_min;
	double		t_max;
}				t_ray;

typedef struct	s_fig
{
	char			*type;
	t_vector		center;
	t_vector		center2;
	double			rad;
	double			rad2;
	int				color;
	int				shine;
	double			refl;
	struct s_fig	*next;
}				t_fig;

typedef struct s_light
{
	char			*type;
	double			intensity;
	t_vector		pos;
	t_vector		dir;
	struct s_light	*next;
}				t_light;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	t_vector	camera;
	int			ang_x;
	int			ang_y;
	int			ang_z;
	int			width;
	int			height;
	int			distance;
	int			color;
	t_fig		*fig;
	t_light		*light;
}				t_env;

void		draw_scene(t_env *env);

int			handle_keypress(int keycode, t_env *env);

t_vector	vsum(t_vector A, t_vector B);
t_vector	vdiff(t_vector A, t_vector B);
t_vector	vmult(double num, t_vector A);
double		vscal(t_vector A, t_vector B);
double		vsquare(t_vector A);
double		vlen(t_vector A);
t_vector	vort(t_vector A);
t_vector	vrefl(t_vector L, t_vector N);
t_vector	vrotate(t_vector A, t_env *env);

double		get_light(t_vector P, t_vector N, t_fig *fig, t_env *env);

int			change_brightness(int color, double coef);
int			get_color_sum(int c1, int c2);
int			get_middle_color(int c1, int c2);
int			get_fig_point_color(t_fig *fig, t_vector P, t_vector N, t_env *env);

t_fig		*get_closest_fig(t_ray ray, t_fig *fig, double *closest_t);

double		get_cyl_intersection(t_fig *fig, t_ray ray);
double		get_cone_intersection(t_fig *fig, t_ray ray);

t_env		*get_env(int fd);
void		redraw_scene(t_env *env);

int			show_invalid_color_error();
int			show_usage_error();
int			show_file_not_found_error();
int			show_invalid_property_error();
int			show_invalid_vector_error();
int			show_invalid_property_value_error();
int			show_invalid_light_error();
int			show_invalid_fig_error();

double		get_quadratic_solution(double a, double b, double c, t_ray ray);
double		get_rad(int degree);
int			read_color(char *s);
int			count_elems(char **array);

#endif
