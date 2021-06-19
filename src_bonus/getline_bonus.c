/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:39:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 19:23:26 by mhaddi           ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t original_length, size_t new_length)
{
	void	*ptr_new;

	if (new_length == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_length));
	else if (new_length <= original_length)
		return (ptr);
	else
	{
		if (!ptr || new_length <= original_length)
			return (NULL);
		ptr_new = malloc(new_length);
		if (ptr_new)
		{
			ft_memcpy(ptr_new, ptr, original_length);
			free(ptr);
		}
		return (ptr_new);
	}
}

char	*ft_getline(void)
{
	char	*line;
	char	*line_prev;
	size_t	max_len;
	size_t	len;
	int		c;
	char	*line_next;

	line = malloc(100);
	if (line == NULL)
		return (NULL);
	line_prev = line;
	max_len = 100;
	len = max_len;
	while (1)
	{
		read(0, &c, 1);
		if (c == EOF)
			break ;
		if (--len == 0)
		{
			len = max_len;
			line_next = ft_realloc(line_prev, len, max_len * 2);
			max_len *= 2;
			if (line_next == NULL)
			{
				free(line_prev);
				return (NULL);
			}
			line = line_next + (line - line_prev);
			line_prev = line_next;
		}
		if ((*line++ = c) == '\n')
			break ;
	}
	*line = '\0';
	return (line_prev);
}
