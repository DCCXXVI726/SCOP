/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:32:32 by thorker           #+#    #+#             */
/*   Updated: 2020/07/06 18:17:03 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Обновляет позиции камеры, матрицы поворота камеры и проекции
** (может их сразу перемножить?)
*/

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

/*
** Очистка экрана и отрисовка заново
*/

void	clean_and_redraw(t_scop *scop)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(scop->shader_program);
	glBindTexture(GL_TEXTURE_2D, scop->texture);
	glBindVertexArray(scop->vve.vao);
	glDrawElements(GL_TRIANGLES, scop->vve.ind_size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glfwSwapBuffers(scop->window);
}

/*
** Основной игровой цикл
*/

void	ft_loop(t_scop *scop)
{
	while (!glfwWindowShouldClose(scop->window))
	{
		glfwPollEvents();
		hooks(scop->window, scop->camera);
		update_matrix(scop->matrix, scop->camera);
		update_uniform(scop->camera, scop->matrix, scop->shader_program);
		clean_and_redraw(scop);
	}
	ft_clear(scop);
}
