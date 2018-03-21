/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 13:08:14 by grevenko          #+#    #+#             */
/*   Updated: 2018/03/21 14:19:06 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	add_fig_to_figs(t_fig *fig, t_fig **figs)
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

static char	*get_fig_type(char *given)
{
	if (!ft_strcmp(given, "sphere")
		|| !ft_strcmp(given, "plane")
		|| !ft_strcmp(given, "cylinder")
		|| !ft_strcmp(given, "cone"))
		return (ft_strdup(given));
	exit(show_invalid_fig_error());
}

static void	add_prop_to_fig(char **split, t_fig *fig)
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

void		add_fig_to_env(t_env *env, int fd)
{
	char	*line;
	char	**split;
	t_fig	*fig;

	fig = (t_fig *)malloc(sizeof(t_fig));
	fig->type = "sphere";
	fig->center = (t_vector){0.0, 0.0, 100.0};
	fig->center2 = (t_vector){fig->center.x, fig->center.y + 10, fig->center.z};
	fig->rad = 10.0;
	fig->rad2 = 0.0;
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
