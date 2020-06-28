/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shader_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 19:12:19 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 20:14:21 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	Читает код из файла
*/

char	*get_shader_code(char *name)
{
	int		file;
	char	*line;
	int		max_buff;

	max_buff = 65534;
	if ((file = open(name, O_RDONLY)) < 0)
		return (NULL);
	if ((line = (char*)malloc(max_buff)) == 0)
	{
		close(file);
		return (NULL);
	}
	if (read(file, line, max_buff) == -1)
		ft_strdel(&line);
	close(file);
	return (line);
}
