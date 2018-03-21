/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:05 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/21 14:10:33 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define PLUS 69
# define MINUS 78
# define W 13
# define A 0
# define S 1
# define D 2
# define Q 12
# define E 14

# define WINDOW_CLOSING_EVENT 17

# define DEPTH 3

# define IN_RANGE(VALUE, MIN, MAX) (VALUE >= MIN && VALUE <= MAX ? 1 : 0)

typedef struct	s_sol
{
	double	t1;
	double	t2;
}				t_sol;

typedef struct	s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef	struct	s_ray
{
	t_vector	o;
	t_vector	d;
	t_vector	p;
	t_vector	n;
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

typedef struct	s_light
{
	char			*type;
	double			power;
	t_vector		vector;
	struct s_light	*next;
}				t_light;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	t_vector	camera;
	int			width;
	int			height;
	t_vector	angle;
	int			color;
	t_fig		*fig;
	t_light		*light;
}				t_env;

int				change_brightness(int color, double coef);
int				get_fig_point_color(t_fig *fig, t_ray ray, t_env *env);

t_sol			get_cone_intersection(t_fig *fig, t_ray ray);
t_vector		get_cone_normal(t_fig *fig, t_vector p);

t_sol			get_cyl_intersection(t_fig *fig, t_ray ray);
t_vector		get_cyl_normal(t_vector c1, t_vector c2, t_vector p);

int				show_invalid_color_error(void);
int				show_usage_error(void);
int				show_file_not_found_error(void);
int				show_invalid_property_error(void);
int				show_invalid_value_error(void);
int				show_invalid_vector_error(void);
int				show_invalid_property_value_error(void);
int				show_invalid_light_error(void);
int				show_invalid_fig_error(void);

int				handle_keypress(int keycode, t_env *env);

double			get_light(t_ray ray, t_fig *fig, t_env *env);

void			redraw_scene(t_env *env);

t_sol			get_plane_intersection(t_fig *fig, t_ray ray);

t_vector		get_normal(t_vector p, t_fig *fig);
t_fig			*get_closest_fig(t_ray *ray, t_fig *fig, double *closest_t,
	int *inner);
int				trace_ray(t_env *env, t_ray ray, int depth);

void			add_fig_to_env(t_env *env, int fd);

void			add_light_to_env(t_env *env, int fd);

int				read_color(char *s);
int				get_non_negative(int n);
void			set_vector_value(char *source, t_vector *vector);
int				count_elems(char **array);

void			free_split(char **split);
t_env			*get_env(int fd);

t_sol			get_sphere_intersection(t_fig *fig, t_ray ray);

t_sol			get_quadratic_solution(double a, double b, double c);
t_sol			get_lim_solution(t_sol sol, t_ray ray, t_fig *fig, t_vector va);
double			get_rad(int degree);

t_vector		vsum(t_vector a, t_vector b);
t_vector		vdiff(t_vector a, t_vector b);
t_vector		vmult(double num, t_vector a);
double			vscal(t_vector a, t_vector b);
double			vsq(t_vector a);
double			vlen(t_vector a);
t_vector		vort(t_vector a);
t_vector		vmid(t_vector a, t_vector b);
t_vector		vrefl(t_vector l, t_vector n);
t_vector		vrot(t_vector a, t_env *env);

#endif
