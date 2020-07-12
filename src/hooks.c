/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 18:06:40 by thorker           #+#    #+#             */
/*   Updated: 2020/07/12 19:13:38 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** обработка изменений мыши
*/

void	change_color(GLFWwindow *window, t_camera *camera)
{
	static float	last_time = 0;
	static float	last_procent = 0;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		last_time = glfwGetTime();
		camera->color_flag *= -1;
		last_procent = 1.0f - camera->procent_color;
		camera->procent_color = last_procent;
	}
	if (camera->procent_color < 1.0f)
	{
		camera->procent_color = last_procent + (glfwGetTime() - last_time) / 3;
		if (camera->procent_color > 1.0f)
			camera->procent_color = 1.0f;
	}
}

void	mouse_hooks(GLFWwindow *window, t_camera *camera)
{
	double			x;
	double			y;
	static int		flag = 1;
	static float	last_time = 0;

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		if ((flag = flag * -1) == 1)
			last_time = glfwGetTime();
	glfwGetCursorPos(window, &x, &y);
	if (flag != 1)
	{
		camera->tetta += (y - camera->last_y) * MOUSE_SENY;
		if (camera->tetta > M_PI / 2)
			camera->tetta = M_PI / 2;
		else if (camera->tetta < -M_PI / 2)
			camera->tetta = -M_PI / 2;
		camera->phi += (x - camera->last_x) * MOUSE_SENX;
	}
	else
	{
		camera->phi = camera->phi + glfwGetTime() - last_time;
		last_time = glfwGetTime();
	}
	camera->last_x = x;
	camera->last_y = y;
}

/*
** обработка нажатия клавиш
*/

void	hooks(GLFWwindow *window, t_camera *camera)
{
	change_color(window, camera);
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
