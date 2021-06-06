/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 07:23:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 19:04:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*ptr;
	int			i;
	int			j;

	if (!s2)
		return (0);
	if (!s1)
		s1 = malloc(1);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (*(s1 + i) != '\0')
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	while (*(s2 + j) != '\0')
		*(ptr + i++) = *(s2 + j++);
	*(ptr + i) = '\0';
	free(s1);
	return (ptr);
}
