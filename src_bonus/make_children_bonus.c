/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_children_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:16:05 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 09:47:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_exit_status(int is_last_cmd, t_arg_data *arg_data)
{
	int	child_status;

	check_error(
		wait(&child_status) == -1, errno, "wait() failed.\nError", arg_data);
	if (WIFEXITED(child_status) != 0
		&& WEXITSTATUS(child_status) != 0 && is_last_cmd)
	{
		free_all_arg_data(arg_data);
		exit(WEXITSTATUS(child_status));
	}
}

void	raise_child(int **fds, int *cmd_data, t_arg_data *arg_data, char **envp)
{
	int	exec_status;
	int	*pipe_fd;
	int	*outfile_fd;
	int	num_cmd;
	int	argc;

	pipe_fd = fds[0];
	outfile_fd = fds[1];
	num_cmd = cmd_data[0];
	argc = cmd_data[1];
	if (num_cmd < argc - arg_data->not_cmds - 1)
		check_error(
			dup2(pipe_fd[1], 1) == -1, errno, "dup2() failed.\nError", arg_data);
	else
		check_error(dup2(*outfile_fd, 1) == -1,
			errno, "dup2() failed.\nError", arg_data);
	exec_status = execve(
			arg_data->cmds[num_cmd][0], arg_data->cmds[num_cmd], envp);
	check_error(exec_status == -1, errno, "execve() failed.\nError", arg_data);
}

void	init_pids(int argc, t_arg_data *arg_data)
{
	arg_data->pids = malloc(sizeof(arg_data->pids) * argc);
	check_error(!arg_data->pids, ENOMEM, "malloc() failed.\nError", arg_data);
	arg_data->pids_state = 1;
}

/**
 * We first create the first pipe and start a loop to create more pipes and
 * fork as much child processes as the commands need.
 *
 * Inside the loop, if we're yet in the first command, we proceed and fork
 * the first child without creating a new pipe, so that the first command
 * would read from stdin (where we've got our infile input). Then in the
 * raise_child() function, as long as the command isn't the last one, we
 * duplicate the write end of the pipe into stdout, so that the output of
 * the command we execute next using execve() will go into the pipe.
 *
 * After that, in the parent process, we wait for the exit status of the
 * command in the check_exit_status(), then we close the read end of the
 * pipe (if we don't close it, the command will hang waiting for EOF),
 * then we proceed with the next iteration.
 * 
 * In every new iteration, we then duplicate the read end of the previous
 * pipe into stdin, so that now the content of the pipe can be read through
 * stdin when the next command is run. Right after that we then create a new
 * pipe, where the output of the new command will be written.
 *
 * This is continued until the last command is reached, that's when in the
 * function raise_child(), instead of duplicating the write end of the pipe
 * into stdout, we duplicate the outfile_fd into it, so that the output of
 * the last command will be written into that file.
 */
void	make_children(
			int *outfile_fd,
			t_arg_data *arg_data,
			char **envp,
			int argc
			)
{
	int		pipe_fd[2];
	int		num_cmd;

	init_pids(argc, arg_data);
	create_pipe(pipe_fd, arg_data);
	num_cmd = 0;
	while (num_cmd < (argc - arg_data->not_cmds))
	{
		if (num_cmd)
		{
			check_error(dup2(pipe_fd[0], 0) == -1,
				errno, "dup2() failed.\nError", arg_data);
			create_pipe(pipe_fd, arg_data);
		}
		arg_data->pids[num_cmd] = fork();
		check_error(
			arg_data->pids[num_cmd] < 0, errno, "fork() fail.\nError", arg_data);
		if (arg_data->pids[num_cmd] == 0)
			raise_child((int *[2]){pipe_fd, outfile_fd},
				(int [2]){num_cmd, argc}, arg_data, envp);
		check_error(
			close(pipe_fd[1]) == -1, errno, "close() failed.\nError", arg_data);
		check_exit_status(num_cmd == argc - arg_data->not_cmds - 1, arg_data);
		num_cmd++;
	}
}
