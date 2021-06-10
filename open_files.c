/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:29:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:33:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Release stdin (FD 0) so that it no longer refers to any file,
 * in order to make the next open() call on the input file return
 * FD 0 (lowest FD available).
 */
void	open_files(
			int *infile_fd,
			int *outfile_fd,
			char **argv,
			t_strings *strings
			)
{
	int	close_status;

	close_status = close(0);
	check_error(close_status == -1, errno, "close() failed.\nError", strings);
	*infile_fd = open(argv[1], O_RDONLY);
	check_error(*infile_fd == -1, errno, "Input file invalid.\nError", strings);
	*outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_error(*outfile_fd == -1,
		errno,
		"Couldn't open/create output file.\nError",
		strings);
}
