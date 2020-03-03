/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:33:08 by thorker           #+#    #+#             */
/*   Updated: 2020/03/03 04:39:26 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Добавить очистку после vertices == 0
** 
*/

int		add_vertices(char *line, t_obj *object)
{
	char	**buffer;
	GLfloat	tmp;
	size_t	i;
	GLfloat	*vertices;

	if (line == 0)
		return (EMPTY_LINE_ERROR);
	if ((buffer = ft_strsplit(line, ' ')) == 0)
		return (SPLIT_ERROR);
	i = 1;
	while (*(buffer + i) != 0)
	{
		tmp = atof(*(buffer + i));
		vertices = ft_realloc(object->vertices,
				object->ver_size * sizeof(GLfloat), &tmp, sizeof(GLfloat));
		if (vertices == 0)
			return (-1);
		object->vertices = vertices;
		object->ver_size++;
		i++;
	}
	cleanbuf(buffer);
	return (0);
}

int		add_indices(char *line, t_obj *object)
{
	char	**buffer;
	GLuint	tmp;
	size_t	i;
	GLuint	*indices;

	if (line == 0)
		return (EMPTY_LINE_ERROR);
	if ((buffer = ft_strsplit(line, ' ')) == 0)
		return(SPLIT_ERROR);
	i = 1;
	while (*(buffer + i) != 0)
	{
		tmp = ft_atoi(*(buffer + i)) - 1;
		indices = ft_realloc(object->indices,
				object->ind_size * sizeof(GLuint), &tmp, sizeof(GLuint));
		if (indices == 0)
			return (-1);
		object->indices = indices;
		object->ind_size++;
		i++;
	}
	cleanbuf(buffer);
	return (0);
}
