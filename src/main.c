/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 09:43:27 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg_data	arg_data;
	int			infile_fd;
	int			outfile_fd;
	int			i;

	init_all_arg_data(&arg_data, argc);
	check_error(argc != 5,
		EINVAL,
		"There should be 4 arguments to your program, "
		"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError",
		&arg_data);
	i = 0;
	while (i < (argc - 3))
	{
		set_command(arg_data.cmds[i], argv[i + 2], &arg_data);
		i++;
	}
	open_files(&infile_fd, &outfile_fd, argv, &arg_data);
	make_children(&outfile_fd, &arg_data, envp);
	free_all_arg_data(&arg_data);
	return (EXIT_SUCCESS);
}
