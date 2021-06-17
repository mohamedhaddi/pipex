/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:29:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 15:25:17 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/fcntl.h>
#include <unistd.h>

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
	char **line = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		while (ft_strncmp(argv[2], *line, ft_strlen(argv[2]) + 1) != 0)
		{
			get_next_line(0, line);
			write(1, line, ft_strlen(*line));
			//free(line);
		}
		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		check_error(*outfile_fd == -1, errno, "Invalid file.\nError", strings);
	}
	else
	{
		*infile_fd = open(argv[1], O_RDONLY);
		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		check_error(*outfile_fd == -1, errno, "Invalid file.\nError", strings);
	}
}
