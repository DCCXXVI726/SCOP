/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:06:40 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 19:07:34 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** обработка изменений мыши
*/

void	mouse_hooks(GLFWwindow *window, t_camera *camera)
{
	double	x;
	double	y;

	glfwGetCursorPos(window, &x, &y);
	camera->tetta += (y - camera->last_y) * MOUSE_SENY;
	if (camera->tetta > M_PI / 2)
		camera->tetta = M_PI / 2;
	else if (camera->tetta < -M_PI / 2)
		camera->tetta = -M_PI / 2;
	camera->phi += (x - camera->last_x) * MOUSE_SENX;
	camera->last_x = x;
	camera->last_y = y;
}

/*
** обработка нажатия клавиш
*/

void	hooks(GLFWwindow *window, t_camera *camera)
{
	mouse_hooks(window, camera);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->x += STEP;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->x -= STEP;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera->y -= STEP;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		camera->y += STEP;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->z += STEP;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->z -= STEP;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		ft_error(0);
}
