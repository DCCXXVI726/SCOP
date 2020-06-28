/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:33:08 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 19:53:22 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Добавить очистку после vertices == 0
** Добавление вершин
*/

int		add_vertices(char *line, t_obj *object)
{
	char	**buffer;
	GLfloat	tmp;
	size_t	i;

	if (line == NULL)
		return (EMPTY_LINE_ERROR);
	if ((buffer = ft_strsplit(line, ' ')) == 0)
		return (SPLIT_ERROR);
	i = 1;
	while (*(buffer + i) != 0)
	{
		tmp = atof(*(buffer + i));
		object->vertices = ft_realloc(object->vertices,
				object->ver_size * sizeof(GLfloat), &tmp, sizeof(GLfloat));
		if (object->vertices == NULL)
		{
			ft_cleanbuf(buffer);
			return (-1);
		}
		object->ver_size++;
		i++;
	}
	ft_cleanbuf(buffer);
	return (0);
}

/*
** Добавление индексов вершин
*/

int		add_indices(char *line, t_obj *object)
{
	char	**buffer;
	GLuint	tmp;
	size_t	i;

	if (line == NULL)
		return (EMPTY_LINE_ERROR);
	if ((buffer = ft_strsplit(line, ' ')) == 0)
		return (SPLIT_ERROR);
	i = 1;
	while (*(buffer + i) != NULL)
	{
		tmp = ft_atoi(*(buffer + i)) - 1;
		object->indices = ft_realloc(object->indices,
				object->ind_size * sizeof(GLuint), &tmp, sizeof(GLuint));
		if (object->indices == NULL)
		{
			ft_cleanbuf(buffer);
			return (-1);
		}
		object->ind_size++;
		i++;
	}
	ft_cleanbuf(buffer);
	return (0);
}
