/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:18:13 by thorker           #+#    #+#             */
/*   Updated: 2020/07/06 19:22:59 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Считывает и загружает текстуру в OPENGL
*/

int	create_texture(char *image_name, GLuint *texture)
{
	SDL_Surface	*image;

	if (image_name == NULL || (image = IMG_Load(image_name)) == 0)
		return (-1);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (0);
}
