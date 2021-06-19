/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:25:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 16:09:31 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst && !size)
		return (srclen);
	while (size > 1)
	{
		if (*src == '\0')
			break ;
		*(dst++) = *(src++);
		size--;
	}
	if (size)
		*dst = '\0';
	return (srclen);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && (*s1 || *s2))
	{
		if (*(unsigned char *)s1++ != *(unsigned char *)s2++)
			return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
		n--;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s1);
	ptr = malloc((sizeof(*ptr) * slen) + sizeof(*ptr));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, slen + 1);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc((sizeof(char) * len) + sizeof(char));
	if (!strjoin)
		return (NULL);
	while (*s1)
		strjoin[i++] = *(s1++);
	while (*s2)
		strjoin[i++] = *(s2++);
	strjoin[i] = '\0';
	return (strjoin);
}
