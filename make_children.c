/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:16:05 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:16:48 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	raise_child_a(int **fds, t_strings *strings, char **envp)
{
	int	exec_status;
	int	*pipe_fd;
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
	int	exec_status;
	int	close_status;
	int	*pipe_fd;
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
 * it allows the system to release the resources associated with the childs
 * after terminating; if a wait is not performed, then the terminated child
 * remains in a "zombie" state.
 */
void	make_children(
			int *pipe_fd,
			int *outfile_fd,
			t_strings *strings,
			char **envp
			)
{
	pid_t	child_a;
	pid_t	child_b;
	int		dup2_fd;

	child_a = fork();
	check_error(child_a == -1, errno, "fork() failed.\nError", strings);
	if (child_a == 0)
		raise_child_a((int *[2]){pipe_fd, &dup2_fd}, strings, envp);
	else
	{
		child_b = fork();
		check_error(child_b == -1, errno, "fork() failed.\nError", strings);
		free_double_pointer_and_init(strings->first_cmd,
			&strings->first_cmd_state);
		if (child_b == 0)
			raise_child_b(
				(int *[3]){pipe_fd, outfile_fd, &dup2_fd}, strings, envp);
		else
		{
			check_error(
				wait(NULL) == -1, errno, "waitpid() failed.\nError", strings);
			free_double_pointer_and_init(strings->second_cmd,
				&strings->second_cmd_state);
		}
	}
}
