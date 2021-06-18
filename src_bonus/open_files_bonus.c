/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:29:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/18 17:00:05 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
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
	char *input;
	char *line;

	infile_fd = fds[0];
	outfile_fd = fds[1];

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		input = malloc(sizeof(input));
		*input = '\0';
		while (1)
		{
			line = NULL;
			check_error(get_next_line(0, &line) == -1, 0, "get_next_line() failed.\nError", strings);
			if (ft_strncmp(argv[2], line, ft_strlen(argv[2])) == 0)
			{
				free(line);
				break;
			}
			input = ft_strjoin(input, line);
			free(line);
			check_error(!input, ENOMEM, "ft_strjoin() failed.\nError", strings);
		}
		close_status = close(0);
		check_error(close_status == -1, errno, "close() failed.\nError", strings);
		check_error(write(0, input, ft_strlen(input)) == -1, errno, "close() failed.\nError", strings);
		free(input);

		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		check_error(*outfile_fd == -1, errno, "Invalid file.\nError", strings);
	}
	else
	{
		close_status = close(0);
		check_error(close_status == -1, errno, "close() failed.\nError", strings);
		*infile_fd = open(argv[1], O_RDONLY);
		*outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		check_error(*outfile_fd == -1, errno, "Invalid file.\nError", strings);
	}
}
