/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:39:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 14:27:40 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**ft_reallocate(char **old_map, int i)
{
	char	**new_map;
	int		j;

	j = 0;
	new_map = (char **)malloc((i + 1) * sizeof(char *));
	while (j < i)
	{
		new_map[j] = old_map[j];
		j++;
	}
	new_map[j] = 0;
	free(old_map);
	return (new_map);
}

char		*ft_getline(void)
{
	char	*line;
	char	*linep;
	size_t	lenmax;
	size_t	len;
	int		c;
	char	**linen;

	line = malloc(100);
	linep = line;
	lenmax = 100;
	len = lenmax;
	if (line == NULL)
		return (NULL);
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF)
			break ;
		if (--len == 0)
		{
			len = lenmax;
			linen = ft_reallocate(&linep, lenmax *= 2);
			if (*linen == NULL)
			{
				free(linep);
				return (NULL);
			}
			line = *linen + (line - linep);
			linep = *linen;
		}
		if ((*line++ = c) == '\n')
			break ;
	}
	*line = '\0';
	return (linep);
}
