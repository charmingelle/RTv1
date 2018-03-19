/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/19 15:13:21 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	add_prop_to_env(char **split, t_env *env, int fd)
{
	if (!ft_strcmp(split[0], "width"))
		env->width = get_non_negative(ft_atoi(split[1]));
	else if (!ft_strcmp(split[0], "height"))
		env->height = get_non_negative(ft_atoi(split[1]));
	else if (!ft_strcmp(split[0], "camera"))
		set_vector_value(split[1], &(env->camera));
	else if (!ft_strcmp(split[0], "angle"))
		set_vector_value(split[1], &(env->angle));
	else if (!ft_strcmp(split[0], "color"))
		env->color = read_color(split[1]);
	else if (!ft_strcmp(split[0], "fig"))
		add_fig_to_env(env, fd);
	else if (!ft_strcmp(split[0], "light"))
		add_light_to_env(env, fd);
	else
		exit(show_invalid_property_error());
}

static void	read_scene(t_env *env, int fd)
{
	char	*line;
	char	**split;

	while (get_next_line(fd, &line) == 1)
	{
		split = ft_strsplit(line, ' ');
		if (count_elems(split) != 2)
			exit(show_invalid_property_value_error());
		add_prop_to_env(split, env, fd);
		free(line);
		free_split(split);
	}
}

t_env		*get_env(int fd)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->camera = (t_vector){0.0, 0.0, 0.0};
	env->width = 700;
	env->height = 700;
	env->angle = (t_vector){0.0, 0.0, 0.0};
	env->color = 0;
	env->fig = NULL;
	env->light = NULL;
	read_scene(env, fd);
	env->window = mlx_new_window(env->mlx, env->width, env->height, "RTv1");
	return (env);
}
