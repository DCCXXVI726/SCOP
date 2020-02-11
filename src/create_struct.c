/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:12:46 by thorker           #+#    #+#             */
/*   Updated: 2020/02/11 21:00:31 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat	*create_camera_matrix(void)
{
	GLfloat	*matrix;
	size_t	i;

	if ((matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16)) == 0)
		ft_error(MALLOC_E);
	i = 0;
	while (i < 16)
		matrix[i++] = 0.0f;
	return (matrix);
}

GLfloat	*create_projection(void)
{
	GLfloat	*matrix;
	size_t	i;
	GLfloat	fovrad;

	if ((matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16)) == 0)
		ft_error(MALLOC_E);
	i = 0;
	while (i < 16)
		matrix[i++] = 0.0f;
	fovrad = 1.0f / tan(FOV * 0.5f / 180.0f * M_PI);
	matrix[0] = ((GLfloat)WIN_H) / WIN_W * fovrad;
	matrix[5] = fovrad;
	matrix[10] = FAR / (FAR - NEAR);
	matrix[11] = 1.0f;
	matrix[14] = (-1) * (FAR * NEAR) / (FAR - NEAR);
	return (matrix);
}

t_scop	*create_struct(void)
{
	t_scop	*scop;

	if ((scop = (t_scop*)malloc(sizeof(t_scop))) == 0)
		ft_error(MALLOC_E);
	if ((scop->camera = (t_camera*)malloc(sizeof(t_camera))) == 0)
		ft_error(MALLOC_E);
	scop->camera->x = 0;
	scop->camera->y = 0;
	scop->camera->z = -3.0f;
	scop->camera->last_x = WIN_W / 2;
	scop->camera->last_y = WIN_H / 2;
	scop->camera->phi = 0;
	scop->camera->tetta = 0;
	scop->matrix.projection = create_projection();
	scop->matrix.camera = create_camera_matrix();
	return (scop);
}
