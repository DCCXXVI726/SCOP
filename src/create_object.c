/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:33 by thorker           #+#    #+#             */
/*   Updated: 2020/03/03 04:37:09 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <fcntl.h>

/*
** Проверить object
*/

t_obj	*create_object(char *file_name)
{
	int		fd;
	t_obj	*object;
	char	*line;
	int		gnl;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return 0;
	if ((object = (t_obj*)malloc(sizeof(t_obj))) == 0)
	{
		close(fd);
		return 0;
	}
	object->ind_size = 0;
	object->indices = 0;
	object->ver_size = 0;
	object->vertices = 0;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		if (*line == 'v')
			if ((gnl = add_vertices(line, object)) != 0)
				break ;
		if (*line == 'f')
			if ((gnl = add_indices(line, object)) != 0)
				break ;
		free(line);
	}
	close(fd);
	return (object);
}
