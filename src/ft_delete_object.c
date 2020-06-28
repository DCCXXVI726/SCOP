/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 17:33:44 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 18:18:48 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**  Очистка объекта
*/

void	ft_delete_object(t_obj **object)
{
	ft_memdel((void**)&((*object)->indices));
	ft_memdel((void**)&((*object)->vertices));
	ft_memdel((void**)object);
}
