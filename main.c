/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/08 16:16:57 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

typedef struct	s_strings
{
	char **first_cmd;
	char **second_cmd;
	char *first_cmd_full_path;
	char *second_cmd_full_path;
	char **env_var;
	char **paths;
	char *slash_cmd;
}				t_strings;

void	init_all_strings(t_strings *strings)
{
	strings->first_cmd = NULL;
	strings->second_cmd = NULL;
	strings->first_cmd_full_path = NULL;
	strings->second_cmd_full_path = NULL;
	strings->env_var = NULL;
	strings->paths = NULL;
	strings->slash_cmd = NULL;
}

void	free_all_strings(t_strings *strings)
{
	if (strings->first_cmd)
		free_double_pointer_and_init(strings->first_cmd);
	if (strings->second_cmd)
		free_double_pointer_and_init(strings->second_cmd);
	if (strings->first_cmd_full_path)
		free_and_init(strings->first_cmd_full_path);
	if (strings->second_cmd_full_path)
		free_and_init(strings->second_cmd_full_path);
	if (strings->env_var)
		free_double_pointer_and_init(strings->env_var);
	if (strings->paths)
		free_double_pointer_and_init(strings->paths);
	if (strings->slash_cmd)
		free_and_init(strings->slash_cmd);
}

void	check_error(bool is_error, int errno_val, char *error_msg, t_strings *strings)
{
	if (is_error)
	{
		free_all_strings(strings);
		raise_error(errno_val, error_msg);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_strings strings;
	int i;
	int first_cmd_path_fd;
	int second_cmd_path_fd;
	bool path_var_found;
	int j;
	int pipe_fd[2];
	int pipe_status;
	pid_t child_a;
	int dup2_fd;
	int exec_status;
	pid_t child_b;
	int close_status;

	init_all_strings(&strings);

	/**
	 * Check number of arguments.
	 */
	check_error(argc != 5, EINVAL, "There should be 4 arguments to your program, "
				"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError", &strings);

	/**
	 * Get the first command and its parameters if there are any.
	 */
	strings.first_cmd = ft_split(argv[2], ' ');
	check_error(strings.first_cmd == NULL, ENOMEM, "ft_split() failed.\nError", &strings);

	/**
	 * Get the second command and its parameters if there are any.
	 */
	strings.second_cmd = ft_split(argv[3], ' ');
	check_error(strings.second_cmd == NULL, ENOMEM, "ft_split() failed.\nError", &strings);

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
		strings.env_var = ft_split(envp[i], '=');
		check_error(strings.env_var == NULL, ENOMEM, "ft_split() failed.\nError", &strings);

		path_var_found = ft_strncmp("PATH", strings.env_var[0], 5) == 0;
		if (path_var_found) {
			strings.paths = ft_split(strings.env_var[1], ':');
			check_error(strings.paths == NULL, ENOMEM, "ft_split() failed.\nError", &strings);

			j = 0;
			while (strings.paths[j]) {
				if (first_cmd_path_fd == -1)
				{
					strings.slash_cmd = ft_strjoin("/", strings.first_cmd[0]);
					check_error(strings.slash_cmd == NULL, ENOMEM, "ft_strjoin() failed.\nError", &strings);

					free_and_init(strings.first_cmd_full_path);
					strings.first_cmd_full_path = ft_strjoin(strings.paths[j], strings.slash_cmd);
					check_error(strings.first_cmd_full_path == NULL, ENOMEM, "ft_strjoin() failed.\nError", &strings);

					free_and_init(strings.slash_cmd);
					first_cmd_path_fd = open(strings.first_cmd_full_path, O_RDONLY);
					close(first_cmd_path_fd);
				}
				if (second_cmd_path_fd == -1)
				{
					strings.slash_cmd = ft_strjoin("/", strings.second_cmd[0]);
					check_error(strings.slash_cmd == NULL, ENOMEM, "ft_strjoin() failed.\nError", &strings);
					free_and_init(strings.second_cmd_full_path);
					strings.second_cmd_full_path = ft_strjoin(strings.paths[j], strings.slash_cmd);
					check_error(strings.second_cmd_full_path == NULL, ENOMEM, "ft_strjoin() failed.\nError", &strings);
					free_and_init(strings.slash_cmd);
					second_cmd_path_fd = open(strings.second_cmd_full_path, O_RDONLY);
					close(second_cmd_path_fd);
				}
				if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
					break ;
				j++;
			}
			free_double_pointer_and_init(strings.paths);
		}
		free_double_pointer_and_init(strings.env_var);
		if (first_cmd_path_fd != -1 && second_cmd_path_fd != -1)
			break ;
		else if (path_var_found)
			break ;
		i++;
	}
	check_error(first_cmd_path_fd == -1 || second_cmd_path_fd == -1, EINVAL, "Command not found.\nError", &strings);

	/**
	 * Release stdin (FD 0) so that it no longer refers to any file,
	 * in order to make the next open() call on the input file return
	 * FD 0 (lowest FD available).
	 */
	close_status = close(0);
	check_error(close_status == -1, errno, "close() failed.\nError", &strings);

	int infile_fd = open(argv[1], O_RDONLY);
	check_error(infile_fd == -1, ENOENT, "Input file invalid.\nError", &strings);

	int outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_error(outfile_fd == -1, ENOENT, "Couldn't open/create output file.\nError", &strings);

	/**
	 * Create a pipe with pipe(), it fills in fields of the array
	 * pipe_fd with two open FDs:
	 * One for the read end of the pipe pipe_fd[0],
	 * One for the write end of the pipe pipe_fd[1].
	 * It returns either 0 for success or -1 in case of error.
	 */
	pipe_status = pipe(pipe_fd);
	check_error(pipe_status == -1, errno, "pipe() failed.\nError", &strings);

	/**
	 * Fork a child (child_a) in order to execute the first command.
	 * (fork() returns 0 to the child process, and the PID of the child
	 * to the parent process; otherwise, -1 is returned to the parent
	 * process on error.)
	 *
	 * Then, inside the child process, duplicate the pipe's write end FD
	 * to FD 1 (stdout), so that the output of the command executed by execve(),
	 * if it originally goes to stdout, will go into the write end of the pipe.
	 *
	 * The program ran by execve() reads from stdin (FD 0) by default, which is
	 * now infile_fd.
	 * exit() is not needed in this case since execve() replaces its current process
	 * (the child process) with the exectued program.
	 * 
	 * In the parent process, we then fork a new child (child_b) to run the second
	 * command, then, in the new child process, we duplicate the pipe's read end FD
	 * to FD 0 (stdin), and duplicate the outfile_fd to FD 1 (stdout), so now when
	 * execve() runs the second command, it reads from the read end of the pipe,
	 * and outputs to outfile_fd.
	 *
	 * We perform a wait() for the childs termination in the parent process because
	 * it allows the system to release the resources associated with the childs after
	 * terminating; if a wait is not performed, then the terminated child remains
	 * in a "zombie" state.
	 */
	child_a = fork();
	check_error(child_a == -1, errno, "fork() failed.\nError", &strings);

	if (child_a == 0)
	{
		dup2_fd = dup2(pipe_fd[1], 1);
		check_error(dup2_fd == -1, errno, "dup2() failed.\nError", &strings);

		exec_status = execve(strings.first_cmd_full_path, strings.first_cmd, envp);
		check_error(exec_status == -1, errno, "execve() failed.\nError", &strings);
	}
	else
	{
		child_b = fork();
		check_error(child_b == -1, errno, "fork() failed.\nError", &strings);

		free_double_pointer_and_init(strings.first_cmd);
		free_and_init(strings.first_cmd_full_path);

		if (child_b == 0)
		{
			dup2_fd = dup2(pipe_fd[0], 0);
			check_error(dup2_fd == -1, errno, "dup2() failed.\nError", &strings);

			close_status = close(pipe_fd[1]);
			check_error(close_status == -1, errno, "close() failed.\nError", &strings);

			close_status = close(pipe_fd[0]);
			check_error(close_status == -1, errno, "close() failed.\nError", &strings);

			dup2_fd = dup2(outfile_fd, 1);
			check_error(dup2_fd == -1, errno, "dup2() failed.\nError", &strings);

			exec_status = execve(strings.second_cmd_full_path, strings.second_cmd, envp);
			check_error(exec_status == -1, errno, "execve() failed.\nError", &strings);
		}
		else
		{
			check_error(wait(NULL) == -1, errno, "waitpid() failed.\nError", &strings);
			free_double_pointer_and_init(strings.second_cmd);
			free_and_init(strings.second_cmd_full_path);
		}
	}

	/**
	 * Code here would be shared between all the processes (I guess).
	 */

	return (0);
}
