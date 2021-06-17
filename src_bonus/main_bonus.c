/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 14:42:18 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_strings	strings;
	int			infile_fd;
	int			outfile_fd;
	int			i;
	int			subtrahend;

	init_all_strings(&strings, argc, argv);
	check_error(argc < 5,
		EINVAL,
		"There should be at least 4 arguments to your program, "
		"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError",
		&strings);
	i = 0;
	subtrahend = 3;	
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		subtrahend = 4;	
	while (i < (argc - subtrahend))
	{
		set_command(strings.cmds[i], argv[i + 2], &strings);
		i++;
	}
	open_files((int *[2]){&infile_fd, &outfile_fd}, argc, argv, &strings);
	make_children(&outfile_fd, &strings, envp, argc);
	free_all_strings(&strings);
	return (EXIT_SUCCESS);
}
