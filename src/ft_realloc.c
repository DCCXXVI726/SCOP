/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:20:54 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 19:55:31 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Выделение новой памяти
** Копирование старой и новой памяти
** Удаление старой памяти
*/

void	*ft_realloc(void *old_mem,
		size_t old_size, void *add_mem, size_t add_size)
{
	void *new_mem;

	if ((new_mem = ft_memalloc(old_size + add_size)) == 0)
		return (NULL);
	ft_memcpy(new_mem + old_size, add_mem, add_size);
	if (old_mem != NULL)
	{
		ft_memcpy(new_mem, old_mem, old_size);
		free(old_mem);
	}
	return (new_mem);
}
