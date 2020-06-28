/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 14:37:16 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 20:14:58 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	Инициализация glfw, glew
**	создание окна
**	скрытие курсора
*/

int		init_window(t_scop *scop)
{
	double	x;
	double	y;

	if (glfwInit() == GLFW_FALSE)
		ft_error(GLFW_INIT_E);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if ((scop->window = glfwCreateWindow(WIN_W, WIN_H, WIN_NAME, 0, 0)) == 0)
		ft_error(GLFW_WIN_E);
	glfwMakeContextCurrent(scop->window);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glewInit() != GLEW_OK)
		ft_error(GLEW_INIT_E);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(scop->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(scop->window, &x, &y);
	scop->camera->last_x = x;
	scop->camera->last_y = y;
	return (0);
}
