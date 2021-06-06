/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 00:04:54 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 19:03:51 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
