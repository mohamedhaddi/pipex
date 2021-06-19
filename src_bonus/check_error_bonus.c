/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:26 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 14:24:09 by mhaddi           ###   ########.fr       */
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
			t_arg_data *arg_data
			)
{
	if (is_error)
	{
		free_all_arg_data(arg_data);
		raise_error(errno_val, error_msg);
	}
}

void	check_error_here_doc(int *error_data,
							char *error_msg,
							t_here_doc_data *here_doc_data,
							t_arg_data *arg_data)
{
	bool	is_error;
	int		errno_val;

	is_error = error_data[0];
	errno_val = error_data[1];
	if (is_error)
	{
		free_all_arg_data(arg_data);
		free_all_here_doc_data(here_doc_data);
		raise_error(errno_val, error_msg);
	}
}
