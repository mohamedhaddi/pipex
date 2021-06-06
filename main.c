/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 21:57:42 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char **first_cmd;
	char **second_cmd;
	int i;
	int first_cmd_path_fd;
	int second_cmd_path_fd;
	char *first_cmd_full_path;
	char *second_cmd_full_path;
	bool path_var_found;
	char **env_var;
	char **paths;
	int j;
	char *slash_cmd;

	/**
	 * Check number of arguments.
	 */
	if (argc != 5)
		ft_raise_error(EINVAL,
				"There should be 4 arguments to your program, \
				e.g.:\n./pipex file1 cmd1 cmd2 file2\nError");

	/**
	 * Get the first command and its parameters if there are any.
	 */
	first_cmd = ft_split(argv[2], ' ');

	/**
	 * Get the second command and its parameters if there are any.
	 */
	second_cmd = ft_split(argv[3], ' ');

	/**
	 * Loop through the environment variables until PATH is found.
	 * Then loop through the PATH paths, until the path for each
	 * command is found.
	 * (Path is checked with open(), if a valid FD is returned,
	 * it means that the file was succesfully opened (command is found.))
	 */
	i = 0;
	first_cmd_path_fd = -1;
	second_cmd_path_fd = -1;
	while (envp[i]) {
		env_var = ft_split(envp[i], '=');
		path_var_found = ft_strncmp("PATH", env_var[0], 5) == 0;
		if (path_var_found) {
			paths = ft_split(env_var[1], ':');
			j = 0;
			while (paths[j]) {
				if (first_cmd_path_fd == -1)
				{
					slash_cmd = ft_strjoin("/", first_cmd[0]);
					first_cmd_full_path = ft_strjoin(paths[j], slash_cmd);
					free(slash_cmd);
					first_cmd_path_fd = open(first_cmd_full_path, O_RDONLY);
					close(first_cmd_path_fd);
				}
				if (second_cmd_path_fd == -1)
				{
					slash_cmd = ft_strjoin("/", second_cmd[0]);
					second_cmd_full_path = ft_strjoin(paths[j], slash_cmd);
					free(slash_cmd);
					second_cmd_path_fd = open(second_cmd_full_path, O_RDONLY);
					close(second_cmd_path_fd);
				}
				if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
					break ;
				j++;
			}
			ft_free_double_pointer(paths);
		}
		ft_free_double_pointer(env_var);
		if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
			break ;
		else if (path_var_found)
			break ;
		i++;
	}
	free(first_cmd);
	free(second_cmd);
	if (first_cmd_path_fd == -1 || second_cmd_path_fd == -1)
	{
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(EINVAL, "Command not found.\nError");
	}

	/**
	 * Release STDIN (FD 0) so that it no longer refers to any file,
	 * in order to make the next open() call on the input file return
	 * FD 0 (lowest FD available).
	 */
	close(0);
	int infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(ENOENT, "Input file invalid.\nError");
	}

	int outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile_fd == -1)
	{
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(ENOENT, "Couldn't open/create output file.\nError");
	}

	// CREATE A PIPE
	int pipe_fd[2];
	pipe(pipe_fd);	// returns two open fds in pipe_fd[]:
					// one for the read end of the pipe pipe_fd[0]
					// one for the write end of the pipe pipe_fd[1]
					// or -1 in case of error

	pid_t child_a = fork();
	if (child_a == 0) // child process
	{
		dup2(pipe_fd[1], 1); // remap output back to parent
		execve(first_cmd_full_path, first_cmd, envp);	// by default, programs reads
														// from stdin (path_fd 0)
		// exit() not needed since execve replaces the process with another program
	}
	else // parent process
	{
		free(first_cmd_full_path);
		pid_t child_b = fork();
		if (child_b == 0) // child process
		{
			// remap output from previous child to input
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]); // we don't wanna write again into the pipe
			close(pipe_fd[0]); // not necessary, it's just the read end
			dup2(outfile_fd, 1);
			execve(second_cmd_full_path, second_cmd, envp); // by default, programs reads
															// from stdin (path_fd 0)
			// exit() not needed since execve replaces the process with another program
		}
		else // parent process
			free(second_cmd_full_path);
		//else { // parent process
		//	dup2(pipe_fd[0], 0);
		//	close(pipe_fd[1]); // we don't wanna write again into the pipe
		//	close(pipe_fd[0]); // not necessary, it's just the read end
		//}
	}

	//shared code
	//printf("test shared\n");

	return (0);
}
