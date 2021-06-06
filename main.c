/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 16:39:21 by mhaddi           ###   ########.fr       */
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

	// TO-DO: ERROR MANAGEMENT
	/*
	if (argc != 5)
	{
		perror("Error\nThere should be five arguments:\n./pipex file1 first_cmd cmd2 file2");
		exit(EXIT_FAILURE);
	}
	*/

	// find first and second cmds in env paths
	char **first_cmd = ft_split(argv[2], ' ');
	char **second_cmd = ft_split(argv[3], ' ');
	int i = 0;
	int first_cmd_path_fd = -1;
	int second_cmd_path_fd = -1;
	char *first_cmd_full_path;
	char *second_cmd_full_path;
	while (envp[i]) {
		char **env_var = ft_split(envp[i], '='); // split var name and its paths value
		if (ft_strncmp("PATH", env_var[0], 5) == 0) {
			char **paths = ft_split(env_var[1], ':'); // split all paths in var
			int j = 0;
			while (paths[j]) { // lookup actual path for each command using open
				if (first_cmd_path_fd == -1)
				{
					first_cmd_full_path = ft_strjoin(paths[j], ft_strjoin("/", first_cmd[0]));
					first_cmd_path_fd = open(first_cmd_full_path, O_RDONLY);
					close(first_cmd_path_fd); // not needed anymore
				}
				if (second_cmd_path_fd == -1)
				{
					second_cmd_full_path = ft_strjoin(paths[j], ft_strjoin("/", second_cmd[0]));
					second_cmd_path_fd = open(second_cmd_full_path, O_RDONLY);
					close(second_cmd_path_fd); // not needed anymore
				}
				if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
					break ;
				j++;
			}
		}
		if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
			break ;
		i++;
	}

	if (first_cmd_path_fd == -1 || second_cmd_path_fd == -1)
	{
		fprintf(stderr, "cmd not found");
		exit(EXIT_FAILURE);
	}

	// RELASE stdin AND OPEN ARGV[1]
	close(0); // release fd 0 so that it no longer refers to any file and may be reused
	open(argv[1], O_RDONLY); // open file with fd 0

	// CREATE A PIPE
	int pipe_fd[2];
	pipe(pipe_fd);	// returns two open fds in pipe_fd[]:
					// one for the read end of the pipe pipe_fd[0]
					// one for the write end of the pipe pipe_fd[1]
					// or -1 in case of error

	if (fork() == 0)
	{
		dup2(pipe_fd[1], 1); // remap output back to parent
		execve(first_cmd_full_path, first_cmd, envp);	// by default, programs reads
														// from stdin (path_fd 0)
		// exit() not needed since execve replaces the process with another program
	}

	// remap output from previous child to input
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]); // we don't wanna write again into the pipe
	close(pipe_fd[0]); // not necessary, it's just the read end
	execve(second_cmd_full_path, second_cmd, envp); // by default, programs reads
													// from stdin (path_fd 0)

	return (0);
}
