/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:42:48 by thorker           #+#    #+#             */
/*   Updated: 2020/07/06 19:24:28 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**	Джаст мейн
**
**	Добавить чтение из файла
*/

int		main(int ac, char **av)
{
	t_scop	*scop;

	if (ac != 2)
		return (0);
	scop = create_struct();
	init_window(scop);
	scop->shader_program = create_program();
	scop->vve = create_vao_vbo(av[1]);
	if (create_texture("resources/cat.png", &(scop->texture)) != 0)
		ft_error(0);
	ft_loop(scop);
	ft_clear(scop);
	return (0);
}
