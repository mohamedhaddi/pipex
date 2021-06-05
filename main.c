/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/05 21:04:57 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;

	// CREATE A PIPE
	// int pipe_fds[2];
	// pipe(pipe_fds);

	// TO-DO: ERROR MANAGEMENT
	/*
	if (argc != 5)
	{
		perror("Error\nThere should be five arguments:\n./pipex file1 first_cmd cmd2 file2");
		exit(EXIT_FAILURE);
	}
	*/

	// RELASE stdin AND OPEN ARGV[1]
	close(0); // release fd 0 so that it no longer refers to any file and may be reused
	open(argv[1], O_RDONLY); // open file with fd 0

	// FIND PATH AND IMPLEMENT INPUT REDIRECTION TO CMD1
	// find first cmd in env paths
	char **first_cmd = ft_split(argv[2], ' ');
	int i = 0;
	int path_fd = -1;
	char *full_path;
	while (envp[i] && path_fd == -1) {
		char **env_var = ft_split(envp[i], '='); // split var name and its paths value
		if (ft_strncmp("PATH", env_var[0], 5) == 0) {
			char **paths = ft_split(env_var[1], ':'); // split all paths in var
			int j = 0;
			// lookup actual path using open
			while (paths[j]) {
				full_path = ft_strjoin(paths[j], ft_strjoin("/", first_cmd[0]));
				path_fd = open(full_path, O_RDONLY);
				if (path_fd != -1)
					break ;
				j++;
			}
		}
		i++;
	}
	if (path_fd != -1)
	{
		close(path_fd); // not needed anymore
		execve(full_path, first_cmd, envp); // by default, programs reads from stdin (path_fd 0)
	}
	
	return (0);
}
