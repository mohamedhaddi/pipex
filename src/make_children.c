/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:16:05 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 09:44:32 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_exit_status(int i, t_arg_data *arg_data)
{
	int	child_status;

	check_error(
		wait(&child_status) == -1, errno, "wait() failed.\nError", arg_data);
	if (WIFEXITED(child_status) != 0 && WEXITSTATUS(child_status) != 0 && i % 2)
	{
		free_all_arg_data(arg_data);
		exit(WEXITSTATUS(child_status));
	}
}

void	raise_child(int **fds, int num_cmd, t_arg_data *arg_data, char **envp)
{
	int	exec_status;
	int	*pipe_fd;
	int	*outfile_fd;

	pipe_fd = fds[0];
	outfile_fd = fds[1];
	if (num_cmd == 0)
		check_error(
			dup2(pipe_fd[1], 1) == -1, errno, "dup2() failed.\nError", arg_data);
	else
		check_error(dup2(*outfile_fd, 1) == -1,
			errno, "No such file or directory.\nError", arg_data);
	exec_status = execve(
			arg_data->cmds[num_cmd][0], arg_data->cmds[num_cmd], envp);
	check_error(
		exec_status == -1, errno, "execve() failed.\nError", arg_data);
}

/**
 * Fork the first child in order to execute the first command (num_cmd = 0).
 * (fork() returns 0 to the child process, and the PID of the child
 * to the parent process; otherwise, -1 is returned to the parent
 * process on error.)
 *
 * Then, inside the child process (raise_child()), if it's the first command,
 * duplicate the pipe's write end FD to FD 1 (stdout), so that the output of
 * the command executed by execve() that goes to stdout would go into the
 * write end of the pipe.
 *
 * The program ran by execve() reads from stdin (FD 0) by default, which is
 * now infile_fd.
 * exit() is not needed in this case since execve() replaces its current process
 * (the child process) with the exectued program.
 *
 * In the parent process, we then close the pipe's write end so that the command
 * won't hang waiting for EOF, and then we call wait() on the childs'
 * termination, for two reasons:
 * 1. It is needed to retreive the termination status of the child process.
 * 2. It allows the system to release the resources associated with the childs
 * after terminating; if a wait is not performed, then the terminated child
 * remains in a "zombie" state.
 *
 * In the second iteration, a new child is then forked to run the second command
 * (num_cmd = 1), we duplicate the pipe's read end FD to FD 0 (stdin). Then, in
 * the new child process, we duplicate the outfile_fd to FD 1 (stdout), so now
 * when execve() runs the second command, it reads from the read end of the pipe,
 * and outputs to outfile_fd.
 *
 * We then close the read end of the pipe in the parent process.
 */
void	make_children(
			int *outfile_fd,
			t_arg_data *arg_data,
			char **envp
			)
{
	pid_t	pids[2];
	int		pipe_fd[2];
	int		num_cmd;

	num_cmd = 0;
	while (num_cmd < 2)
	{
		if (num_cmd == 0)
			create_pipe(pipe_fd, arg_data);
		else
			check_error(dup2(pipe_fd[0], 0) == -1,
				errno, "dup2() failed.\nError", arg_data);
		pids[num_cmd] = fork();
		check_error(
			pids[num_cmd] == -1, errno, "fork() failed.\nError", arg_data);
		if (pids[num_cmd] == 0)
			raise_child(
				(int *[2]){pipe_fd, outfile_fd}, num_cmd, arg_data, envp);
		check_error(
			close(pipe_fd[!num_cmd]) == -1,
			errno, "close() failed.\nError", arg_data);
		check_exit_status(num_cmd, arg_data);
		num_cmd++;
	}
}
