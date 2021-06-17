/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 01:11:29 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	t_strings	strings;
	int			infile_fd;
	int			outfile_fd;
	int			i;

	init_all_strings(&strings, argc);
	check_error(argc != 5,
		EINVAL,
		"There should be 4 arguments to your program, "
		"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError",
		&strings);
	i = 0;
	while (i < (argc - 3))
	{
		set_command(strings.cmds[i], argv[i + 2], &strings);
		i++;
	}
	open_files(&infile_fd, &outfile_fd, argv, &strings);
	make_children(&outfile_fd, &strings, envp, argc);
	free_all_strings(&strings);
	return (EXIT_SUCCESS);
}
