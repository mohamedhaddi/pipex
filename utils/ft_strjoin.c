/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 07:23:43 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/07 02:31:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *strjoin;
    size_t  len;
    size_t  i;

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
