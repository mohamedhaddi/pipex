/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:39:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/18 16:51:59 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int get_next_line(int fd, char **line)
{
	char *tmp;

	tmp = malloc(sizeof(tmp) * 2);
	*tmp = '\0';
	while (*tmp != '\n' && *tmp != EOF)
	{
		if (read(fd, tmp, 1) == -1)
		{
			free(tmp);
			return (-1);
		}
		tmp[1] = '\0';
		*line = ft_strjoin(*line, tmp);
	}
	free(tmp);
	return (0);
}
