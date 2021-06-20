/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:39:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 08:49:23 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_getline(void)
{
	char	c;
	char	*line;
	char	*tmp;

	line = malloc(1);
	*line = '\0';
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF)
			return (line);
		tmp = line;
		line = ft_strjoin(tmp, (char [2]){c, '\0'});
		free(tmp);
		if (c == '\n')
			return (line);
	}
}
