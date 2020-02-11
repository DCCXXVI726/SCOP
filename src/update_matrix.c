/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 19:35:18 by thorker           #+#    #+#             */
/*   Updated: 2020/02/11 20:54:28 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_matrix(t_matrix	matrix, t_camera *camera)
{
	matrix.camera[0] = cos(camera->phi);
	matrix.camera[1] = sin(camera->tetta) * sin(camera->phi);
	matrix.camera[2] = sin(camera->phi) * cos(camera->tetta);
	matrix.camera[5] = cos(camera->tetta);
	matrix.camera[6] = -1 * sin(camera->tetta);
	matrix.camera[8] = -1 * sin(camera->phi);
	matrix.camera[9] = sin(camera->tetta) * cos(camera->phi);
	matrix.camera[10] = cos(camera->phi) * cos(camera->tetta);
	matrix.camera[15] = 1.0f;
}
