/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 19:19:45 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_strings	strings;
	int			pipe_fd[2];
	int			infile_fd;
	int			outfile_fd;

	init_all_strings(&strings);
	check_error(argc != 5,
		EINVAL,
		"There should be 4 arguments to your program, "
		"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError",
		&strings);
	set_command(strings.first_cmd, argv[2], &strings);
	set_command(strings.second_cmd, argv[3], &strings);
	open_files(&infile_fd, &outfile_fd, argv, &strings);
	create_pipe(pipe_fd, &strings);
	make_children(pipe_fd, &outfile_fd, &strings, envp);
	return (0);
}
