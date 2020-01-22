/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:19:18 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/16 18:19:32 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void clean_buffer(char **buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		ft_strdel(&buffer[i]);
		i++;
	}
	i = 0;
	free(buffer);
}
