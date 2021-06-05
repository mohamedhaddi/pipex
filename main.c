/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/05 23:35:19 by mhaddi           ###   ########.fr       */
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

	// RELASE stdin AND OPEN ARGV[1]
	close(0); // release fd 0 so that it no longer refers to any file and may be reused
	open(argv[1], O_RDONLY); // open file with fd 0

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
				}
				if (second_cmd_path_fd == -1)
				{
					second_cmd_full_path = ft_strjoin(paths[j], ft_strjoin("/", second_cmd[0]));
					second_cmd_path_fd = open(second_cmd_full_path, O_RDONLY);
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

	// CREATE A PIPE
	int pipe_fd[2];
	pipe(pipe_fd);  // Creates a pipe with file descriptors Eg.
					// input = 3 and output = 4 (Since, 0,1 and 2 are not available)

	if (first_cmd_path_fd == -1 || second_cmd_path_fd == -1)
	{
		fprintf(stderr, "cmd not found");
		exit(EXIT_FAILURE);
	}

	if (fork() == 0)
	{
		// child process
		close(0); // release fd 0
		close(pipe_fd[0]); // close pipe fds since useful one is duplicated
		close(pipe_fd[1]);
		dup(pipe_fd[0]); // create duplicate of pipe reading end fd to fd 0
		close(second_cmd_path_fd); // not needed anymore
		execve(second_cmd_full_path, second_cmd, envp); // by default, programs reads
														// from stdin (path_fd 0)
	}
	else
	{
		// parent process
		close(1); // release fd 1
		close(pipe_fd[0]); // close pipe fds since useful one is duplicated
		close(pipe_fd[1]);
		dup2(pipe_fd[1], 1); // create duplicate of pipe writing end fd to fd 1
		close(first_cmd_path_fd); // not needed anymore
		execve(first_cmd_full_path, first_cmd, envp); // by default, programs reads
														// from stdin (path_fd 0)
	}

	return (0);
}
