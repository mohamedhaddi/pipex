/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raise_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:18:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 19:26:58 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    ft_raise_error(int errno_val, char *error_msg)
{
    errno = errno_val;
    perror(error_msg);
    exit(EXIT_FAILURE);
}
