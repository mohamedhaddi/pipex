/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:29:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 17:14:09 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc_loop(t_here_doc_data *here_doc_data, t_arg_data *arg_data)
{
	char	*tmp;

	here_doc_data->line = ft_getline();
	check_error_here_doc((int [2]){!here_doc_data->line, 0},
		"ft_getline() failed.\nError", here_doc_data, arg_data);
	here_doc_data->line_state = 1;
	here_doc_data->limiter = ft_strjoin(arg_data->argv[2], "\n");
	check_error_here_doc((int [2]){!here_doc_data->limiter, 0},
		"ft_strjoin() failed.\nError", here_doc_data, arg_data);
	here_doc_data->limiter_state = 1;
	if (ft_strncmp(here_doc_data->limiter, here_doc_data->line,
			ft_strlen(arg_data->argv[2])) == 0)
		return (1);
	free_and_init(here_doc_data->limiter, &here_doc_data->limiter_state);
	tmp = ft_strdup(here_doc_data->input);
	check_error_here_doc((int [2]){!tmp, 0},
		"ft_strdup() failed.\nError", here_doc_data, arg_data);
	free_and_init(here_doc_data->input, &here_doc_data->input_state);
	here_doc_data->input = ft_strjoin(tmp, here_doc_data->line);
	check_error_here_doc((int [2]){!here_doc_data->input, 0},
		"ft_strjoin() failed.\nError", here_doc_data, arg_data);
	here_doc_data->input_state = 1;
	free(tmp);
	free_and_init(here_doc_data->line, &here_doc_data->line_state);
	return (0);
}

void	create_here_doc_infile(int *infile_fd,
							t_here_doc_data *here_doc_data,
							t_arg_data *arg_data)
{
	int	write_status;
	int	close_status;

	free_and_init(here_doc_data->line, &here_doc_data->line_state);
	free_and_init(here_doc_data->limiter, &here_doc_data->limiter_state);
	*infile_fd = open("infile", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	write_status = write(
			*infile_fd, here_doc_data->input, ft_strlen(here_doc_data->input));
	check_error_here_doc((int [2]){write_status == -1, errno},
		"write() failed.\nError",
		here_doc_data,
		arg_data);
	free_and_init(here_doc_data->input, &here_doc_data->input_state);
	close(*infile_fd);
	close_status = close(0);
	check_error(close_status == -1, errno, "close() failed.\nError", arg_data);
	*infile_fd = open("infile", O_RDONLY);
}

void	do_here_doc(int **fds,
					int argc,
					t_here_doc_data *here_doc_data,
					t_arg_data *arg_data)
{
	int	*infile_fd;
	int	*outfile_fd;

	infile_fd = fds[0];
	outfile_fd = fds[1];
	here_doc_data->input = malloc(sizeof(here_doc_data->input));
	check_error_here_doc((int [2]){!here_doc_data->input, ENOMEM},
		"malloc() failed.\nError",
		here_doc_data,
		arg_data);
	here_doc_data->input_state = 1;
	*here_doc_data->input = '\0';
	while (1)
		if (here_doc_loop(here_doc_data, arg_data))
			break ;
	create_here_doc_infile(infile_fd, here_doc_data, arg_data);
	*outfile_fd = open(
			arg_data->argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	check_error(*outfile_fd == -1, errno, "Invalid file.\nError", arg_data);
}

/**
 * Release stdin (FD 0) so that it no longer refers to any file,
 * in order to make the next open() call on the input file return
 * FD 0 (lowest FD available).
 */
void	open_files(int **fds, int argc, t_arg_data *arg_data)
{
	int				*infile_fd;
	int				*outfile_fd;
	int				close_status;
	t_here_doc_data	here_doc_data;

	infile_fd = fds[0];
	outfile_fd = fds[1];
	if (arg_data->not_cmds == 4)
	{
		init_all_here_doc_data(&here_doc_data);
		do_here_doc(
			(int *[2]){infile_fd, outfile_fd}, argc, &here_doc_data, arg_data);
	}
	else
	{
		close_status = close(0);
		check_error(
			close_status == -1, errno, "close() failed.\nError", arg_data);
		*infile_fd = open(arg_data->argv[1], O_RDONLY);
		*outfile_fd = open(
				arg_data->argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		check_error(*outfile_fd == -1, errno, "Invalid file.\nError", arg_data);
	}
}
