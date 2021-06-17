/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:26 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 02:53:17 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	raise_error(int errno_val, char *error_msg)
{
	errno = errno_val;
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	check_error(
			bool is_error,
			int errno_val,
			char *error_msg,
			t_strings *strings
			)
{
	if (is_error)
	{
		free_all_strings(strings);
		raise_error(errno_val, error_msg);
	}
}
