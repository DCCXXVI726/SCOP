/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vao_vbo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:42:23 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 20:15:31 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Создаем основные структуры
** VBO Vertex Buffer Object
** Cписок всех вершин в буффере
** VAO Vertex Array Object
** Перевод буфера в маасив
** EBO Element Buffer object
** Индексы вершин для отрисовки по одинаковым точкам
*/

t_vve	create_vao_vbo(void)
{
	t_obj			*object;
	t_vve			vve;

	object = create_object("resources/42.obj");
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
	return (vve);
}
