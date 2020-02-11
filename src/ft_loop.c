/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:32:32 by thorker           #+#    #+#             */
/*   Updated: 2020/02/11 21:03:16 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_uniform(t_camera *camera, t_matrix matrix, GLuint program)
{
	GLint adress;

	adress = glGetUniformLocation(program, "camCoord");
	glUniform3f(adress, camera->x, camera->y, camera->z);
	adress = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(adress, 1, GL_FALSE, matrix.projection);
	adress = glGetUniformLocation(program, "camera");
	glUniformMatrix4fv(adress, 1, GL_FALSE, matrix.camera);
}

void	clean_and_redraw(GLuint program, GLuint vao, GLFWwindow *window)
{
	GLfloat	rotation1[9];
	GLfloat rotation2[9];
	size_t	i;
	GLfloat timeValue;
	GLint	adress;

	i = 0;
	while (i < 9)
	{
		rotation1[i] = 0;
		rotation2[i] = 0;
		i++;
	}
	timeValue = glfwGetTime();
	rotation1[0] = cos(timeValue);
	rotation1[1] = sin(timeValue);
	rotation1[3] = -sin(timeValue);
	rotation1[4] = cos(timeValue);
	rotation1[8] = 1;
	rotation2[0] = 1;
	rotation2[4] = cos(timeValue * 0.5);
	rotation2[5] = sin(timeValue * 0.5);
	rotation2[7] = -sin(timeValue * 0.5);
	rotation2[8] = cos(timeValue * 0.5);
	adress = glGetUniformLocation(program, "rot1");
	glUniformMatrix3fv(adress, 1, GL_FALSE, rotation1);
	adress = glGetUniformLocation(program, "rot2");
	glUniformMatrix3fv(adress, 1, GL_FALSE, rotation2);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glfwSwapBuffers(window);
}

void	ft_loop(t_scop *scop)
{
	while (!glfwWindowShouldClose(scop->window) )
	{
		glfwPollEvents();
		hooks(scop->window, scop->camera);
		update_matrix(scop->matrix, scop->camera);
		update_uniform(scop->camera, scop->matrix, scop->shader_program);
		clean_and_redraw(scop->shader_program, scop->vve.vao, scop->window);
	}
	ft_clear(scop);
}
