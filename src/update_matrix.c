/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:35:18 by thorker           #+#    #+#             */
/*   Updated: 2020/07/11 17:51:53 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Вычесление матрицы поворота камеры из углов
** Засунусть center в структуру
*/

void	update_matrix(t_matrix matrix, t_camera *camera, float *center)
{
	camera->phi = glfwGetTime();
	matrix.camera[0] = cos(camera->phi);
	matrix.camera[1] = sin(camera->tetta) * sin(camera->phi);
	matrix.camera[2] = sin(camera->phi) * cos(camera->tetta);
	matrix.camera[12] = matrix.camera[0] * center[0]
		+ matrix.camera[4] * center[1]
		+ matrix.camera[8] * center[2] - center[0];
	matrix.camera[5] = cos(camera->tetta);
	matrix.camera[6] = -1 * sin(camera->tetta);
	matrix.camera[13] = matrix.camera[1] * center[0]
		+ matrix.camera[5] * center[1]
		+ matrix.camera[9] * center[2] - center[1];
	matrix.camera[8] = -1 * sin(camera->phi);
	matrix.camera[9] = sin(camera->tetta) * cos(camera->phi);
	matrix.camera[10] = cos(camera->phi) * cos(camera->tetta);
	matrix.camera[14] = matrix.camera[2] * center[0]
		+ matrix.camera[6] * center[1]
		+ matrix.camera[10] * center[2] - center[2];
	matrix.camera[15] = 1.0f;
}
