/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:31:20 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 13:00:07 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Create a pipe with pipe(), it fills in fields of the array
 * pipe_fd with two open FDs:
 * One for the read end of the pipe pipe_fd[0],
 * One for the write end of the pipe pipe_fd[1].
 * It returns either 0 for success or -1 in case of error.
 */
void	create_pipe(int *pipe_fd, t_arg_data *arg_data)
{
	int	pipe_status;

	pipe_status = pipe(pipe_fd);
	check_error(pipe_status == -1, errno, "pipe() failed.\nError", arg_data);
}
