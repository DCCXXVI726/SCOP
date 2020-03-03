/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 12:55:18 by thorker           #+#    #+#             */
/*   Updated: 2020/03/02 23:18:46 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

GLuint	create_vert(void)
{
	const GLchar	*vertex_shader_source = "#version 400 core\n"
		"layout (location = 0) in vec3 position;\n"
		"uniform vec3 camCoord;\n"
		"uniform mat3 rot1;\n"
		"uniform mat3 rot2;\n"
		"uniform mat4 camera;\n"
		"uniform mat4 projection;\n"
		"out vec4 kek;\n"
		"void main()\n"
		"{\n"
		"kek = vec4(position, 1.0f);\n"
		"gl_Position = projection * camera * vec4(position - camCoord, 1.0f);\n"
		"}\n\0";
	GLuint			vertex_shader;

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, 0);
	glCompileShader(vertex_shader);
	if (check_shader(vertex_shader) != 0)
		return (0);
	return (vertex_shader);
}

GLuint	create_frag(void)
{
	const GLchar	*fragment_shader_source = "#version 400 core\n"
		"out vec4 color;\n"
		"in	vec4 kek;\n"
		"void main()\n"
		"{\n"
		"color = kek;\n"
		"}\n\0";
	GLuint			fragment_shader;

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, 0);
	glCompileShader(fragment_shader);
	if (check_shader(fragment_shader) != 0)
		return (0);
	return (fragment_shader);
}

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
