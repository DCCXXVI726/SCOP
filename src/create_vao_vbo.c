/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vao_vbo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:42:23 by thorker           #+#    #+#             */
/*   Updated: 2020/06/27 20:09:35 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vve	create_vao_vbo(void)
{
	/*
	const GLfloat	vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f
	};
	const GLuint	indices[] = {
		0, 2, 6,
		0, 6, 4,
		4, 6, 7,
		4, 7, 5,
		5, 7, 3,
		5, 3, 1,
		1, 3, 2,
		1, 2, 0,
		2, 3, 7,
		2, 7, 6,
		5, 1, 0,
		5, 0, 4
	};
	*/
	t_obj			*object;
	t_vve			vve;

	object = create_object("42.obj");
	ft_putnbrln(object->ind_size);

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
