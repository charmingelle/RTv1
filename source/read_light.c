/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/14 16:39:08 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	add_light_to_lights(t_light *light, t_light **lights)
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

static char	*get_light_type(char *given_type)
{
	if (!ft_strcmp(given_type, "ambient")
		|| !ft_strcmp(given_type, "point")
		|| !ft_strcmp(given_type, "dir"))
		return (ft_strdup(given_type));
	exit(show_invalid_light_error());
}

static void	add_prop_to_light(char **split, t_light *light)
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

void		add_light_to_env(t_env *env, int fd)
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
