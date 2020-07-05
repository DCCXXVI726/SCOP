/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:33 by thorker           #+#    #+#             */
/*   Updated: 2020/07/05 18:34:36 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <fcntl.h>
#include <stdio.h>

/*
** Установка начальных значений
*/

void	init_object(t_obj *object)
{
	object->ind_size = 0;
	object->indices = NULL;
	object->ver_size = 0;
	object->vertices = NULL;
}

/*
** Создает объект(точки и треугольники из этих точек)
*/

t_obj	*create_object(char *file_name)
{
	int		fd;
	t_obj	*object;
	char	*line;
	int		gnl;

	if (file_name != 0 && (fd = open(file_name, O_RDONLY)) == -1)
		return (NULL);
	if ((object = (t_obj*)malloc(sizeof(t_obj))) != 0)
	{
		init_object(object);
		while ((gnl = get_next_line(fd, &line)) > 0)
		{
			if (*line == 'v')
				if ((gnl = add_vertices(line, object)) != 0)
					break ;
			if (*line == 'f')
				if ((gnl = add_indices(line, object)) != 0)
					break ;
			ft_strdel(&line);
		}
		if (gnl != 0)
			ft_delete_object(&object);
	}
	close(fd);
	return (object);
}
