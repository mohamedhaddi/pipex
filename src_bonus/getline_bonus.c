/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:39:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 19:06:08 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n)
	{
		if (*(unsigned char *)(s1++) != *(unsigned char *)(s2++))
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
		n--;
	}
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	len;

	if ((!dst && !src) || (!dst && !n))
		return (NULL);
	if (!src && !n)
		return (dst);
	if (!ft_memcmp(dst, src, n))
		return (dst);
	len = n;
	while (len)
	{
		*(char *)(dst++) = *(char *)(src++);
		len--;
	}
	return (dst - n);
}

void	*ft_realloc(void *ptr, size_t originalLength, size_t newLength)
{
	void	*ptrNew;

	if (newLength == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(newLength));
	else if (newLength <= originalLength)
		return (ptr);
	else
	{
		if (!ptr || newLength <= originalLength)
			return (NULL);
		ptrNew = malloc(newLength);
		if (ptrNew)
		{
			ft_memcpy(ptrNew, ptr, originalLength);
			free(ptr);
		}
		return (ptrNew);
	}
}

char	*ft_getline(void)
{
	char	*line;
	char	*linep;
	size_t	lenmax;
	size_t	len;
	int		c;
	char	*linen;

	line = malloc(100);
	if (line == NULL)
		return (NULL);
	linep = line;
	lenmax = 100;
	len = lenmax;
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF)
			break ;
		if (--len == 0)
		{
			len = lenmax;
			linen = ft_realloc(linep, len, lenmax * 2);
			lenmax *= 2;
			if (linen == NULL)
			{
				free(linep);
				return (NULL);
			}
			line = linen + (line - linep);
			linep = linen;
		}
		if ((*line++ = c) == '\n')
			break ;
	}
	*line = '\0';
	return (linep);
}
