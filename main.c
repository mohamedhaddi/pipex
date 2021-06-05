/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/05 17:32:53 by mhaddi           ###   ########.fr       */
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
	int pipe_fds[2];

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
	// child process
	//int first_pid = fork();
	//if (first_pid == 0)
	//{
	char **first_cmd = ft_split(argv[2], ' ');
	int i = 0;
	while (envp[i]) {
		char **var = ft_split(envp[i], '=');
		if (ft_strncmp("PATH", var[0], 5) == 0) {
			char **paths = ft_split(var[1], ':');
			int j = 0;
			int path_fd = -1;
			char *full_path;
			while (paths[j] && path_fd == -1) {
				full_path = ft_strjoin(paths[j], ft_strjoin("/", first_cmd[0]));
				path_fd = open(full_path, O_RDONLY);
				if (path_fd != -1)
					break ;
				j++;
			}
			if (path_fd != -1 && full_path)
			{
				close(path_fd);
				//first_cmd[0] = full_path;
				execve(full_path, first_cmd, envp); // by default, programs reads from stdin (path_fd 0)
			}
		}
		i++;
	}
	//}
	//waitpid(first_pid, NULL, 0);
	
	// CREATE A PIPE
	pipe(pipe_fds);


	return (0);
}
