/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/13 15:32:51 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_non_negative(int n)
{
	if (n < 0)
		exit(show_invalid_value_error());
	return (n);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	add_fig_to_figs(t_fig *fig, t_fig **figs)
{
	if (*figs == NULL)
		*figs = fig;
	else
	{
		while ((*figs)->next != NULL)
			figs = &((*figs)->next);
		(*figs)->next = fig;
	}
}

void	add_light_to_lights(t_light *light, t_light **lights)
{
	if (*lights == NULL)
		*lights = light;
	else
	{
		while ((*lights)->next != NULL)
			lights = &((*lights)->next);
		(*lights)->next = light;
	}
}

void	set_vector_value(char *source, t_vector *vector)
{
	char	**coords;

	coords = ft_strsplit(source, ',');
	if (count_elems(coords) != 3)
		exit(show_invalid_vector_error());
	*vector = (t_vector){ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2])};
	free_split(coords);
}

char	*get_fig_type(char *given)
{
	if (!ft_strcmp(given, "sphere")
		|| !ft_strcmp(given, "plane")
		|| !ft_strcmp(given, "cylinder")
		|| !ft_strcmp(given, "cone"))
	return (ft_strdup(given));
	exit(show_invalid_fig_error());
}

void	add_prop_to_fig(char **split, t_fig *fig)
{
	if (!ft_strcmp(split[0], "type"))
		fig->type = get_fig_type(split[1]);
	else if (!ft_strcmp(split[0], "center"))
		set_vector_value(split[1], &(fig->center));
	else if (!ft_strcmp(split[0], "center2"))
		set_vector_value(split[1], &(fig->center2));
	else if (!ft_strcmp(split[0], "rad"))
		fig->rad = get_non_negative(ft_atoi(split[1]));
	else if (!ft_strcmp(split[0], "rad2"))
		fig->rad2 = get_non_negative(ft_atoi(split[1]));
	else if (!ft_strcmp(split[0], "color"))
		fig->color = read_color(split[1]);
	else if (!ft_strcmp(split[0], "shine"))
		fig->shine = get_non_negative(ft_atoi(split[1]));
	else if (!ft_strcmp(split[0], "refl"))
		fig->refl = get_non_negative(ft_atoi(split[1])) / 100.0;
	else
		exit(show_invalid_property_error());
}

void	add_fig_to_env(t_env *env, int fd)
{
	char	*line;
	char	**split;
	t_fig	*fig;

	fig = (t_fig *)malloc(sizeof(t_fig));
	fig->type = "sphere";
	fig->center = (t_vector){0.0, 0.0, 800.0};
	fig->center2 = (t_vector){0.0, 200.0, 800.0};
	fig->rad = 100.0;
	fig->rad2 = 50.0;
	fig->color = 0xFFFFFF;
	fig->shine = 0;
	fig->refl = 0.0;
	while (get_next_line(fd, &line) && ft_strcmp(line, "}"))
	{
		split = ft_strsplit(line, ' ');
		if (count_elems(split) != 2)
			exit(show_invalid_property_value_error());
		add_prop_to_fig(split, fig);
		free(line);
		free_split(split);
	}
	free(line);
	fig->next = NULL;
	add_fig_to_figs(fig, &(env->fig));
}

char	*get_light_type(char *given_type)
{
	if (!ft_strcmp(given_type, "ambient")
		|| !ft_strcmp(given_type, "point")
		|| !ft_strcmp(given_type, "dir"))
	return (ft_strdup(given_type));
	exit(show_invalid_light_error());
}

void	add_prop_to_light(char **split, t_light *light)
{
	if (!ft_strcmp(split[0], "type"))
		light->type = get_light_type(split[1]);
	else if (!ft_strcmp(split[0], "intensity"))
		light->intensity = get_non_negative(ft_atoi(split[1])) / 100.0;
	else if (!ft_strcmp(split[0], "pos"))
		set_vector_value(split[1], &(light->pos));
	else if (!ft_strcmp(split[0], "dir"))
		set_vector_value(split[1], &(light->dir));
	else
		exit(show_invalid_property_error());
}

void	add_light_to_env(t_env *env, int fd)
{
	char	*line;
	char	**split;
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->type = "ambient";
	light->intensity = 1.0;
	light->pos = (t_vector){0.0, 0.0, 0.0};
	light->dir = (t_vector){0.0, 0.0, 0.0};
	while (get_next_line(fd, &line) && ft_strcmp(line, "}"))
	{
		split = ft_strsplit(line, ' ');
		if (count_elems(split) != 2)
			exit(show_invalid_property_value_error());
		add_prop_to_light(split, light);
		free(line);
		free_split(split);
	}
	free(line);
	light->next = NULL;
	add_light_to_lights(light, &(env->light));
}

void	add_sizes_to_env(t_env *env, int size)
{
	env->width = size;
	env->height = size;
	env->distance = size;
}

void	add_prop_to_env(char **split, t_env *env, int fd)
{
	if (!ft_strcmp(split[0], "size"))
		add_sizes_to_env(env, get_non_negative(ft_atoi(split[1])));
	else if (!ft_strcmp(split[0], "camera"))
		set_vector_value(split[1], &(env->camera));
	else if (!ft_strcmp(split[0], "angle"))
		set_vector_value(split[1], &(env->angle));
	else if (!ft_strcmp(split[0], "fig"))
		add_fig_to_env(env, fd);
	else if (!ft_strcmp(split[0], "light"))
		add_light_to_env(env, fd);
	else
		exit(show_invalid_property_error());
}

void	read_scene(t_env *env, int fd)
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

t_env	*get_env(int fd)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->camera = (t_vector){0.0, 0.0, 0.0};
	env->angle = (t_vector){0.0, 0.0, 0.0};
	add_sizes_to_env(env, 700);
	env->color = 0;
	env->fig = NULL;
	env->light = NULL;
	read_scene(env, fd);
	env->window = mlx_new_window(env->mlx, env->width, env->height, "RTv1");
	return (env);
}
