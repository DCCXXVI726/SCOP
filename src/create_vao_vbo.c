/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vao_vbo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:42:23 by thorker           #+#    #+#             */
/*   Updated: 2020/07/11 18:22:18 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Находим центр масс объекта
*/

static	float	*create_center(t_obj *object)
{
	float	*center;
	size_t	i;

	if ((center = (float*)malloc(sizeof(float) * 3)) == NULL)
		return (NULL);
	center[0] = 0;
	center[1] = 0;
	center[2] = 0;
	i = 0;
	while (i < object->ver_size)
	{
		center[i % 3] += object->vertices[i];
		i++;
	}
	center[0] = -center[0] / (object->ver_size / 3);
	center[1] = -center[1] / (object->ver_size / 3);
	center[2] = -center[2] / (object->ver_size / 3);
	return (center);
}

/*
** Создаем основные структуры
** VBO Vertex Buffer Object
** Cписок всех вершин в буффере
** VAO Vertex Array Object
** Перевод буфера в маасив
** EBO Element Buffer object
** Индексы вершин для отрисовки по одинаковым точкам
*/

t_vve			create_vao_vbo(char *file_name)
{
	t_obj			*object;
	t_vve			vve;

	if ((object = create_object(file_name)) == 0)
		ft_error("can't create object");
	if ((vve.center = create_center(object)) == NULL)
		ft_error("can't create center");
	vve.ind_size = object->ind_size;
	glGenVertexArrays(1, &(vve.vao));
	glGenBuffers(1, &(vve.vbo));
	glGenBuffers(1, &(vve.ebo));
	glBindVertexArray(vve.vao);
	glBindBuffer(GL_ARRAY_BUFFER, vve.vbo);
	glBufferData(GL_ARRAY_BUFFER, object->ver_size * sizeof(GLfloat),
			object->vertices, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vve.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, object->ind_size * sizeof(GLuint),
			object->indices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3,
			GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ft_delete_object(&object);
	return (vve);
}
