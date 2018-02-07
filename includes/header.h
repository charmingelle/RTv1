/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:05 by grevenko          #+#    #+#             */
/*   Updated: 2018/02/07 18:40:13 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1200
# define HEIGHT 1000
# define ESC 53

# define WHITE 0xFFFFFF
# define RED 0xFF0000;

typedef struct	s_2point
{
	double	x;
	double	y;
}				t_2point;

typedef struct	s_pount
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_sphere
{
	t_point	center;
	double	rad;
	int		color;
}				t_sphere;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	t_point		camera;
	double		distance;
	int			color;
	t_sphere	sphere;
}				t_env;

int	handle_keypress(int keycode, t_env *env);

t_point	get_vector(t_point start, t_point end);

double	get_scalar_product(t_point v1, t_point v2);

#endif
