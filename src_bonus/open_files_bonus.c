/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:29:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 03:30:15 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Release stdin (FD 0) so that it no longer refers to any file,
 * in order to make the next open() call on the input file return
 * FD 0 (lowest FD available).
 */
void	open_files(
			int **fds,
			int	argc,
			char **argv,
			t_strings *strings
			)
{
	int *infile_fd;
	int *outfile_fd;
	int	close_status;

	infile_fd = fds[0];
	outfile_fd = fds[1];
	close_status = close(0);
	check_error(close_status == -1, errno, "close() failed.\nError", strings);
	*infile_fd = open(argv[1], O_RDONLY);
	*outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
}
