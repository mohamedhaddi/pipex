/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_pointer_and_init.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 19:16:02 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 15:21:56 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    free_double_pointer_and_init(char **ptr, int *state)
{
    int i;

    i = 0;
    while (ptr[i])
        free_and_init(ptr[i++], state);
    free(ptr);
    *state = 0;
}
