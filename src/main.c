/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/14 15:38:58 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_strings	strings;
	int			infile_fd;
	int			outfile_fd;

	check_error(argc != 5,
		EINVAL,
		"There should be 4 arguments to your program, "
		"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError",
		&strings);
	init_all_strings(&strings, argc);
	int i = 0;
	while (i < (argc - 3))
	{
		set_command(strings.cmds[i], argv[i + 2], &strings);
		i++;
	}
	open_files(&infile_fd, &outfile_fd, argv, &strings);
	make_children(&outfile_fd, &strings, envp, argc);
	free_all_strings(&strings);
	return (0);
}
