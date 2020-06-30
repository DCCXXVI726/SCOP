/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:55:18 by thorker           #+#    #+#             */
/*   Updated: 2020/06/30 20:12:18 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	Проверяет правильно ли создался шейдер
*/

int		check_shader(GLuint shader)
{
	GLint	success;
	GLchar	info_log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, 0, info_log);
		ft_error(info_log);
	}
	return (0);
}

/*
**	Создание vertex shader
*/

GLuint	create_vert(void)
{
	GLuint			vertex_shader;
	const GLchar	*vertex_shader_src = get_shader_code("src/vertex_shader");

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_src, 0);
	glCompileShader(vertex_shader);
	free((void*)vertex_shader_src);
	if (check_shader(vertex_shader) != 0)
		return (0);
	return (vertex_shader);
}

/*
** Создание fragment shader
*/

GLuint	create_frag(void)
{
	const GLchar	*frag_shader_src = get_shader_code("src/fragment_shader");
	GLuint			fragment_shader;

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_shader_src, 0);
	glCompileShader(fragment_shader);
	free((void*)frag_shader_src);
	if (check_shader(fragment_shader) != 0)
		return (0);
	return (fragment_shader);
}

/*
** Создание программы шейдеров, привязка всех шейдеров
** удалание шейдеров
*/

GLuint	create_program(void)
{
	GLuint	fragment_shader;
	GLuint	vertex_shader;
	GLuint	shader_program;
	GLint	success;
	GLchar	info_log[512];

	if ((fragment_shader = create_frag()) == 0)
		ft_error(FRAG_E);
	if ((vertex_shader = create_vert()) == 0)
		ft_error(VERT_E);
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, 0, info_log);
		ft_error(info_log);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (shader_program);
}
