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
	char			*type;
	t_vector		center;
	t_vector		center2;
	double			rad;
	double			rad2;
	t_vector		normal;
	int				color;
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
	int			width;
	int			height;
	int			distance;
	int			color;
	int			fig_amount;
	t_fig		*fig;
	t_light		*light;
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

double		get_light(t_vector point, t_vector normal, t_env *env);

int			change_brightness(int color, double coef);

int			get_fig_point_color(t_fig *fig, t_vector point, t_env *env);

t_t1t2		*get_quadratic_solution(double a, double b, double c);

double		get_rad(int degree);

t_fig		*get_closest_fig(t_fig *fig, double *closest_t, t_vector o, t_vector d);

t_t1t2		*get_cone_intersections(t_fig *fig, t_vector o, t_vector d);

t_t1t2		*get_cyl_intersections(t_fig *fig, t_vector o, t_vector d);

t_env		*get_env(int fd);

int			show_invalid_color_error();

int			read_color(char *s);

int			show_usage_error();

int			show_file_not_found_error();

int			show_invalid_property_error();

int			show_invalid_vector_error();

int			show_invalid_property_value_error();

int			show_invalid_light_error();

int			show_invalid_fig_error();

int			count_elems(char **array);

#endif
