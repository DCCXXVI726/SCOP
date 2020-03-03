/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:42:48 by thorker           #+#    #+#             */
/*   Updated: 2020/03/02 23:18:30 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		main(int ac, char **av)
{
	t_scop	*scop;

	(void)av;
	(void)ac;
	scop = create_struct();
	init_window(scop);
	scop->shader_program = create_program();
	scop->vve = create_vao_vbo();
	ft_loop(scop);
	ft_clear(scop);
	return (0);
}
