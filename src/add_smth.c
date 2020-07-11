/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_smth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:33:08 by thorker           #+#    #+#             */
/*   Updated: 2020/07/11 16:53:05 by thorker          ###   ########.fr       */
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
** Переводит строку индексов в буфер
** Если индексов больше 3х, разбивает по тройкам
*/

char	**create_buffer(char *line)
{
	char	**buffer;
	size_t	length;
	char	**new_buffer;
	size_t	i;

	if ((buffer = ft_strsplit(line, ' ')) == 0)
		return (NULL);
	length = 0;
	while (*(buffer + length) != NULL)
		length++;
	if ((new_buffer = (char**)malloc(sizeof(char*) *
					((length - 3) * 3 + 1))) != NULL)
	{
		i = 0;
		while (i < (length - 3))
		{
			*(new_buffer + i * 3) = ft_strdup(*(buffer + 1));
			*(new_buffer + i * 3 + 1) = ft_strdup(*(buffer + i + 2));
			*(new_buffer + i * 3 + 2) = ft_strdup(*(buffer + i + 3));
			i++;
		}
		*(new_buffer + i * 3) = NULL;
	}
	ft_cleanbuf(buffer);
	return (new_buffer);
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
	if ((buffer = create_buffer(line)) == 0)
		return (SPLIT_ERROR);
	i = 0;
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
