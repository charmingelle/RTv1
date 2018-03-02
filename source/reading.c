/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/01 18:04:32 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		free(split_line[i++]);
	free(split_line);
}

static int	hex_to_digit(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= '0' && c <= '9')
		return (c - '0');
	exit(show_invalid_color_error());
}

int	get_color(char *s)
{
	int	result;
	int	i;

	if ((s[0] != '0') || (s[1] != 'x'))
		exit(show_invalid_color_error());
	result = 0;
	i = 1;
	while (s[++i])
		result = result * 16 + hex_to_digit(s[i]);
	if (result > 0xFFFFFF)
		exit(show_invalid_color_error());
	return (result);
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
	*vector = (t_vector){ft_atoi(coords[0]), ft_atoi(coords[1]), ft_atoi(coords[2])};
	free_split_line(coords);
}

void	add_figure(t_env *env, int fd)
{
	char	*line;
	char	**split_line;
	t_fig	*fig;

	fig = (t_fig *)malloc(sizeof(t_fig));
	while (get_next_line(fd, &line) && ft_strcmp(line, "}"))
	{
		split_line = ft_strsplit(line, ' ');
		if (ft_strcmp(split_line[0], "type") == 0)
			fig->type = ft_strdup(split_line[1]);
		else if (ft_strcmp(split_line[0], "center") == 0)
			set_vector_value(split_line[1], &(fig->center));
		else if (ft_strcmp(split_line[0], "center2") == 0)
			set_vector_value(split_line[1], &(fig->center2));
		else if (ft_strcmp(split_line[0], "rad") == 0)
			fig->rad = ft_atoi(split_line[1]);
		else if (ft_strcmp(split_line[0], "rad2") == 0)
			fig->rad2 = ft_atoi(split_line[1]);
		else if (ft_strcmp(split_line[0], "normal") == 0)
			set_vector_value(split_line[1], &(fig->normal));
		else if (ft_strcmp(split_line[0], "color") == 0)
			fig->color = get_color(split_line[1]);
		free(line);
		free_split_line(split_line);
	}
	free(line);
	fig->next = NULL;
	add_fig_to_figs(fig, &(env->fig));
}

void	add_light(t_env *env, int fd)
{
	char	*line;
	char	**split_line;
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	while (get_next_line(fd, &line) && ft_strcmp(line, "}"))
	{
		split_line = ft_strsplit(line, ' ');
		if (ft_strcmp(split_line[0], "type") == 0)
			light->type = ft_strdup(split_line[1]);
		else if (ft_strcmp(split_line[0], "intensity") == 0)
			light->intensity = ft_atoi(split_line[1]) / 100.0;
		else if (ft_strcmp(split_line[0], "pos") == 0)
			set_vector_value(split_line[1], &(light->pos));
		else if (ft_strcmp(split_line[0], "dir") == 0)
			set_vector_value(split_line[1], &(light->dir));
		free(line);
		free_split_line(split_line);
	}
	free(line);
	light->next = NULL;
	add_light_to_lights(light, &(env->light));
}

void	add_sizes(t_env *env, int size)
{
	env->width = size;
	env->height = size;
	env->distance = size;
}

t_env	*get_env(int fd)
{
	t_env	*env;
	char	*line;
	char	**split_line;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->fig = NULL;
	env->light = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		split_line = ft_strsplit(line, ' ');
		if (ft_strcmp(split_line[0], "size") == 0)
			add_sizes(env, ft_atoi(split_line[1]));
		else if (ft_strcmp(split_line[0], "camera") == 0)
			set_vector_value(split_line[1], &(env->camera));
		else if (ft_strcmp(split_line[0], "figure") == 0)
			add_figure(env, fd);
		else if (ft_strcmp(split_line[0], "light") == 0)
			add_light(env, fd);
		free(line);
		free_split_line(split_line);
	}
	env->window = mlx_new_window(env->mlx, env->width, env->height, "RTv1");
	env->color = 0;
	return (env);
}