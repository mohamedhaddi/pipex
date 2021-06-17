/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:25:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 15:27:46 by mhaddi           ###   ########.fr       */
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

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && (*s1 || *s2))
    {
        if (*(unsigned char *)s1++ != *(unsigned char *)s2++)
            return (*(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1));
        n--;
    }
    return (0);
}

char    *ft_strdup(const char *s1)
{
    char    *ptr;
    size_t  slen;

    slen = ft_strlen(s1);
    ptr = malloc((sizeof(*ptr) * slen) + sizeof(*ptr));
    if (!ptr)
        return (NULL);
    ft_strlcpy(ptr, s1, slen + 1);
    return (ptr);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t          j;
    char            *substr;
    size_t          slen;

    if (!s)
        return (NULL);
    slen = ft_strlen(s);
    if (start > slen || !len || !*s)
        return (ft_strdup(""));
    j = 0;
    if (len > slen - start)
        len = slen - start;
    substr = malloc((sizeof(*substr) * len) + sizeof(*substr));
    if (!substr)
        return (NULL);
    s += start;
    while (*s && j < len)
        substr[j++] = *(s++);
    substr[j] = '\0';
    return (substr);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char        *ptr;
    int         i;
    int         j;

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
