/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 15:30:27 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg_data	arg_data;
	int			infile_fd;
	int			outfile_fd;
	int			i;

	init_all_arg_data(&arg_data, argc, argv);
	i = 0;
	while (i < argc - arg_data.not_cmds)
	{
		set_command(
			arg_data.cmds[i], argv[i + arg_data.not_cmds - 1], &arg_data);
		i++;
	}
	open_files((int *[2]){&infile_fd, &outfile_fd}, argc, &arg_data);
	make_children(&outfile_fd, &arg_data, envp, argc);
	free_all_arg_data(&arg_data);
	return (EXIT_SUCCESS);
}
