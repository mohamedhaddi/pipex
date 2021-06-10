/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:04:28 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct	s_strings
{
	char **first_cmd;
	int first_cmd_state;
	char **second_cmd;
	int second_cmd_state;
}				t_strings;

void	free_all_strings(t_strings *strings)
{
	if (strings->first_cmd_state)
		free_double_pointer_and_init(strings->first_cmd, &strings->first_cmd_state);
	if (strings->second_cmd_state)
		free_double_pointer_and_init(strings->second_cmd, &strings->second_cmd_state);
}

void	check_error(bool is_error, int errno_val, char *error_msg, t_strings *strings)
{
	if (is_error)
	{
		free_all_strings(strings);
		raise_error(errno_val, error_msg);
	}
}

void	init_all_strings(t_strings *strings)
{
	strings->first_cmd = malloc(sizeof(char **) * 4);
	check_error(strings->first_cmd == NULL, ENOMEM, "malloc() failed.\nerror", strings);
	strings->first_cmd_state = 1;
	strings->second_cmd = malloc(sizeof(char **) * 4);
	check_error(strings->second_cmd == NULL, ENOMEM, "malloc() failed.\nerror", strings);
	strings->second_cmd_state = 1;
}

void set_cmd(char **dst_cmd, char *cmd, t_strings *strings)
{
	size_t cmd_len;

	cmd_len = ft_strlen(cmd) + 1;
	dst_cmd[0] = malloc(sizeof(char *) * 8);
	check_error(dst_cmd[0] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[0], "/bin/sh", 8);
	dst_cmd[1] = malloc(sizeof(char *) * 3);
	check_error(dst_cmd[1] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[1], "-c", 3);
	dst_cmd[2] = malloc(sizeof(char *) * cmd_len);
	check_error(dst_cmd[2] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[2], cmd, cmd_len);
	dst_cmd[3] = NULL;

}

/**
 * Release stdin (FD 0) so that it no longer refers to any file,
 * in order to make the next open() call on the input file return
 * FD 0 (lowest FD available).
 */
void open_files(int *infile_fd, int *outfile_fd, char **argv, t_strings *strings)
{
	int close_status;

	close_status = close(0);
	check_error(close_status == -1, errno, "close() failed.\nError", strings);
	*infile_fd = open(argv[1], O_RDONLY);
	check_error(*infile_fd == -1, errno, "Input file invalid.\nError", strings);
	*outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_error(*outfile_fd == -1, errno, "Couldn't open/create output file.\nError", strings);
}

/**
 * Create a pipe with pipe(), it fills in fields of the array
 * pipe_fd with two open FDs:
 * One for the read end of the pipe pipe_fd[0],
 * One for the write end of the pipe pipe_fd[1].
 * It returns either 0 for success or -1 in case of error.
 */
void	create_pipe(int *pipe_fd, t_strings *strings)
{
	int pipe_status;

	pipe_status = pipe(pipe_fd);
	check_error(pipe_status == -1, errno, "pipe() failed.\nError", strings);
}

void	raise_child_a(int **fds, t_strings *strings, char **envp)
{
	int exec_status;
	int *pipe_fd;
	int	*dup2_fd;

	pipe_fd = fds[0];
	dup2_fd = fds[1];
	*dup2_fd = dup2(pipe_fd[1], 1);
	check_error(*dup2_fd == -1, errno, "dup2() failed.\nError", strings);
	exec_status = execve(strings->first_cmd[0], strings->first_cmd, envp);
	check_error(exec_status == -1, errno, "execve() failed.\nError", strings);
}

void	raise_child_b(int **fds, t_strings *strings, char **envp)
{
	int exec_status;
	int	close_status;
	int *pipe_fd;
	int	*outfile_fd;
	int	*dup2_fd;

	pipe_fd = fds[0];
	outfile_fd = fds[1];
	dup2_fd = fds[2];
	*dup2_fd = dup2(pipe_fd[0], 0);
	check_error(*dup2_fd == -1, errno, "dup2() failed.\nError", strings);
	close_status = close(pipe_fd[1]);
	check_error(close_status == -1, errno, "close() failed.\nError", strings);
	close_status = close(pipe_fd[0]);
	check_error(close_status == -1, errno, "close() failed.\nError", strings);
	*dup2_fd = dup2(*outfile_fd, 1);
	check_error(*dup2_fd == -1, errno, "dup2() failed.\nError", strings);
	exec_status = execve(strings->second_cmd[0], strings->second_cmd, envp);
	check_error(exec_status == -1, errno, "execve() failed.\nError", strings);
}

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
void	make_children(int *pipe_fd, int *outfile_fd, t_strings *strings, char **envp)
{
	pid_t child_a;
	pid_t child_b;
	int dup2_fd;

	child_a = fork();
	check_error(child_a == -1, errno, "fork() failed.\nError", strings);
	if (child_a == 0)
		raise_child_a((int *[2]){pipe_fd, &dup2_fd}, strings, envp);
	else
	{
		child_b = fork();
		check_error(child_b == -1, errno, "fork() failed.\nError", strings);
		free_double_pointer_and_init(strings->first_cmd, &strings->first_cmd_state);
		if (child_b == 0)
			raise_child_b((int *[3]){pipe_fd, outfile_fd, &dup2_fd}, strings, envp);
		else
		{
			check_error(wait(NULL) == -1, errno, "waitpid() failed.\nError", strings);
			free_double_pointer_and_init(strings->second_cmd, &strings->second_cmd_state);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_strings strings;
	int pipe_fd[2];
	int infile_fd;
	int outfile_fd;

	check_error(argc != 5, EINVAL, "There should be 4 arguments to your program, "
				"e.g.:\n./pipex file1 cmd1 cmd2 file2\nError", &strings);
	init_all_strings(&strings);
	set_cmd(strings.first_cmd, argv[2], &strings);
	set_cmd(strings.second_cmd, argv[3], &strings);
	open_files(&infile_fd, &outfile_fd, argv, &strings);
	create_pipe(pipe_fd, &strings);
	make_children(pipe_fd, &outfile_fd, &strings, envp);
	return (0);
}
