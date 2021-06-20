/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:26 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/14 13:18:41 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			t_arg_data *arg_data
			)
{
	if (is_error)
	{
		free_all_arg_data(arg_data);
		raise_error(errno_val, error_msg);
	}
}
