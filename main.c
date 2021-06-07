/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/07 02:49:19 by mhaddi           ###   ########.fr       */
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
	int pipe_fd[2];
	int pipe_status;
	pid_t child_a;
	int dup2_fd;
	int exec_status;
	pid_t child_b;
	int close_status;

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
	if (first_cmd == NULL)
		ft_raise_error(ENOMEM, "ft_split() failed.\nError");

	/**
	 * Get the second command and its parameters if there are any.
	 */
	second_cmd = ft_split(argv[3], ' ');
	if (second_cmd == NULL)
	{
		ft_free_double_pointer(first_cmd);
		ft_raise_error(ENOMEM, "ft_split() failed.\nError");
	}

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
	first_cmd_full_path = malloc(sizeof(first_cmd_full_path));
	second_cmd_full_path = malloc(sizeof(second_cmd_full_path));
	while (envp[i]) {
		env_var = ft_split(envp[i], '=');
		if (env_var == NULL)
		{
			ft_free_double_pointer(first_cmd);
			ft_free_double_pointer(second_cmd);
			ft_raise_error(ENOMEM, "ft_split() failed.\nError");
		}
		path_var_found = ft_strncmp("PATH", env_var[0], 5) == 0;
		if (path_var_found) {
			paths = ft_split(env_var[1], ':');
			if (paths == NULL)
			{
				ft_free_double_pointer(first_cmd);
				ft_free_double_pointer(second_cmd);
				ft_free_double_pointer(env_var);
				ft_raise_error(ENOMEM, "ft_split() failed.\nError");
			}
			j = 0;
			while (paths[j]) {
				if (first_cmd_path_fd == -1)
				{
					slash_cmd = ft_strjoin("/", first_cmd[0]);
					if (slash_cmd == NULL)
					{
						ft_free_double_pointer(first_cmd);
						ft_free_double_pointer(second_cmd);
						ft_free_double_pointer(env_var);
						ft_free_double_pointer(paths);
						free(second_cmd_full_path);
						ft_raise_error(ENOMEM, "ft_strjoin() failed.\nError");
					}
					first_cmd_full_path = ft_strjoin(paths[j], slash_cmd);
					if (first_cmd_full_path == NULL)
					{
						ft_free_double_pointer(first_cmd);
						ft_free_double_pointer(second_cmd);
						ft_free_double_pointer(env_var);
						ft_free_double_pointer(paths);
						free(slash_cmd);
						free(second_cmd_full_path);
						ft_raise_error(ENOMEM, "ft_strjoin() failed.\nError");
					}
					free(slash_cmd);
					first_cmd_path_fd = open(first_cmd_full_path, O_RDONLY);
					close(first_cmd_path_fd);
				}
				if (second_cmd_path_fd == -1)
				{
					slash_cmd = ft_strjoin("/", second_cmd[0]);
					if (slash_cmd == NULL)
					{
						ft_free_double_pointer(first_cmd);
						ft_free_double_pointer(second_cmd);
						ft_free_double_pointer(env_var);
						ft_free_double_pointer(paths);
						free(first_cmd_full_path);
						ft_raise_error(ENOMEM, "ft_strjoin() failed.\nError");
					}
					second_cmd_full_path = ft_strjoin(paths[j], slash_cmd);
					if (second_cmd_full_path == NULL)
					{
						ft_free_double_pointer(first_cmd);
						ft_free_double_pointer(second_cmd);
						ft_free_double_pointer(env_var);
						ft_free_double_pointer(paths);
						free(slash_cmd);
						free(first_cmd_full_path);
						ft_raise_error(ENOMEM, "ft_strjoin() failed.\nError");
					}
					free(slash_cmd);
					second_cmd_path_fd = open(second_cmd_full_path, O_RDONLY);
					close_status = close(second_cmd_path_fd);
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
	if (first_cmd_path_fd == -1 || second_cmd_path_fd == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(EINVAL, "Command not found.\nError");
	}

	/**
	 * Release STDIN (FD 0) so that it no longer refers to any file,
	 * in order to make the next open() call on the input file return
	 * FD 0 (lowest FD available).
	 */
	close_status = close(0);
	if (close_status == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(errno, "close() failed.\nError");
	}

	int infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(ENOENT, "Input file invalid.\nError");
	}

	int outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile_fd == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(ENOENT, "Couldn't open/create output file.\nError");
	}

	/**
	 * Create a pipe with pipe(), it fills in fields of the array
	 * pipe_fd with two open FDs:
	 * One for the read end of the pipe pipe_fd[0],
	 * One for the write end of the pipe pipe_fd[1].
	 * It returns either 0 for success or -1 in case of error.
	 */
	pipe_status = pipe(pipe_fd);
	if (pipe_status == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(errno, "pipe() failed.\nError");
	}

	child_a = fork();
	if (child_a == -1)
	{
		free(first_cmd);
		free(second_cmd);
		free(first_cmd_full_path);
		free(second_cmd_full_path);
		ft_raise_error(errno, "fork() failed.\nError");
	}
	else if (child_a == 0) // child process
	{
		dup2_fd = dup2(pipe_fd[1], 1); // remap output back to parent
		if (dup2_fd == -1)
		{
			free(first_cmd);
			free(second_cmd);
			free(first_cmd_full_path);
			free(second_cmd_full_path);
			ft_raise_error(errno, "dup2() failed.\nError");
		}
		exec_status = execve(first_cmd_full_path, first_cmd, envp);
		/** by default, programs reads from stdin (path_fd 0) exit()
		 * not needed since execve replaces the process with another program
		 */
		if (exec_status == -1)
		{
			free(first_cmd);
			free(second_cmd);
			free(first_cmd_full_path);
			free(second_cmd_full_path);
			ft_raise_error(errno, "execve() failed.\nError");
		}
	}
	else // parent process
	{
		child_b = fork();
		if (child_b == -1)
		{
			free(first_cmd);
			free(second_cmd);
			free(first_cmd_full_path);
			free(second_cmd_full_path);
			ft_raise_error(errno, "fork() failed.\nError");
		}
		free(first_cmd);
		free(first_cmd_full_path);
		if (child_b == 0) // child process
		{
			// remap output from previous child to input
			dup2_fd = dup2(pipe_fd[0], 0);
			if (dup2_fd == -1)
			{
				free(second_cmd);
				free(second_cmd_full_path);
				ft_raise_error(errno, "dup2() failed.\nError");
			}
			close_status = close(pipe_fd[1]); // we don't wanna write again into the pipe
			if (close_status == -1)
			{
				free(second_cmd);
				free(second_cmd_full_path);
				ft_raise_error(errno, "close() failed.\nError");
			}
			close_status = close(pipe_fd[0]); // not necessary, it's just the read end
			if (close_status == -1)
			{
				free(second_cmd);
				free(second_cmd_full_path);
				ft_raise_error(errno, "close() failed.\nError");
			}
			dup2_fd = dup2(outfile_fd, 1);
			if (dup2_fd == -1)
			{
				free(second_cmd);
				free(second_cmd_full_path);
				ft_raise_error(errno, "dup2() failed.\nError");
			}
			exec_status = execve(second_cmd_full_path, second_cmd, envp);
			/** by default, programs reads from stdin (path_fd 0) exit()
			 * not needed since execve replaces the process with another program
			 */
			if (exec_status == -1)
			{
				free(second_cmd);
				free(second_cmd_full_path);
				ft_raise_error(errno, "execve() failed.\nError");
			}
		}
		else // parent process
		{
			free(second_cmd);
			free(second_cmd_full_path);
		}
	}

	/**
	 * Code here would be shared between all the processes (I guess).
	 */

	return (0);
}
