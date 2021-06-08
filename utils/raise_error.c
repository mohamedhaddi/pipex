/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raise_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:18:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/08 15:49:22 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    raise_error(int errno_val, char *error_msg)
{
    errno = errno_val;
    perror(error_msg);
    exit(EXIT_FAILURE);
}
