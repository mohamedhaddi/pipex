/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:13:00 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 15:20:09 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*ft_char_calloc(size_t count)
{
	void	*ptr;
	int		i;

	i = 0;
	ptr = malloc(count);
	if (ptr)
	{
		while ((int)(count) > i)
		{
			*(char *)(ptr + i) = 0;
			i++;
		}
		return (ptr);
	}
	return (0);
}

