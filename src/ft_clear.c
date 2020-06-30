/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:46:56 by thorker           #+#    #+#             */
/*   Updated: 2020/06/30 19:36:55 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Чистка основной структуры
*/

void	ft_clear(t_scop *scop)
{
	if (scop != 0)
	{
		glDeleteVertexArrays(1, &(scop->vve.vao));
		glDeleteBuffers(1, &(scop->vve.vbo));
		glDeleteBuffers(1, &(scop->vve.ebo));
	}
	glfwTerminate();
}
